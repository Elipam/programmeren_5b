// Requirements:
// 1. Copy the Vec3D, Sphere and Ray class from opdracht3 and paste it into the code editor.
// 2. Make an abstract base class Object so objects can be stored in a vector.
// 3. Come up with a way to link the tile area to the vector end.
// 4. Initialize the rays and scan the area.
// 5. Print a character for each ray that hits an object.

// Testspecs:
// 1. Test the whole program by running it and checking if the output is correct.
// 2. Change the voriabel values to see if the program still works correctly.

// Design:
// The program is designed to create a checkerboard pattern with a few spheres on it.
// The program has to depict these in 3D bij using a ray scanner.
// The program uses a vector of objects to store the objects. Which can be a floor or a sphere.
// The ray loops through the objects and checks if it hits an object. If it does, it prints a character.

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <variant>

// Define the namespace, to avoid conflicts using the st
using namespace std;
const int square = 2;

// Function to return the opposite direction of a vector outside the class, because it is not a function used on a Vec3D object
float minus2(float scalar)
{
    return -scalar;
}

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
const float zVoid = 6;
const Vec3D endPointA(-6, 3, zVoid);
const Vec3D endPointB(6, 3, zVoid);
const Vec3D endPointC(6, -3, zVoid);
const Vec3D endPointD(-6, -3, zVoid);
const int amountRaysX = 120;
const int amountRaysY = 50;

// Forward declaration of Ray class
class Ray;

// Abstract base class Object
class Object
{
public:
    Vec3D center;

    // Constructor
    Object(float x, float y, float z) : center(x, y, z) {}

    // Pure virtual methods
    virtual bool hit(Ray &ray) = 0;
    virtual Ray bounce(Ray &ray) = 0;

    // Virtual destructor
    virtual ~Object() = default;
};

// Vector of pointers to objects to use in ray and rayscanner
using VPO = vector<Object *>;

// Ray class: Represents a ray with a support vector and a direction vector
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

    float hitSomething = 0;

    void printChar()
    {
        if (hitSomething >= 2)
        {
            cout << "##";
            return;
        }
        for (const auto &obj : objects)
        {
            if (obj->hit(*this))
            {
                hitSomething++;
                Ray rayBounce = obj->bounce(*this);
                rayBounce.printChar();
            }
        }

        if (hitSomething >= 2)
        {
            cout << "##";
        }
        else if (hitSomething == 1)
        {
            cout << "++";
        }
        else
        {
            cout << "  ";
        }
    }
};

// Sphere class: Represents a sphere with a center and a radius
class Sphere : public Object
{
public:
    float radius;

    // Constructor
    Sphere(float x, float y, float z, float radius) : Object(x, y, z), radius(radius) {}

    float distFromRay(Ray const &ray) const
    {
        return ray.support.sub(center).cross(ray.direction).norm() / (ray.direction.norm());
    }

    bool hit(Ray &ray)
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

    Vec3D hitPoint(Ray &ray)
    {
        bool hit = this->hit(ray);
        if (hit == false)
        {
            cerr << "Ray does not hit the sphere.\n";
            return Vec3D(0, 0, 0);
        }
        else
        {
            Vec3D centerToSupport = ray.support.sub(center);
            // a = dir * dir
            float a = ray.direction.dot(ray.direction);
            // b = 2 * dir * (sup - center)
            float b = 2 * centerToSupport.dot(ray.direction);
            // c = (sup - center) * (sup - center) - r^2
            float c = centerToSupport.dot(centerToSupport) - radius * radius;

            float d = b * b - 4 * a * c;

            float t1 = (-b - sqrt(d)) / (2 * a);
            float t2 = (-b + sqrt(d)) / (2 * a);
            float t = t1 < t2 ? t1 : t2;
            return ray.support.add(ray.direction.mul(t));
        }
    }

    Ray bounce(Ray &ray)
    {
        Vec3D hitPoint = this->hitPoint(ray);
        Vec3D normal = hitPoint.sub(center).unit();
        Vec3D reflectedDir = ray.direction.sub(normal.mul(2 * ray.direction.dot(normal))).unit();
        Ray ray2(0, 0, ray.objects);
        ray2.direction = reflectedDir;
        ray2.support = hitPoint;
        return ray2;
    }
};

// Floor class: Represents a floor with a tile size
class Floor : public Object
{
public:
    float tileSize;
    float x, y, z;

    // Constructor
    Floor(float x, float y, float z, float tileSize) : Object(x, y, z), tileSize(tileSize) {}

    bool isEven(int num)
    {
        return num % 2 == 0;
    }

    // function to draw checkerboard pattern
    bool hit(Ray &ray)
    {
        float t = (this->y - ray.support.y) / ray.direction.y;
        Vec3D hitPoint = ray.support.add(ray.direction.mul(t));

        if (ray.direction.y >= 0 || hitPoint.z > 3)
        {
            return false;
        }

        int tileX = floor(hitPoint.x / tileSize);
        int tileZ = floor(hitPoint.z / tileSize);

        return !isEven(tileX + tileZ);
    }

    Ray bounce(Ray &ray)
    {
        float t = (this->y - ray.support.y) / ray.direction.y;
        Vec3D hitPoint = ray.support.add(ray.direction.mul(t));
        Ray ray2 = Ray(0, 0, ray.objects);
        ray.direction.z = minus2(ray.direction.z);
        ray2.direction = ray.direction;
        ray2.support = hitPoint;
        return ray2;
    };
};

class RayScanner
{
public:
    VPO objects{
        new Floor(0, 0, 0, 0.5),
        new Sphere(-1.5, 1.2, 2.0, 0.8),
        new Sphere(2.0, 0.7, 2.0, 0.3),
        new Sphere(0.5, 1.4, 2.0, 0.5)};

    // Initialize rays
    void scan()
    {
        float yStep = (endPointA.y - endPointD.y) / amountRaysY;
        float xStep = (endPointB.x - endPointA.x) / amountRaysX;
        for (float i = endPointA.y; i >= endPointC.y; i -= yStep)
        {
            for (float j = endPointA.x; j <= endPointB.x; j += xStep)
            {
                Ray ray(0, 1, objects);
                ray.direction = Vec3D(j, i, zVoid).sub(ray.support).unit();
                ray.hitSomething = 0;
                ray.printChar();
            }
            cout << "\n";
        }
    }
};

int main()
{
    RayScanner scanner;
    scanner.scan();
    return 0;
}