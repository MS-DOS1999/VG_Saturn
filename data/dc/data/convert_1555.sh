#!/bin/bash

# Chemin vers texconv
TEXCONV="/mnt/c/Users/Julien/Desktop/PROG/VerdictRepos/VerdictGuilty/tools/texconv/texconv"

# Fonction pour convertir un fichier PNG en .tex
convert_png_to_tex() {
    png_file="$1"
    tex_output_dir="$2"

    png_filename=$(basename "$png_file")
    tex_filename="${png_filename%.png}.tex"
    tex_output_file="$tex_output_dir/$tex_filename"

    # Exécution de la commande texconv
    "$TEXCONV" -i "$png_file" -o "$tex_output_file" -f ARGB1555 -c -v

    echo "Conversion réussie : $png_file -> $tex_output_file"
}

# Fonction pour parcourir le dossier et ses sous-dossiers
convert_pngs_in_directory() {
    directory="$1"

    find "$directory" -type f -name "*.png" | while read -r png_file; do
        convert_png_to_tex "$png_file" "$(dirname "$png_file")"
    done
}

# Appel de la fonction pour convertir les PNGs dans un dossier
directory="./"  # Remplacez ceci par le chemin de votre dossier racine
convert_pngs_in_directory "$directory"
