Here is a `README.md` file for your ray tracer project, including descriptions of the mathematics used, depth of field, animation, and instructions on how to run the automated file:

---

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

### Vector Operations

Vectors are fundamental in ray tracing for representing directions, positions, and colors.

- **Dot Product**: Measures the cosine of the angle between two vectors, used for lighting calculations.
  \[
  \mathbf{v}_1 \cdot \mathbf{v}_2 = v_{1x}v_{2x} + v_{1y}v_{2y} + v_{1z}v_{2z}
  \]

- **Cross Product**: Produces a vector perpendicular to two given vectors, used for calculating normals.
  \[
  \mathbf{v}_1 \times \mathbf{v}_2 = (v_{1y}v_{2z} - v_{1z}v_{2y}, v_{1z}v_{2x} - v_{1x}v_{2z}, v_{1x}v_{2y} - v_{1y}v_{2x})
  \]

- **Normalization**: Converts a vector to a unit vector, preserving its direction.
  \[
  \mathbf{\hat{v}} = \frac{\mathbf{v}}{|\mathbf{v}|} = \frac{\mathbf{v}}{\sqrt{v_x^2 + v_y^2 + v_z^2}}
  \]

### Ray-Sphere Intersection

The equation to find the intersection of a ray with a sphere:

\[
\text{Ray:} \quad \mathbf{P} = \mathbf{O} + t\mathbf{D}
\]

\[
\text{Sphere:} \quad |\mathbf{P} - \mathbf{C}|^2 = R^2
\]

Combining these equations, we get a quadratic in \(t\):

\[
t^2 (\mathbf{D} \cdot \mathbf{D}) + 2t (\mathbf{O} - \mathbf{C}) \cdot \mathbf{D} + (\mathbf{O} - \mathbf{C}) \cdot (\mathbf{O} - \mathbf{C}) - R^2 = 0
\]

### Ray-Cube Intersection

To find the intersection of a ray with a cube, we check the intersection with each of the cube’s six planes. The intersection of the ray with each axis-aligned plane is calculated, and we check if the intersection point is within the bounds of the cube.

### Reflection and Refraction

- **Reflection**: Calculated using the reflection formula:
  \[
  \mathbf{R} = \mathbf{I} - 2(\mathbf{I} \cdot \mathbf{N})\mathbf{N}
  \]
  where \(\mathbf{I}\) is the incident vector, and \(\mathbf{N}\) is the normal vector at the intersection point.

- **Refraction**: Calculated using Snell's law, taking into account the change in refractive index:
  \[
  \mathbf{R} = \eta \mathbf{I} + (\eta \cos \theta_i - \cos \theta_t)\mathbf{N}
  \]
  where \(\eta = \frac{n_1}{n_2}\) is the relative refractive index, \(\theta_i\) is the incident angle, and \(\theta_t\) is the transmitted angle.

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
1. **Navigate to the build directory**:
 ```bash
    python automate.py
    ```
