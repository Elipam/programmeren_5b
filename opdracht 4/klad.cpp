#include <iostream>
#include <cmath>
#include <vector>
#include <array>

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

// Forward declaration of Ray class
class Ray;

// Abstract base class Object
class Object {
public:
    Vec3D center;

    // Constructor
    Object(float x, float y, float z) : center(x, y, z) {}

    // Pure virtual method
    virtual bool hit(Ray& ray) = 0;

    // Virtual destructor
    virtual ~Object() = default;
};

// VPO definition
using VPO = std::vector<Object*>;

// Extended Ray class
class Ray {
public:
    Vec3D support;
    Vec3D direction;
    VPO& objects;

    // Constructor
    Ray(float xStart, float yStart, VPO& objects)
        : support(xStart, yStart, 0), direction(0, 0, 0), objects(objects) {}

    // Scan method
    bool scan() {
        return true;
    }
};

class Sphere : public Object {
    public:
        float radius;

        Sphere(float x, float y, float z, float radius) : Object(x, y, z), radius(radius) {}

    bool hit(Ray &ray) {
        return true;
    }
        
};

class Floor : public Object {
    bool hit(Ray &ray) {
        return true;
    }
};

class RayScanner {
    
};

int main()
{
    // Constant variables for board and circle dimensions
    const int boardWidth = 300;
    const int boardHeight = 100;

    const int middleX = boardWidth / 2;
    const int middleY = boardHeight / 2;

    const float tileWidthX = 20;
    const float horizon = 50;

    const double outerRadius = 80.0;
    const double innerRadius = 40.0;

    // Characters to be printed
    std::array<char, 3> chars = {' ', 'L', 'N'};

    // Switcher to toggle the chessboard pattern
    float tileHeight = 1;
    int switcher = 0;
    int lastSwitcher = 1;
    int count2Y = 0;
    int num;
    int num2;

    // Loop for the Y axis to generate rows
    for (int countY = 0; countY < boardHeight; countY++)
    {
        num = std::floor(countY / tileHeight);
        switcher = (num % 2 == 0) ? 1 : 0;

        // tileHeight begint 1
        // switch tile height = 1
        // 

        // Loop for the X axis to generate columns
        for (int countX = 0; countX < boardWidth; countX++)
        {
            int character = 0;
            num2 = std::floor(countX / tileWidthX) + switcher;
            if (num2 % 2 == 0 && countY > horizon)
            {
                character += 1;
            }

            // Calculate the distance from the center using Pythagoras
            float pythagoras = std::sqrt((countX - middleX) * (countX - middleX) + 7 * (countY - middleY) * (countY - middleY));
            if (pythagoras <= outerRadius && pythagoras >= innerRadius)
            {
                character += 1;
            }

            // Output the corresponding character
            std::cout << chars[character];
        }
        // Newline at the end of each row
        std::cout << std::endl;
    }

    return 0;
}