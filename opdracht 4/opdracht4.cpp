#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Vec3D class to represent a 3D vector
class Vec3D {
public:
    float x, y, z;

    Vec3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vec3D operator+(const Vec3D& other) const {
        return Vec3D(x + other.x, y + other.y, z + other.z);
    }

    Vec3D operator-(const Vec3D& other) const {
        return Vec3D(x - other.x, y - other.y, z - other.z);
    }

    Vec3D operator*(float scalar) const {
        return Vec3D(x * scalar, y * scalar, z * scalar);
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

    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3D normalized() const {
        float n = norm();
        return Vec3D(x / n, y / n, z / n);
    }
};

// Ray class to represent a ray in 3D space
class Ray {
public:
    Vec3D origin, direction;

    Ray(const Vec3D& origin, const Vec3D& direction)
        : origin(origin), direction(direction.normalized()) {}
};

// Abstract base class for objects in the scene
class Object {
public:
    Vec3D center;

    Object(float x, float y, float z) : center(x, y, z) {}

    virtual bool hit(const Ray& ray, float& t) const = 0;
};

// Sphere class derived from Object
class Sphere : public Object {
public:
    float radius;

    Sphere(float x, float y, float z, float radius)
        : Object(x, y, z), radius(radius) {}

    bool hit(const Ray& ray, float& t) const override {
        Vec3D oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            t = (-b - std::sqrt(discriminant)) / (2.0f * a);
            return true;
        }
    }
};

// Floor class derived from Object, represents a checkerboard pattern
class Floor : public Object {
public:
    Floor() : Object(0, -1, 0) {}

    bool hit(const Ray& ray, float& t) const override {
        if (std::fabs(ray.direction.y) < 1e-3) return false; // Avoid division by zero
        t = -(ray.origin.y + 1) / ray.direction.y;
        Vec3D hitPoint = ray.origin + ray.direction * t;
        bool isLightSquare = (static_cast<int>(std::floor(hitPoint.x) + std::floor(hitPoint.z)) % 2) == 0;
        return isLightSquare;
    }
};

// Function to render the scene
void renderScene(const std::vector<Object*>& objects, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float u = (2.0f * x) / width - 1.0f;
            float v = (2.0f * y) / height - 1.0f;
            Ray ray(Vec3D(0, 0, 0), Vec3D(u, -v, -1));

            char pixel = ' ';
            float closest_t = std::numeric_limits<float>::max();
            for (const auto& obj : objects) {
                float t;
                if (obj->hit(ray, t) && t < closest_t) {
                    closest_t = t;
                    pixel = '#';
                }
            }
            std::cout << pixel;
        }
        std::cout << std::endl;
    }
}

int main() {
    // Define objects in the scene
    std::vector<Object*> objects;
    objects.push_back(new Sphere(-0.4, 0.23, -1, 0.4));
    objects.push_back(new Sphere(0.4, 0.4, -1.2, 0.3));
    objects.push_back(new Sphere(0.7, -0.15, -1.5, 0.2));
    objects.push_back(new Floor());

    // Render the scene
    int width = 80;
    int height = 40;
    renderScene(objects, width, height);

    // Clean up dynamically allocated memory
    for (auto obj : objects) {
        delete obj;
    }

    return 0;
}
