# Saturn YAUL Mednafen Debug

## Lancer le debug automatique

Deux méthodes automatiques sont validées dans cet environnement.

Méthode recommandée pour YAUL `dbgio`:

```powershell
python tools\run_mednafen_debug.py build\yaul_mednafen_probe\yaul_mednafen_probe.cue --docker-image mednafen-ss-dev:1.32.1-yaul-dbgio --timeout 25
```

Pour reconstruire le Mednafen patché si l'image Docker manque:

```powershell
docker build -t mednafen-ss-dev:1.32.1-yaul-dbgio -f tools\mednafen-yaul-dbgio.Dockerfile .
```

Les BIOS ne sont pas copiés dans l'image. Le conteneur monte le projet et lit:

```text
Emulators\mednafen\firmware
```

Un backup des BIOS a été créé ici:

```text
Emulators\_firmware_backup_20260705
```

Méthode validée avec le Mednafen Windows fourni, pour le debug SCSP MIDI déjà présent dans le projet:

```powershell
python tools\run_mednafen_debug.py verdict_guilty_saturn.cue
```

Le script écrit le log combiné dans `logs\mednafen.txt` par défaut. Il retourne `0` seulement si le log contient `[BOOT]` et `[PASS]`, sans marqueur d'échec.

## Lire les logs

- Pas de `[BOOT]`: le programme n'a pas atteint l'initialisation debug, ou Mednafen ne capture pas le canal utilisé.
- `[BOOT]` sans `[PASS]`: le jeu a démarré mais n'a pas atteint le point de succès attendu avant timeout.
- `[CHECKPOINT] name`: dernier point connu avant blocage.
- `[FAIL]`: échec contrôlé; lire le fichier et la ligne imprimés.
- `[FATAL]`: blocage volontaire après une erreur critique.
- `Address Error` ou `Illegal Instruction`: crash CPU; symboliquer le PC si Mednafen donne une adresse.
- Timeout avec `[PASS]`: accepté par le runner, car Mednafen reste ouvert après le succès.
- Timeout sans `[PASS]`: échec; le dernier checkpoint est la zone à inspecter.

## Ajouter un checkpoint

Pour YAUL `dbgio`, initialiser très tôt:

```c
dbgio_init();
dbgio_dev_default_init(DBGIO_DEV_MEDNAFEN_DEBUG);
dbgio_printf("[BOOT] verdict guilty\n");
```

Ajouter ensuite des checkpoints:

```c
dbgio_printf("[CHECKPOINT] after_asset_load\n");
dbgio_printf("[PASS] fixed_asset_load\n");
dbgio_printf("[FAIL] asset load returned null\n");
```

Dans le projet courant, il existe aussi une sortie SCSP MIDI dans `source\saturn\saturn_debug.cpp`:

```c
vg_saturn_debug_stage(42, "after_asset_load");
vg_saturn_debug_puts("[PASS] fixed_asset_load\n");
```

Ne laisse pas un `[PASS]` temporaire comme preuve générale si le chemin testé ne couvre pas réellement le bug.

## Symboliquer une adresse

Générer les fichiers de symboles depuis l'ELF du jeu:

```powershell
docker run --rm -v "${PWD}:/work" -w /work ijacquez/yaul:latest sh -lc "mkdir -p logs; /opt/tool-chains/sh2eb-elf/bin/sh2eb-elf-nm -n build/verdict_guilty_saturn.elf > logs/symbols.txt; /opt/tool-chains/sh2eb-elf/bin/sh2eb-elf-objdump -dS build/verdict_guilty_saturn.elf > logs/game.disasm"
```

Résoudre une adresse:

```powershell
docker run --rm -v "${PWD}:/work" -w /work ijacquez/yaul:latest sh -lc "/opt/tool-chains/sh2eb-elf/bin/sh2eb-elf-addr2line -e build/verdict_guilty_saturn.elf -f -C 0x06082264"
```

Test validé: `0x06082264` résout vers `main`, `source/saturn/VerdictGuilty_Saturn.cpp:385`.

## Trouver un écran noir

Ajoute des checkpoints étroits autour du dernier sous-système suspect:

```c
dbgio_printf("[CHECKPOINT] before_cd_open\n");
dbgio_printf("[CHECKPOINT] after_cd_open\n");
dbgio_printf("[CHECKPOINT] after_texture_upload\n");
```

Relance avec le runner adapté au canal utilisé:

```powershell
python tools\run_mednafen_debug.py verdict_guilty_saturn.cue
python tools\run_mednafen_debug.py build\yaul_mednafen_probe\yaul_mednafen_probe.cue --docker-image mednafen-ss-dev:1.32.1-yaul-dbgio --timeout 25
```

Si le dernier log est `before_cd_open`, inspecte l'ouverture CD. Si le dernier log est `after_cd_open`, inspecte la lecture ou l'upload suivant. Ne corrige qu'une hypothèse à la fois, rebuild, puis relance Mednafen.

## Méthodes à ne pas utiliser comme automatiques ici

Le Mednafen Windows fourni ne capture pas les marqueurs bruts de `DBGIO_DEV_MEDNAFEN_DEBUG`.

Le build officiel Mednafen 1.32.1 compilé avec `--enable-dev-build` et `ss.dbg_mask warning` montre les writes cart `0x02100001(DB=...)`, mais pas les marqueurs `[BOOT]` bruts; c'est un diagnostic partiel, pas une méthode automatique.

Le debugger Mednafen est utile manuellement: lancer Mednafen, `ALT+D` pour ouvrir le debugger, `ALT+1` pour la vue CPU, `Space` pour poser un breakpoint PC. Aucune interface non interactive fiable n'a été validée.

Le GDB stub YAUL n'a pas été validé dans cet environnement, faute de matériel Saturn / USB cart / FTDI / proxy disponible.
