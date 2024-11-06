#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

auto const far = 1e10;  
typedef st::vector<float> VF;
typedef st::vector<VF> VFF;

auto const pixelChars = "M ";
auto const nrOfRows = 96;                // Number of rows (Height)
auto const nrOfCols = 3 * nrOfRows;      // Number of columns (Width)
auto const aspectRatio = float(nrOfCols) / float(nrOfRows);  // Adjusted aspect ratio
auto image = VFF(nrOfRows, VF(nrOfCols, 0));  // Image matrix

class Vec3D {
public:
    float x, y, z;
    Vec3D() : x(0), y(0), z(0) {}
    Vec3D(float xIn, float yIn, float zIn) : x(xIn), y(yIn), z(zIn) {}
    Vec3D add(const Vec3D& other) const { return Vec3D(x + other.x, y + other.y, z + other.z); }
    Vec3D sub(const Vec3D& other) const { return Vec3D(x - other.x, y - other.y, z - other.z); }
    Vec3D mul(float scalar) const { return Vec3D(x * scalar, y * scalar, z * scalar); }
    float dot(const Vec3D& other) const { return x * other.x + y * other.y + z * other.z; }
    Vec3D cross(const Vec3D& other) const { return Vec3D(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }
    float norm() const { return st::sqrt(x * x + y * y + z * z); }
};

class Ray;
class Object {
protected:
    Vec3D center;
public:
    Object(float x, float y, float z) : center(x, y, z) {}
    virtual bool hit(Ray& ray) = 0;
};

typedef st::vector<Object*> VPO;

class Ray {
private:
    Vec3D support;
    Vec3D direction;
    VPO& objects;

public:
    Ray(float pixelX, float pixelY, VPO& objs)
        : support(0, 0, -3), objects(objs) {
        direction = Vec3D(pixelX, pixelY, 0).sub(support).mul(1.0 / Vec3D(pixelX, pixelY, 0).sub(support).norm());
    }

    bool scan() {
        for (auto& obj : objects) {
            if (obj->hit(*this)) {
                return true;
            }
        }
        return false;
    }

    Vec3D getSupport() const { return support; }
    Vec3D getDirection() const { return direction; }
    void setSupport(const Vec3D& newSupport) { support = newSupport; }
};

class Sphere : public Object {
private:
    float radius;

public:
    Sphere(float x, float y, float z, float r) : Object(x, y, z), radius(r) {}

    float distFromRay(const Ray& ray) const {
        Vec3D centerToSupport = center.sub(ray.getSupport());
        Vec3D crossProduct = centerToSupport.cross(ray.getDirection());
        return crossProduct.norm() / ray.getDirection().norm();
    }

    bool hit(Ray& ray) {
        float distance = distFromRay(ray);
        return distance <= radius;
    }

    // New method to apply brightness logic directly to the sphere
    void adjustBrightness(VFF& image) const {
        for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
            auto y = (nrOfRows / 2.0 - rowIndex) / nrOfRows; 
            for (auto colIndex = 0; colIndex < nrOfCols; colIndex++) {
                auto x = (colIndex - nrOfCols / 2.0) / (aspectRatio * nrOfCols);
                auto distance = sqrt(pow(x - center.x, 2) + pow(y - center.y, 2) + pow(center.z, 2));
                
                // Toggle the brightness if inside or on the sphere
                auto brightness = (distance <= radius) ? 2 : 1;
                if (brightness == 2) {
                    image[rowIndex][colIndex] = (image[rowIndex][colIndex] == 1) ? 0 : 1;
                }
            }
        }
    }
};


class Floor : public Object {
public:
    Floor(float y) : Object(0, y, 0) {}

    bool hit(Ray& ray) {
        Vec3D direction = ray.getDirection();
        Vec3D support = ray.getSupport();

        if (direction.y == 0) return false; // Parallel rays won't intersect the floor

        float t = (center.y - support.y) / direction.y; // Intersection distance
        if (t < 0) return false; // Ignore if behind the starting point

        float intersectX = support.x + direction.x * t;
        float intersectZ = support.z + direction.z * t;

        // Adjust the tile size to reduce edge distortion
        float tileWidth = 1.0;
        float tileHeight = 1.0;

        // Add a small epsilon to avoid artifacts at the edges
        bool isBlackSquare = (int(st::floor((intersectZ + 1e-5) / tileHeight)) + 
                              int(st::floor((intersectX + 1e-5) / tileWidth))) % 2 == 0;
        return isBlackSquare;
    }
};

class RayScanner {
private:
    VPO objects;
    float viewpointZ = -3.0;

public:
    RayScanner() {
        objects.push_back(new Floor(-1.0));
        objects.push_back(new Sphere(-1.5, 0.8, 2.0, 0.8));  
        objects.push_back(new Sphere(2.0, 0.3, 2.0, 0.3));  
        objects.push_back(new Sphere(0.5, 1.0, 2.0, 0.5));  
    }

    void scan() {
        for (int y = 0; y < nrOfRows; ++y) {
            for (int x = 0; x < nrOfCols; ++x) {
                float pixelX = (x - nrOfCols / 2.0f) / (nrOfCols / 2.0f) * aspectRatio;
                float pixelY = (nrOfRows / 2.0f - y) / (nrOfRows / 2.0f);
                Ray ray(pixelX, pixelY, objects);
                image[y][x] = ray.scan() ? 0 : 1;
            }
        }

        // Print the final image
        st::cout << '\n';
        for (auto rowIndex = 0; rowIndex < nrOfRows; rowIndex++) {
            for (auto colIndex = 0; colIndex < nrOfCols; colIndex++) {
                st::cout << pixelChars[int(image[rowIndex][colIndex])];
            }
            st::cout << '\n';
        }
        st::cout << '\n';
    }

    ~RayScanner() {
        for (auto obj : objects) delete obj;
    }
};

int main() {
    RayScanner scanner;
    scanner.scan();
    return 0;
}