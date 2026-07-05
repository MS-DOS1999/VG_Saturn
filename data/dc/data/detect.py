import os
from PIL import Image

def is_power_of_two(n):
    return (n & (n - 1)) == 0

def check_png_files(directory):
    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith('.png'):
                filepath = os.path.join(root, filename)
                try:
                    image = Image.open(filepath)
                    width, height = image.size

                    if not is_power_of_two(width) or not is_power_of_two(height):
                        print(f'PNG non power of two: {filepath}')

                    if width > 1024 or height > 1024:
                        print(f'Large PNG: {filepath} ({width}x{height})')

                except Exception as e:
                    print(f'Error processing {filepath}: {e}')

if __name__ == '__main__':
    directory = './'  # Remplacez ceci par le chemin de votre dossier racine
    check_png_files(directory)
