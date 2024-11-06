#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <variant>

using namespace std;
const int square = 2;

// Vec3D class: Represents a 3D vector and its operations
class Vec3D
{
public:
    float x, y, z;

    // Constructor declaration
    Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}

    // Function to display a vector with a label
    void show(string label)
    {
        std::cout << label << "(" << x << ", " << y << ", " << z << ")\n";
    }

    // Function to display a vector property with a label
    void show(string label, float scalar)
    {
        std::cout << label << ": " << scalar << "\n";
    }

    // Function to return the opposite direction of a vector
    Vec3D minus() const
    {
        return Vec3D{x, y, z};
    }

    float minus2(float scalar)
    {
        return -scalar;
    }

    // Function to add two vectors
    Vec3D add(Vec3D const &self) const
    {
        return Vec3D{x + self.x, y + self.y, z + self.z};
    }

    // Function to subtract two vectors
    Vec3D sub(Vec3D const &other) const
    {
        return Vec3D{x - other.x, y - other.y, z - other.z};
    }

    // Function to multiply a vector by a scalar
    Vec3D mul(float scalar) const
    {
        return Vec3D{x * scalar, y * scalar, z * scalar};
    }

    // Function to divide a vector by a scalar
    Vec3D div(float scalar) const
    {
        if (scalar == 0)
        {
            cerr << "Division by zero impossible.\n";
            return Vec3D{x, y, z};
        }
        return Vec3D{x / scalar, y / scalar, z / scalar};
    }

    // Function to calculate the norm (length) of a Vec3D
    float norm() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    // Function to normalize a Vec3D (unit vector)
    Vec3D unit() const
    {
        float length = this->norm();
        if (length == 0)
        {
            cerr << "Cannot normalize a zero-length vector.\n";
            return Vec3D{x, y, z};
        }
        return div(length);
    }

    // Function to calculate the dot product of two Vec3D vectors
    float dot(Vec3D const &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    // Function to calculate the cross product of two Vec3D vectors
    Vec3D cross(Vec3D const &other) const
    {
        return Vec3D{
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
    }
};

// Global variables
float zVoid = 4;
Vec3D endPointA(-4, 2, zVoid);
Vec3D endPointB(4, 2, zVoid);
Vec3D endPointC(4, -2, zVoid);
Vec3D endPointD(-4, -2, zVoid);
int amountRaysX = 80;
int amountRaysY = 40;

// Forward declaration of Ray class
class Ray;

// Abstract base class Object
class Object
{
public:
    Vec3D center;

    // Constructor
    Object(float x, float y, float z) : center(x, y, z) {}

    // Pure virtual method
    virtual bool hit(Ray &ray) = 0;

    // Virtual destructor
    virtual ~Object() = default;
};

using VPO = vector<Object *>;

class Ray
{
public:
    Vec3D support;
    Vec3D direction;
    VPO &objects;

    // Constructor
    Ray(float xStart, float yStart, VPO &objects)
        : support(xStart, yStart, -3), direction(0, 0, 0), objects(objects) {}

    // Scan method
    bool scan()
    {
        return true;
    }

    void printChar(float curX, float curY, float stepsX, float stepsY)
    {
        bool hitSomething = false;
        for (const auto &obj : objects)
        {
            if (obj->hit(*this))
            {
                hitSomething = true;
                break;
            }
        }

        if (hitSomething)
        {
            cout << "X";
        }
        else
        {
            cout << " ";
        }
        if (curX >= stepsX)
        {
            cout << "\n";
        }
    }
};

class Sphere : public Object
{
public:
    float radius;

    Sphere(float x, float y, float z, float radius) : Object(x, y, z), radius(radius) {}

    float distFromRay(Ray const &ray) const
    {
        return ray.support.sub(center).cross(ray.direction).norm() / (ray.direction.norm());
    }

    bool hit(Ray &ray) override
    {
        if (distFromRay(ray) < radius)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Floor : public Object
{
public:
    Floor(float x, float z) : Object(x, 0, z) {}

    bool isEven(int num)
    {
        if (num % 2 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool hit(Ray &ray) override
    {
        float t = (0 - ray.support.y) / ray.direction.y;
        Vec3D hitPoint = ray.support.add(ray.direction.mul(t));
        if (isEven(floor(hitPoint.x) + floor(hitPoint.z)))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

class RayScanner
{
public:
    VPO objects{
        new Floor(1, 1),
        new Sphere(-1.5, 0.8, 2.0, 0.8),
        new Sphere(2.0, 0.3, 2.0, 0.3),
        new Sphere(0.5, 1.0, 2.0, 0.5)};
    void scan()
    {
        float yStep = (endPointA.y - endPointD.y) / amountRaysY;
        for (float i = endPointA.y; i >= endPointC.y; i += yStep)
        {
            float xStep = (endPointB.x - endPointA.x) / amountRaysX;
            for (float j = endPointA.x; j <= endPointB.x; j += xStep)
            {
                Ray ray(0, 0, objects);
                ray.direction = Vec3D(j, i, zVoid).sub(ray.support).unit();
                ray.printChar(j, i, endPointB.x, endPointC.y);
            }
        }
    }
};

int main()
{
    RayScanner scanner;
    scanner.scan();
    return 0;
}