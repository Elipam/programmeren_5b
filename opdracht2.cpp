#include <iostream>
#include <cmath>
#include <string>

// Define the Vec3D struct
struct Vec3D {
    float x, y, z;
};

// Function to create a Vec3D
Vec3D vec3D(float x, float y, float z) {
    return Vec3D{x, y, z};
}

// Function to display a Vec3D with a label
void show(std::string label, Vec3D const &self) {
    std::cout << label << ": (" << self.x << ", " << self.y << ", " << self.z << ")\n";
}