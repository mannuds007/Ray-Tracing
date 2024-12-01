#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>
#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using Vector3f = Eigen::Vector3f;

struct Material {
    float refractive_index = 1;
    float albedo[4] = {2, 0, 0, 0};
    Vector3f diffuse_color = {0, 0, 0};
    float specular_exponent = 0;
};

// Sphere structure definition
struct Sphere {
    Vector3f center;
    float radius;
    Material material;
};

// Cube structure definition
struct Cube {
    Vector3f center;
    float size;
    Material material;
};

// Material definitions
constexpr Material marble = {1.0, {0.8, 0.2, 0.0, 0.0}, {0.5, 0.5, 0.5}, 30.};
constexpr Material water = {1.3, {0.1, 0.4, 0.7, 0.5}, {0.2, 0.5, 0.8}, 100.};
constexpr Material shiny_red = {1.0, {1.2, 0.3, 0.0, 0.1}, {0.7, 0.1, 0.1}, 200.};
constexpr Material bronze = {1.0, {0.4, 0.3, 0.2, 0.1}, {0.8, 0.7, 0.5}, 500.};

// Scene objects
constexpr Sphere spheres[] = {
    {{-2, 1, -15}, 1.5, marble},
    {{0, 4, -12}, 2.0, water},
    {{2, 0, -18}, 2.5, shiny_red},
    {{5, 3, -20}, 3.5, bronze}};

constexpr Cube cube = {{0, -1, -10}, 2.0, water};

// Light positions
constexpr Vector3f lights[] = {
    {-15, 10, 25},
    {20, 30, -30},
    {10, 10, 15}};

// Reflect and refract functions
Vector3f reflect(const Vector3f &I, const Vector3f &N) {
    return I - 2.0f * (I.dot(N)) * N;
}

Vector3f refract(const Vector3f &I, const Vector3f &N, const float eta_t, const float eta_i = 1.f) {
    float cosi = -std::clamp(I.dot(N), -1.f, 1.f);
    if (cosi < 0) return refract(I, -N, eta_i, eta_t);
    float eta = eta_i / eta_t;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? Vector3f(1, 0, 0) : I * eta + N * (eta * cosi - std::sqrt(k));
}

// Ray-sphere intersection
std::tuple<bool, float> ray_sphere_intersect(const Vector3f &orig, const Vector3f &dir, const Sphere &s) {
    Vector3f L = s.center - orig;
    float tca = L.dot(dir);
    float d2 = L.dot(L) - tca * tca;
    if (d2 > s.radius * s.radius) return {false, 0};
    float thc = std::sqrt(s.radius * s.radius - d2);
    float t0 = tca - thc, t1 = tca + thc;
    if (t0 > .001) return {true, t0};
    if (t1 > .001) return {true, t1};
    return {false, 0};
}

// Scene intersection function
std::tuple<bool, Vector3f, Vector3f, Material> scene_intersect(const Vector3f &orig, const Vector3f &dir) {
    Vector3f pt, N;
    Material material;

    float nearest_dist = 1e10;
    for (const Sphere &s : spheres) {
        auto [intersection, d] = ray_sphere_intersect(orig, dir, s);
        if (!intersection || d > nearest_dist) continue;
        nearest_dist = d;
        pt = orig + dir * nearest_dist;
        N = (pt - s.center).normalized();
        material = s.material;
    }
    return {nearest_dist < 1000, pt, N, material};
}

// Cast ray function
Vector3f cast_ray(const Vector3f &orig, const Vector3f &dir, const int depth = 0) {
    auto [hit, point, N, material] = scene_intersect(orig, dir);
    if (depth > 4 || !hit) return {0.2, 0.7, 0.8};

    Vector3f reflect_dir = reflect(dir, N).normalized();
    Vector3f refract_dir = refract(dir, N, material.refractive_index).normalized();
    Vector3f reflect_color = cast_ray(point, reflect_dir, depth + 1);
    Vector3f refract_color = cast_ray(point, refract_dir, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (const Vector3f &light : lights) {
        Vector3f light_dir = (light - point).normalized();
        auto [hit, shadow_pt, trashnrm, trashmat] = scene_intersect(point, light_dir);
        if (hit && (shadow_pt - point).norm() < (light - point).norm()) continue;
        diffuse_light_intensity += std::max(0.f, light_dir.dot(N));
        specular_light_intensity += std::pow(std::max(0.f, -reflect(-light_dir, N).dot(dir)), material.specular_exponent);
    }
    return material.diffuse_color * diffuse_light_intensity * material.albedo[0] +
           Vector3f{1., 1., 1.} * specular_light_intensity * material.albedo[1] +
           reflect_color * material.albedo[2] +
           refract_color * material.albedo[3];
}

int main() {
    constexpr int width = 1024;
    constexpr int height = 768;
    constexpr float fov = 1.05;
    std::vector<Vector3f> framebuffer(width * height);

#pragma omp parallel for
    for (int pix = 0; pix < width * height; pix++) {
        float dir_x = (pix % width + 0.5) - width / 2.;
        float dir_y = -(pix / width + 0.5) + height / 2.;
        float dir_z = -height / (2. * tan(fov / 2.));
        framebuffer[pix] = cast_ray(Vector3f{0, 0, 0}, Vector3f{dir_x, dir_y, dir_z}.normalized());
    }

    std::ofstream ofs;
    ofs.open("out.ppm", std::ofstream::out | std::ofstream::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (const Vector3f &color : framebuffer) {
        float max = std::max(1.f, std::max(color[0], std::max(color[1], color[2])));
        for (int chan : {0, 1, 2})
            ofs << (char)(255 * color[chan] / max);
    }
    return 0;
}
