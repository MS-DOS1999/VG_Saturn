# YAUL / Mednafen Saturn Debug Methods Report

Date: 2026-07-05
Project: `C:\Users\Julien\Desktop\PROG\VerdictGuilty_Saturn`

| Méthode | Statut | Commande testée | Résultat | Notes |
|---|---|---|---|---|
| build YAUL debug | VALIDÉ | `.\build_saturn.ps1`; probe dbgio: `docker run --rm -v "${PWD}:/work" -w /work ijacquez/yaul:latest sh -lc 'make clean SH_PROGRAM=yaul_mednafen_probe SH_SRCS=tools/yaul_mednafen_probe.c SH_BUILD_DIR=build/yaul_mednafen_probe SH_OUTPUT_DIR=build/yaul_mednafen_probe IMAGE_DIRECTORY=build/yaul_mednafen_probe/cd && make SH_PROGRAM=yaul_mednafen_probe SH_SRCS=tools/yaul_mednafen_probe.c SH_BUILD_DIR=build/yaul_mednafen_probe SH_OUTPUT_DIR=build/yaul_mednafen_probe IMAGE_DIRECTORY=build/yaul_mednafen_probe/cd'` | `.\build_saturn.ps1` retourne `0`; le probe produit ELF/CUE avec `-g`. | Le projet utilise Docker `ijacquez/yaul:latest`; `YAUL_INSTALL_ROOT=/opt/tool-chains/sh2eb-elf`. Pas de `.yaul.env` locale chargée dans PowerShell. |
| dbgio YAUL vers Mednafen patché | VALIDÉ | `python tools\run_mednafen_debug.py build\yaul_mednafen_probe\yaul_mednafen_probe.cue --docker-image mednafen-ss-dev:1.32.1-yaul-dbgio --timeout 25 --log logs\mednafen_dbgio_patched_script.txt` | Retour `0`; le log contient `[BOOT] yaul mednafen debug probe`, `[CHECKPOINT] main_entry`, `[PASS] mednafen_debug_output_ok`. | Image Docker testée `mednafen-ss-dev:1.32.1-yaul-dbgio`. Patch ciblé: write cart 8-bit à `0x02100001`, octet bas de `DB` vers stdout. Dockerfile reproductible: `tools/mednafen-yaul-dbgio.Dockerfile`. |
| dbgio YAUL vers Mednafen fourni | ÉCHEC | `python tools\run_mednafen_debug.py build\yaul_mednafen_probe\yaul_mednafen_probe.cue --timeout 25 --log logs\mednafen_dbgio_probe.txt` | Retour `1`, `missing [BOOT]`; aucun marqueur brut dans stdout. | `DBGIO_DEV_MEDNAFEN_DEBUG` écrit vers `0x22100001`, qui arrive dans Mednafen comme `0x02100001`, mais le build Windows 1.32.1 fourni ne l'imprime pas. |
| Mednafen officiel dev `ss.dbg_mask` | PARTIEL | Config Docker: `ss.dbg_mask warning`; run du CUE dbgio avec `mednafen-ss-dev:1.32.1-official`. | `logs\mednafen_dbgio_dev_warning.txt` montre `[CART] Unknown 1-byte write to 0x02100001(DB=...)`, mais pas de marqueurs `[BOOT]` bruts. | Confirme l'adresse et l'octet bas, utile pour diagnostic, pas suffisant comme méthode automatique de logs. `-ss.dbg_mask` par CLI est rejeté; via `mednafen.cfg`, le setting est accepté. |
| SCSP MIDI direct vers Mednafen | VALIDÉ | `python tools\run_mednafen_debug.py build\yaul_scsp_midi_probe\yaul_scsp_midi_probe.cue` | Retour `0`; `logs\mednafen.txt` contient `[BOOT] yaul scsp midi probe`, `[CHECKPOINT] main_entry`, `[PASS] scsp_midi_stdout_ok`. | Méthode automatique fonctionnelle avec le Mednafen fourni, `-ss.midi stdout` et `MEDNAFEN_NOSTDREDIR=1`. |
| Mednafen stdout capture | VALIDÉ | Mednafen fourni: `mednafen.exe -force_module ss -ss.midi stdout -sound 0 -video.driver softfb -cd.image_memcache 1 -filesys.path_firmware Emulators\mednafen\firmware ...`; Mednafen patché Docker via `--docker-image`. | Les marqueurs SCSP MIDI et dbgio patché sont capturés dans les fichiers `logs\*.txt`. | Sur Windows, `MEDNAFEN_NOSTDREDIR=1` est nécessaire; sinon Mednafen peut écrire `stdout.txt` / `stderr.txt`. |
| script automatique `run_mednafen_debug.py` | VALIDÉ | `python tools\run_mednafen_debug.py build\yaul_mednafen_probe\yaul_mednafen_probe.cue --docker-image mednafen-ss-dev:1.32.1-yaul-dbgio --timeout 25 --log logs\mednafen_dbgio_patched_script.txt` | Retour `0` avec `[BOOT]` et `[PASS]`; timeout accepté uniquement parce que `[PASS]` est déjà présent. | Le script retourne `1` sur marqueurs `[FAIL]`, `[FATAL]`, `Address Error`, `Illegal Instruction`, `Unhandled`, `assert`, `segmentation fault`, ou si `[BOOT]` manque. |
| symbolication `nm` / `objdump` / `addr2line` | VALIDÉ | `sh2eb-elf-nm -n build/verdict_guilty_saturn.elf > logs/symbols.txt`; `sh2eb-elf-objdump -dS build/verdict_guilty_saturn.elf > logs/game.disasm`; `sh2eb-elf-addr2line -e build/verdict_guilty_saturn.elf -f -C 0x06082264` | `addr2line` retourne `main` puis `/work/source/saturn/VerdictGuilty_Saturn.cpp:385`. | Symbolication fonctionnelle avec les outils du conteneur YAUL. |
| crash markers `[PASS]` / `[FAIL]` / `[FATAL]` | PARTIEL | Probe dbgio patché avec `[PASS]`; runner inspecte `[FAIL]`, `[FATAL]`, `Address Error`, `Illegal Instruction`, `Unhandled`, `assert`, `segmentation fault`. | `[PASS]` validé en exécution Mednafen et via le script. | Aucun `[FATAL]` volontaire n'a été laissé dans le jeu. Le cas fatal volontaire n'a pas été conservé dans les sources. |
| debugger interactif Mednafen | PARTIEL | Lancement Mednafen normal avec les CUE de probe. | Mednafen démarre; documentation locale: `ALT+D` debugger, `ALT+1` CPU, `Space` breakpoint PC, vues mémoire/registres. | Méthode manuelle utile. Aucune interface non interactive fiable trouvée/testée. |
| YAUL GDB stub | NON VALIDÉ | Recherche `rg "gdb|stub"` dans le projet et inspection du conteneur YAUL. | `sh2eb-elf-gdb` existe, mais aucun GDB stub YAUL utilisable avec Mednafen n'a été validé. | Aucun matériel Saturn / USB cart / FTDI / proxy disponible. Ne pas utiliser comme méthode automatique Mednafen. |

## Environnement confirmé

- YAUL/libyaul: présent dans Docker `ijacquez/yaul:latest`, `YAUL_INSTALL_ROOT=/opt/tool-chains/sh2eb-elf`.
- `.yaul.env`: non trouvé/chargé localement; non nécessaire pour le build Docker du projet.
- `make`: présent dans le conteneur Docker.
- Mednafen fourni: `Emulators\mednafen\mednafen.exe`, version 1.32.1.
- Mednafen dev officiel Docker: `mednafen-ss-dev:1.32.1-official`, compilé avec `--enable-dev-build`.
- Mednafen YAUL dbgio Docker: `mednafen-ss-dev:1.32.1-yaul-dbgio`, testé avec `[PASS]`.
- BIOS conservés: `Emulators\mednafen\firmware\mpr-17933.bin`, `Emulators\mednafen\firmware\sega_101.bin`; backup `Emulators\_firmware_backup_20260705`.
- Toolchain SH2: `/opt/tool-chains/sh2eb-elf/bin/sh2eb-elf-gcc`, `nm`, `objdump`, `addr2line`.
- ELF jeu: `build/verdict_guilty_saturn.elf`.
- CUE jeu: `verdict_guilty_saturn.cue`.

## Conclusion

Deux chaînes automatiques sont validées:

1. `YAUL dbgio -> Mednafen patché Docker -> stdout -> tools/run_mednafen_debug.py -> logs -> [PASS]`.
2. `SCSP MIDI OUT direct -> Mednafen fourni -ss.midi stdout -> tools/run_mednafen_debug.py -> logs -> [PASS]`.

La chaîne `dbgio_dev_default_init(DBGIO_DEV_MEDNAFEN_DEBUG)` n'est pas fonctionnelle avec le Mednafen Windows fourni non patché. Elle devient fonctionnelle uniquement avec le build Docker patché `mednafen-ss-dev:1.32.1-yaul-dbgio`.
