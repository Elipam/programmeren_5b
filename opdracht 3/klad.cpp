// Requirements:
// 1. Copy the Vec3D class from opdracht2 and paste it into the code editor.
// 2. Make a ray class that has a support vector and a direction vector.
// 3. Make a sphere class that has a center, a radius and is able to calculate the intersection point of a ray with the sphere.
// 4. Make a main function that creates a list of spheres and a list of rays and tests each ray against each sphere.

// Testspecs:
// 1. Test if the copied Vec3D class works correctly.
// 2. Test if the ray class works correctly. by making

// Design:
// The program is designed to by using simple math functions to calculate the properties of a 3D vector.
// A struct is used to define the vector, because it is a simple way to store the x, y and z components.
// The function definitions were already given in the assignment, so I only had to implement them and add the necessary code.
// Ruling out division by zero is done by checking if the scalar is zero before dividing.

#include <iostream>
#include <cmath>
#include <vector>

namespace st = std;
const int square = 2;

// Vec3D class: Represents a 3D vector and its operations
class Vec3D {
    public:
        float x, y, z;

        // Constructor declaration
        Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}


    // Function to display a vector with a label
    void show (st::string label) {
        std::cout << label << "(" << x << ", " << y << ", " << z << ")\n";
    }

    // Function to display a vector property with a label
    void show (st::string label, float scalar)  {
        std::cout << label << ": " << scalar << "\n";
    }

    // Function to print a newline
    void show () {
        std::cout << "\n";
    }

    // Function to return the opposite direction of a vector
    Vec3D minus (Vec3D const &self) {
        return Vec3D{-self.x, -self.y, -self.z};
    }

    float minus2 (float scalar) {
        return -scalar;
    }

    // Function to add two vectors
    Vec3D add (Vec3D const &self) const {
        return Vec3D{x + self.x, y + self.y, z + self.z};
    }

    // Function to subtract two vectors
    Vec3D sub (Vec3D const &other) const {
        return Vec3D{x - other.x, y - other.y, z - other.z};
    }

    // Function to multiply a vector by a scalar
    Vec3D mul (float scalar) const {
        return Vec3D{x * scalar, y * scalar, z * scalar};
    }

    // Function to divide a vector by a scalar
    Vec3D div (float scalar) const {
        if (scalar == 0) {
            st::cerr << "Division by zero impossible.\n";
            return Vec3D{x, y, z};
        }
        return Vec3D{x / scalar, y / scalar, z / scalar};
    }

    // Function to calculate the norm (length) of a Vec3D
    float norm () const {
        return st::sqrt(x * x + y * y + z * z);
    }

    // Function to normalize a Vec3D (unit vector)
    Vec3D unit () const{
        float length = this->norm();
        if (length == 0) {
            st::cerr << "Cannot normalize a zero-length vector.\n";
            return Vec3D{x, y, z};
        }
        return div(length);
    }

    // Function to calculate the dot product of two Vec3D vectors
    float dot (Vec3D const &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Function to calculate the cross product of two Vec3D vectors
    Vec3D cross (Vec3D const &other) const {
        return Vec3D{
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        };
    }
};

// Ray class: Represents a ray with a support vector and a direction vector
class Ray {
    public:
        Vec3D support;
        Vec3D direction;

        // Constructor
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir) : support(xSup, ySup, zSup), direction(xDir, yDir, zDir) {}
};

// 
class Sphere {
    public:
        Vec3D center;
        float radius;
        // Constructor
        Sphere(float x, float y, float z, float radius) : center(x, y, z), radius(radius) {}

    // Closest distance from the ray to the sphere center, but not the angle
    float distFromRay (Ray const &ray) const {
        return ray.support.sub(center).cross(ray.direction).norm();
    }

    // Check if the ray hits the sphere
    bool hit (Ray const &ray) const{
        return distFromRay(ray) < radius;
    }

    Vec3D hitPoint(const Ray& ray) const {
        Vec3D centerToSupport = ray.support.sub(center);
        float a = ray.direction.dot(ray.direction);
        float b = 2 * centerToSupport.dot(ray.direction);
        float c = centerToSupport.dot(centerToSupport) - radius * radius;

        float d = b * b - 4 * a * c;
        if (d < 0) {
            return Vec3D(0, 0, 0);  
        }

        float t1 = (-b - sqrt(d)) / (2 * a);
        float t2 = (-b + sqrt(d)) / (2 * a);
        st::cout << "t1: " << t1 << ", t2: " << t2 << "\n";
        float t = t1 < t2 ? t1 : t2;
        return ray.support.add(ray.direction.unit().mul(t));
    }
};

int main()
{
    Vec3D v1(1, 2, 3);
    Vec3D v2(4, 5, 6);
    Vec3D v3 = v1.sub(v2);
    v3.show("v1 - v2 = ");
    Vec3D v4 = v1.div(2);
    v4.show("v1 / 2 = ");
    Vec3D v5 = v1.unit();
    v5.show("unit vector of v1 = ", v5.norm());
    Vec3D v6 = v1.cross(v2);
    v6.show("v1 cross v2 = ");

    Sphere testSphere(0, 0, 0, 2);
    Ray testRay(-3, -3, -3, 2, 2, 1);
    testSphere.hitPoint(testRay).show("hit point: ");

    int far = 1000;
    // Create a vector of Sphere objects
    std::vector<Sphere> spheres = {
        Sphere(-0.4, 0.23, -1, 0.4),
        Sphere(0.4, 0.4, -1.2, 0.3),
        Sphere(0.7, -0.15, -1.5, 0.2)
    };

    // Create a vector of Ray objects
    std::vector<Ray> rays = {
        Ray(-far, 0.23, -1, far, 0, 0),
        Ray(0.4, -far, -1.2, 0, far, 0),
        Ray(0.7, -0.15, -far, 0, 0, far)
    };
    // Test each ray against each sphere
    for (size_t i = 0; i < rays.size(); ++i) {
        const Ray ray = rays[i];
        for (size_t j = 0; j < spheres.size(); ++j) {
            const Sphere sphere = spheres[j];
            if (sphere.hit(ray)) {
                st::cout << "Ray " << i << " hits Sphere " << j << ", ";
                Vec3D intersect = sphere.hitPoint(ray);
                intersect.show("hit point:");
            }
        }
    }

}
