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

    // Function to return the opposite direction of a vector
    Vec3D minus () const {
        return Vec3D{x, y, z};
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

class Object {
    public:
        Vec3D center;

        Object(float x, float y, float z) : center(x, y, z) {}

        virtual bool hit(Ray &ray) = 0;
};

class Ray {
    public:
        Vec3D support;
        Vec3D direction;
        using VPO = std::vector<Object*>;
        VPO objects;

        // Constructor
        Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir) : support(xSup, ySup, zSup), direction(xDir, yDir, zDir) {}

        Ray(float xStart, float yStart, VPO objects) {

        }

        bool scan (){

        }
};

class Sphere : public Object {
    public:
        float radius;

        Sphere(float x, float y, float z, float radius) : Object(x, y, z), radius(radius) {}

    bool hit(Ray &ray) {
        
    }
        
};

class Floor : public Object {
    bool hit(Ray &ray) {
        
    }
}

class RayScanner {
    
}