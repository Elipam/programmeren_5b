#include <iostream>
#include <cmath>
#include <vector>
#include <string>

// Vec3D class: Represents a 3D vector
class Vec3D {
public:
    float x, y, z;

    // Constructor
    Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}

    // Methods for vector operations
    Vec3D add(const Vec3D& other) const {
        return Vec3D(x + other.x, y + other.y, z + other.z);
    }

    Vec3D sub(const Vec3D& other) const {
        return Vec3D(x - other.x, y - other.y, z - other.z);
    }

    Vec3D mul(float scalar) const {
        return Vec3D(x * scalar, y * scalar, z * scalar);
    }

    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3D unit() const {
        float length = norm();
        if (length == 0.0f) {
            std::cerr << "Error: Cannot normalize a zero-length vector.\n";
            return *this; // Return original vector as fallback
        }
        return mul(1.0f / length);
    }

    float dot(const Vec3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3D cross(const Vec3D& other) const {
        return Vec3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    // Display the vector
    void show(const std::string& label) const {
        std::cout << label << ": (" << x << ", " << y << ", " << z << ")\n";
    }
};

// Ray class: Represents a ray with a support vector and a direction vector
class Ray {
public:
    Vec3D support;
    Vec3D direction;

    // Constructor
    Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir)
        : support(xSup, ySup, zSup), direction(xDir, yDir, zDir) {}
};

// Sphere class: Represents a sphere with a center and a radius
class Sphere {
public:
    Vec3D center;
    float radius;

    // Constructor
    Sphere(float x, float y, float z, float radius)
        : center(x, y, z), radius(radius) {}

    // Calculate distance from the ray to the center of the sphere
    float distFromRay(const Ray& ray) const {
        Vec3D oc = ray.support.sub(center);
        Vec3D d = ray.direction.unit();
        Vec3D oc_proj = oc.sub(d.mul(oc.dot(d)));
        return oc_proj.norm();
    }

    // Check if the ray hits the sphere
    bool hit(const Ray& ray) const {
        return distFromRay(ray) <= radius;
    }

    // Calculate the hit point of the ray with the sphere
    Vec3D hitPoint(const Ray& ray) const {
        if (!hit(ray)) {
            std::cerr << "Ray does not hit the sphere.\n";
            return Vec3D(0.0f, 0.0f, 0.0f);
        }
        Vec3D oc = ray.support.sub(center);
        float t = -oc.dot(ray.direction.unit());
        return ray.support.add(ray.direction.unit().mul(t));
    }
};

// Main function to test the classes
int main() {
    // Create a list of spheres
    std::vector<Sphere> spheres = {
        Sphere(-0.4, 0.23, -1, 0.4),
        Sphere(0.4, 0.4, -1.2, 0.3),
        Sphere(0.7, -0.15, -1.5, 0.2)
    };

    // Create a list of rays
    float far = 1000.0f; // Arbitrary large value for the ray's distance
    std::vector<Ray> rays = {
        Ray(-far, 0.23, -1, far, 0, 0),
        Ray(0.4, -far, -1.2, 0, far, 0),
        Ray(0.7, -0.15, -far, 0, 0, far)
    };

    // Test each ray with each sphere
    for (const auto& ray : rays) {
        for (const auto& sphere : spheres) {
            if (sphere.hit(ray)) {
                Vec3D point = sphere.hitPoint(ray);
                point.show("Hit Point");
            } else {
                std::cout << "No hit detected.\n";
            }
        }
        std::cout << "\n";
    }

    return 0;
}
