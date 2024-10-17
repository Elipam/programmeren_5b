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

    Vec3D normalized() const {
        float n = std::sqrt(x * x + y * y + z * z);
        return Vec3D(x / n, y / n, z / n);
    }

    Vec3D reflect(const Vec3D& normal) const {
        return *this - normal * 2.0f * this->dot(normal);
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
    virtual bool hit(const Ray& ray, float& t, Vec3D& normal) const = 0;
};

// Sphere class derived from Object
class Sphere : public Object {
public:
    Vec3D center;
    float radius;

    Sphere(const Vec3D& center, float radius)
        : center(center), radius(radius) {}

    bool hit(const Ray& ray, float& t, Vec3D& normal) const override {
        Vec3D oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            t = (-b - std::sqrt(discriminant)) / (2.0f * a);
            Vec3D hitPoint = ray.origin + ray.direction * t;
            normal = (hitPoint - center).normalized();
            return true;
        }
    }
};

// Floor class derived from Object, represents a checkerboard pattern
class Floor : public Object {
public:
    float y;

    Floor(float y) : y(y) {}

    bool hit(const Ray& ray, float& t, Vec3D& normal) const override {
        if (std::fabs(ray.direction.y) < 1e-3) return false;
        t = -(ray.origin.y - y) / ray.direction.y;
        Vec3D hitPoint = ray.origin + ray.direction * t;
        bool isLightSquare = (static_cast<int>(std::floor(hitPoint.x) + std::floor(hitPoint.z)) % 2) == 0;
        normal = Vec3D(0, 1, 0);
        return isLightSquare;
    }
};

// Function to trace a ray and compute the brightness
float trace(const Ray& ray, const std::vector<Object*>& objects, int depth, float brightness) {
    if (depth <= 0 || brightness < 0.01f) return 0.0f;

    float closest_t = std::numeric_limits<float>::max();
    const Object* hitObject = nullptr;
    Vec3D normal;

    for (const auto& obj : objects) {
        float t;
        Vec3D tempNormal;
        if (obj->hit(ray, t, tempNormal) && t < closest_t) {
            closest_t = t;
            hitObject = obj;
            normal = tempNormal;
        }
    }

    if (!hitObject) return 0.0f;

    // If the hit object is the floor, return the brightness based on the square color
    if (dynamic_cast<const Floor*>(hitObject)) {
        return (brightness > 0.5f) ? brightness : 0.0f;
    }

    // Reflect the ray and trace the reflection
    Vec3D hitPoint = ray.origin + ray.direction * closest_t;
    Vec3D reflectedDir = ray.direction.reflect(normal);
    Ray reflectedRay(hitPoint, reflectedDir);

    // Recursively trace the reflected ray
    return 0.6f * trace(reflectedRay, objects, depth - 1, brightness * 0.6f);
}

// Function to render the scene
void renderScene(const std::vector<Object*>& objects, int width, int height) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float u = (2.0f * x) / width - 1.0f;
            float v = (2.0f * y) / height - 1.0f;
            Ray ray(Vec3D(0, 0, 0), Vec3D(u, -v, -1));
            
            float brightness = trace(ray, objects, 4, 1.0f);
            char pixel = (brightness > 0.5f) ? '#' : '.';
            std::cout << pixel;
        }
        std::cout << std::endl;
    }
}

int main() {
    // Define objects in the scene
    std::vector<Object*> objects;
    objects.push_back(new Sphere(Vec3D(-0.4, 0.4, -1.5), 0.5));
    objects.push_back(new Sphere(Vec3D(0.4, 0.5, -2.0), 0.5));
    objects.push_back(new Sphere(Vec3D(0.8, 0.3, -3.0), 0.3));
    objects.push_back(new Floor(-1));

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
