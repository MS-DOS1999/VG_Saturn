import os
from PIL import Image

def split_image(image_path):
    # Ouvrir l'image
    with Image.open(image_path) as img:
        # Vérifier si l'image fait bien 2048x256 pixels
        if img.width == 2048 and img.height == 256:
            # Diviser l'image en 2 parties de 1024x256 pixels
            parts = [
                img.crop((0, 0, 1024, 256)),  # Gauche
                img.crop((1024, 0, 2048, 256))  # Droite
            ]
            # Obtenir le chemin et le nom du fichier sans l'extension
            base_name, ext = os.path.splitext(image_path)
            # Enregistrer les parties
            for i, part in enumerate(parts):
                part.save(f"{base_name}_{i}{ext}")

def process_directory(directory):
    # Parcourir tous les fichiers et sous-dossiers dans le répertoire donné
    for root, dirs, files in os.walk(directory):
        for file in files:
            # Vérifier si le fichier est un fichier PNG
            if file.lower().endswith(".png"):
                file_path = os.path.join(root, file)
                split_image(file_path)

# Entrer le chemin du dossier à analyser
directory_path = input("Entrez le chemin du dossier à analyser : ")
process_directory(directory_path)
