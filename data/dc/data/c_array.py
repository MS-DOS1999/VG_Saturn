import os
from PIL import Image

def is_power_of_two(n):
    return (n & (n - 1)) == 0

def check_png_files(directory):
    png_2048x2048 = []
    png_2048x256 = []

    for root, dirs, files in os.walk(directory):
        for filename in files:
            if filename.endswith('.png'):
                filepath = os.path.join(root, filename)
                try:
                    image = Image.open(filepath)
                    width, height = image.size

                    if width == 2048 and height == 2048:
                        png_2048x2048.append(filepath)
                    elif width == 2048 and height == 256:
                        png_2048x256.append(filepath)

                except Exception as e:
                    print(f'Error processing {filepath}: {e}')

    return png_2048x2048, png_2048x256

def save_paths_to_c_array(paths, output_file):
    with open(output_file, 'w') as f:
        f.write("const char *png_paths[] = {\n")
        for path in paths:
            path = path.replace("\\", "/")
            path = path.replace(".png", ".tex")
            path = path.lstrip("./")
            f.write(f'    "{path}",\n')
        f.write("};\n")

if __name__ == '__main__':
    directory = './'  # Remplacez ceci par le chemin de votre dossier racine
    png_2048x2048, png_2048x256 = check_png_files(directory)

    save_paths_to_c_array(png_2048x2048, 'png_paths_2048x2048.h')
    save_paths_to_c_array(png_2048x256, 'png_paths_2048x256.h')