import subprocess
import os
from PIL import Image

def convert_ppm_to_jpg(input_file, output_file):
    # Open the PPM file
    with Image.open(input_file) as im:
        # Save the image as JPG
        im.save(output_file, 'JPEG')

def run_command(command, cwd=None):
    """Run a shell command and return the output and error."""
    result = subprocess.run(command, shell=True, cwd=cwd, capture_output=True, text=True)
    return result.stdout, result.stderr

def main():
    # Paths
    build_dir = "build"
    release_dir = os.path.join(build_dir, "Release")
    #Change directory to build
    os.makedirs(build_dir, exist_ok=True)
    

    print("Running CMake configuration...")
    stdout, stderr = run_command("cmake ..", cwd=build_dir)
    print("CMake Output:", stdout)
    print("CMake Error:", stderr)
    

    print("Building the project...")
    stdout, stderr = run_command("cmake --build . --config Release", cwd=build_dir)
    print("Build Output:", stdout)
    print("Build Error:", stderr)
    
  
    os.makedirs(release_dir, exist_ok=True)
    

    print("Running the executable...")
    stdout, stderr = run_command("raytracer.exe", cwd=release_dir)
    print("Executable Output:", stdout)
    print("Executable Error:", stderr)


    input_path = 'build/Release/out.ppm'
    output_path = 'output.jpg'

    # Convert the image
    convert_ppm_to_jpg(input_path, output_path)

    print(f"Image saved as {output_path}")

if __name__ == "__main__":
    main()
