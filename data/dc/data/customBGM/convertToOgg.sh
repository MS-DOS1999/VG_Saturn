#!/bin/bash

# Parcourir tous les fichiers WAV dans le répertoire actuel
for fichier_wav in *.wav; do
    # Vérifier s'il y a des fichiers WAV à traiter
    [ -e "$fichier_wav" ] || continue

    # Définir le nom de fichier de sortie OGG en remplaçant l'extension WAV par OGG
    fichier_ogg="${fichier_wav%.wav}.ogg"

    # Convertir le fichier WAV en OGG avec les paramètres spécifiés
    ffmpeg -i "$fichier_wav" -ar 22050 -ac 1 "$fichier_ogg"

    echo "Conversion de $fichier_wav terminée. OGG créé : $fichier_ogg"
done