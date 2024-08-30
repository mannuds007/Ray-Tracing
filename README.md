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


### Diffuse Lighting

To compute the intensity of diffuse lighting, we use the Lambertian reflectance model, which states that the amount of light diffused from a surface is proportional to the cosine of the angle between the light direction and the surface normal.

### Diffuse Lighting Intensity:

$$
I_{\text{diffuse}} = \max(0, \mathbf{L} \cdot \mathbf{N})
$$

Where:

- $$\(\mathbf{L}\)$$ is the direction of the light source.
- $$\(\mathbf{N}\)$$ is the surface normal at the point of intersection.

This formula ensures that only light that strikes the surface at an angle greater than 90 degrees contributes to the diffuse reflection, providing realistic shading.

###. Specular Lighting

The specular component represents the bright spot of light that appears on shiny objects when illuminated. This is calculated using the Blinn-Phong reflection model.

### Specular Lighting Intensity:

$$
I_{\text{specular}} = \text{pow}(\max(0, -\mathbf{R} \cdot \mathbf{D}), \text{exp})
$$

Where:

- $$\(\mathbf{R}\)$$ is the reflected light direction.
- $$\(\mathbf{D}\)$$ is the view (or camera) direction.
- $$\(\text{exp}\)$$ is the specular exponent that controls the shininess of the surface. Higher values create smaller, sharper highlights, resembling a more polished surface.

This equation models how light reflects off a shiny surface and is seen as a bright spot or highlight.

### Camera Ray Generation

To generate rays from the camera through each pixel, the direction of the ray is calculated from the camera's origin to the pixel's position on the image plane. This ensures that each ray accurately corresponds to the pixel it represents.

### Camera Ray Direction:

$$
\mathbf{D} = \frac{\mathbf{p} - \mathbf{o}}{\|\mathbf{p} - \mathbf{o}\|}
$$

Where:

- $$\(\mathbf{p}\)$$ is the pixel position on the image plane.
- $$\(\mathbf{o}\)$$ is the camera origin.
- $$\(\mathbf{D}\)$$ is the normalized direction vector from the camera origin through the pixel position.

This normalization step ensures that the direction vector $$\(\mathbf{D}\)$$ is a unit vector, which is essential for consistent ray tracing calculations.

### Depth of Field

Depth of Field (DoF) is a photographic and rendering effect that simulates the focus range of a camera lens, causing objects at certain distances to appear sharp while others appear blurred.

To achieve depth of field in ray tracing, you can use the following formula to generate additional rays from slightly offset camera positions:

### Depth of Field Equation:

$$
\mathbf{r}_{\text{focus}} = \mathbf{o} + f \cdot (\mathbf{p} - \mathbf{o})
$$

Where:

- $$\(\mathbf{r}_{\text{focus}}\)$$ is the focal point, calculated as a point along the original ray direction where the camera is focused.
- $$\(f\)$$ is the focal distance, which determines how far from the camera the scene will be in sharp focus.
- $$\(\mathbf{o}\)$$ is the camera origin.
- $$\(\mathbf{p}\)$$ is the original pixel position.

To simulate the depth of field, multiple rays are cast from the camera origin with slight offsets, converging towards the focal point $$\(\mathbf{r}_{\text{focus}}\)$$. These rays contribute to the final pixel color, with objects in focus being sharply rendered and those out of focus appearing blurred.


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
