#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <variant>
#include <memory> // Voor std::unique_ptr

using namespace std;
const int square = 2;

float minus2(float scalar)
{
    return -scalar;
}

class Vec3D
{
public:
    float x, y, z;
    Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}

    void show(string label)
    {
        cout << label << "(" << x << ", " << y << ", " << z << ")\n";
    }

    Vec3D minus() const
    {
        return Vec3D{-x, -y, -z}; // Corrigeer minus() functie
    }

    Vec3D add(Vec3D const &self) const
    {
        return Vec3D{x + self.x, y + self.y, z + self.z};
    }

    Vec3D sub(Vec3D const &other) const
    {
        return Vec3D{x - other.x, y - other.y, z - other.z};
    }

    Vec3D mul(float scalar) const
    {
        return Vec3D{x * scalar, y * scalar, z * scalar};
    }

    float norm() const
    {
        return sqrt(x * x + y * y + z * z);
    }

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

    float dot(Vec3D const &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3D cross(Vec3D const &other) const
    {
        return Vec3D{
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x};
    }

    Vec3D div(float scalar) const
    {
        if (scalar == 0)
        {
            cerr << "Division by zero impossible.\n";
            return Vec3D{x, y, z};
        }
        return Vec3D{x / scalar, y / scalar, z / scalar};
    }
};

const float zVoid = 6;
const Vec3D endPointA(-6, 3, zVoid);
const Vec3D endPointB(6, 3, zVoid);
const Vec3D endPointC(6, -3, zVoid);
const Vec3D endPointD(-6, -3, zVoid);
const int amountRaysX = 120;
const int amountRaysY = 50;

class Ray;
class Object
{
public:
    Vec3D center;
    Object(float x, float y, float z) : center(x, y, z) {}
    virtual bool hit(Ray &ray) = 0;
    virtual Ray bounce(Ray &ray) = 0;
    virtual ~Object() = default;
};

using VPO = vector<unique_ptr<Object>>;

class Ray
{
public:
    Vec3D support;
    Vec3D direction;
    VPO &objects;
    float hitSomething = 0;

    Ray(float xStart, float yStart, VPO &objects)
        : support(xStart, yStart, -3), direction(0, 0, 0), objects(objects) {}

    bool scan() { return true; }

    void printChar()
    {
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
        return distFromRay(ray) < radius;
    }

    Vec3D hitPoint(Ray &ray)
    {
        bool hit = this->hit(ray);
        if (!hit)
        {
            cerr << "Ray does not hit the sphere.\n";
            return Vec3D(0, 0, 0);
        }
        else
        {
            Vec3D centerToSupport = ray.support.sub(center);
            float a = ray.direction.dot(ray.direction);
            float b = 2 * centerToSupport.dot(ray.direction);
            float c = centerToSupport.dot(centerToSupport) - radius * radius;
            float d = b * b - 4 * a * c;

            float t1 = (-b - sqrt(d)) / (2 * a);
            float t2 = (-b + sqrt(d)) / (2 * a);
            float t = t1 < t2 ? t1 : t2;
            return ray.support.add(ray.direction.mul(t));
        }
    }

    Ray bounce(Ray &ray) override
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

class Floor : public Object
{
public:
    float tileSize;
    float x, y, z;

    Floor(float x, float y, float z, float tileSize) : Object(x, y, z), tileSize(tileSize) {}

    bool isEven(int num)
    {
        return num % 2 == 0;
    }

    bool hit(Ray &ray) override
    {
        float t = (this->y - ray.support.y) / ray.direction.y;
        Vec3D hitPoint = ray.support.add(ray.direction.mul(t));
        if (ray.direction.y >= 0 || hitPoint.z > 3)
            return false;
        int tileX = floor(hitPoint.x / tileSize);
        int tileZ = floor(hitPoint.z / tileSize);
        return !isEven(tileX + tileZ);
    }

    Ray bounce(Ray &ray) override
    {
        float t = (this->y - ray.support.y) / ray.direction.y;
        Vec3D hitPoint = ray.support.add(ray.direction.mul(t));
        Ray ray2 = Ray(0, 0, ray.objects);
        ray.direction.z = minus2(ray.direction.z);
        ray2.direction = ray.direction;
        ray2.support = hitPoint;
        return ray2;
    }
};

class RayScanner
{
public:
    VPO objects;

    RayScanner()
    {
        objects.emplace_back(make_unique<Floor>(0, 0, 0, 0.5));
        objects.emplace_back(make_unique<Sphere>(-1.5, 1.2, 2.0, 0.8));
        objects.emplace_back(make_unique<Sphere>(2.0, 0.7, 2.0, 0.3));
        objects.emplace_back(make_unique<Sphere>(0.5, 1.4, 2.0, 0.5));
    }

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
