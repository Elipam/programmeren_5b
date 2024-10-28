#include <iostream>
#include <cmath>

// Ray class: Represents a ray with a support vector and a direction vector
class Ray public: Vec3D{
public:
    Vec3D support;
    Vec3D direction;
    float xSup, ySup, zSup, xDir, yDir, zDir;

    // Constructor
    Ray(float xSup, float ySup, float zSup, float xDir, float yDir, float zDir){}
};