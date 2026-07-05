#!/bin/bash

# Répertoire source contenant les fichiers .adx
source_dir="./"

# Répertoire cible où les fichiers .adx seront copiés
target_dir="/mnt/c/Users/Julien/Desktop/PROG/VerdictRepos/VerdictGuilty/data/dc/"

# Vérification si le répertoire source existe
if [ ! -d "$source_dir" ]; then
    echo "Erreur: Le répertoire source '$source_dir' n'existe pas."
    exit 1
fi

# Vérification si le répertoire cible existe, sinon le créer
if [ ! -d "$target_dir" ]; then
    mkdir -p "$target_dir"
fi

# Recherche récursive des fichiers .adx dans le répertoire source
find "$source_dir" -type f -name "*.adx" | while read -r adx_file; do
    # Chemin relatif du fichier .adx par rapport au répertoire source
    relative_path="${adx_file#$source_dir/}"
    
    # Création du répertoire cible s'il n'existe pas déjà
    mkdir -p "$target_dir/$(dirname "$relative_path")"
    filename=$(basename "$adx_file")
    # Copie du fichier .adx dans le répertoire cible
    cp "$adx_file" "$target_dir/$filename"
    
    echo "Copié: $filename"
done

echo "Terminé."
