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
    void show (st::string label, Vec3D const &self) {
        std::cout << label << "(" << self.x << ", " << self.y << ", " << self.z << ")\n";
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

    // Function to add two vectors
    Vec3D add (Vec3D const &self, Vec3D const &self2) {
        return Vec3D{self.x + self2.x, self.y + self2.y, self.z + self2.z};
    }

    // Function to subtract two vectors
    Vec3D sub (Vec3D const &self, Vec3D const &self2) {
        return Vec3D{self.x - self2.x, self.y - self2.y, self.z - self2.z};
    }

    // Function to multiply a vector by a scalar
    Vec3D mul (Vec3D const &self, float scalar) {
        return Vec3D{self.x * scalar, self.y * scalar, self.z * scalar};
    }

    // Function to divide a vector by a scalar
    Vec3D div (Vec3D const &self, float scalar) {
        if (scalar == 0) {
            std::cerr << "Division by zero impossible.\n";
            return self;
        }
        return Vec3D{self.x / scalar, self.y / scalar, self.z / scalar};
    }

    // Function to calculate the norm (length) of a Vec3D
    float norm (Vec3D const &self) {
        return st::sqrt(pow(self.x, square) + pow(self.y, square) + pow(self.z, square));
    }

    // Function to normalize a Vec3D (unit vector)
    Vec3D unit (Vec3D const &self) {
        float length = norm(self);
        if (length == 0) {
            std::cerr << "Cannot normalize a zero-length vector.\n";
            return self;
        }
        return div(self, length);
    }

    // Function to calculate the dot product of two Vec3D vectors
    float dot (Vec3D const &self, Vec3D const &self2) {
        return self.x * self2.x + self.y * self2.y + self.z * self2.z;
    }

    // Function to calculate the cross product of two Vec3D vectors
    Vec3D cross (Vec3D const &self, Vec3D const &self2) {
        return Vec3D{
            self.y * self2.z - self.z * self2.y,
            self.z * self2.x - self.x * self2.z,
            self.x * self2.y - self.y * self2.x
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

    float distFromRay (Ray const &ray) {
    return ray.support.sub (center) .cross (ray.direction) .norm ();
    }


    bool hit (Ray const &ray) const{};

    Vec3D hitPoint (Ray const &ray) const{};
};

int main()
{
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
}
