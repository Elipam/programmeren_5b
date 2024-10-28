#include <iostream>
#include <cmath>

class Vec3D {
    public:
        float x, y, z;
        
        // Constructor (voorheen vec3D functie)
        Vec3D(float x, float y, float z);

        // Methods (voorheen losse functies)
        Vec3D add(Vec3D other);
        Vec3D subtract(Vec3D other);
        float dot(Vec3D other);
        Vec3D cross(Vec3D other);
        Vec3D scale(float scalar);
        void print();
};