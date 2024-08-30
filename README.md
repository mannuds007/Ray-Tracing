# Ray Tracer Project

## Overview

This project implements a simple ray tracer in C++ that renders 3D scenes with various shapes and materials. The ray tracer supports features such as reflection, refraction, lighting, depth of field, and animation. The project also includes a script to automate the building and execution of the ray tracer.

## Features

- **Vector Operations**: Basic operations like addition, subtraction, dot product, cross product, and normalization.
- **Materials**: Different materials with properties like diffuse color, specular exponent, and refractive index.
- **Shapes**: Spheres and cubes, with the possibility to extend to other shapes.
- **Ray Tracing**: Calculates intersections of rays with objects, handles reflections, refractions, and shadows.
- **Depth of Field**: Simulates camera focus by adjusting the sharpness of objects based on their distance from the focal point.
- **Animation**: Generates frames over time to create animations.

## Mathematics Used


### Ray-Sphere Intersection

The equation to find the intersection of a ray with a sphere:

1. **Ray Equation**: P = O + t * D  
2. **Sphere Equation**: |P - C|^2 = R^2  

Combining these equations gives a quadratic in `t`:

`t^2 * (D · D) + 2 * t * ((O - C) · D) + ((O - C) · (O - C) - R^2) = 0`

### Ray-Cube Intersection

To find the intersection of a ray with a cube, we check the intersection with each of the cube’s six planes. The intersection of the ray with each axis-aligned plane is calculated, and we check if the intersection point is within the bounds of the cube.

### Reflection and Refraction

- **Reflection**:  
  `R = I - 2 * (I · N) * N`  
  where `I` is the incident vector, and `N` is the normal vector at the intersection point.

- **Refraction**: Calculated using Snell's law, taking into account the change in refractive index:  
  `R = η * I + (η * cosθi - cosθt) * N`  
  where `η = n1 / n2` is the relative refractive index, `θi` is the incident angle, and `θt` is the transmitted angle.

### Depth of Field

Depth of field is simulated by perturbing the ray origin slightly based on the aperture size and focusing the camera on a specific distance (focal length).

- **Aperture Sampling**: Randomly perturb the origin within an aperture.
- **Focus Plane**: Adjust rays so they converge on a focal plane at a specific distance.

### Animation

Animation is created by updating the scene for each frame and rendering the frames in sequence. Objects can be moved, rotated, or scaled over time to create animated effects.

## How to Run the Automated File

To automate the building and execution of the ray tracer, a Python script (`build_and_run.py`) is provided. This script performs the following steps:

1. **Navigate to the build directory**:
    ```bash
    cd build
    ```

2. **Generate build files using CMake**:
    ```bash
    cmake ..
    ```

3. **Build the project**:
    ```bash
    cmake --build . --config Release
    ```

4. **Run the executable**:
    ```bash
    cd Release
    ./raytracer.exe
    ```

### Automating with Python

To run the automation script, use Python to execute the commands in sequence:


```bash
python automate.py
```
