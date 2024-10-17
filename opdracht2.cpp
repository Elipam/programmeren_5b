// Requirements:
// 1. Define a struct type Vec3D to represent a 3D vector with x, y, and z components.
// 2. Implement the following functions:
//    - Vec3D vec3D(float x, float y, float z) to create and return a Vec3D.
//    - void show(std::string label, Vec3D const &self) to print a Vec3D with a label.
//    - void show(std::string label, float scalar) to print a float scalar with a label.
//    - void show() to print a newline.
//    - Vec3D minus(Vec3D const &self) to return a vector pointing in the opposite direction.
//    - Vec3D add(Vec3D const &self, Vec3D const &other) to return the sum of two vectors.
//    - Vec3D sub(Vec3D const &self, Vec3D const &other) to return the difference of two vectors.
//    - Vec3D mul(Vec3D const &self, float scalar) to return the product of a vector and a scalar.
//    - Vec3D div(Vec3D const &self, float scalar) to return the quotient of a vector and a scalar.
//    - float norm(Vec3D const &self) to return the length (magnitude) of the vector.
//    - Vec3D unit(Vec3D const &self) to return a unit vector in the same direction.
//    - float dot(Vec3D const &self, Vec3D const &other) to return the dot product of two vectors.
//    - Vec3D cross(Vec3D const &self, Vec3D const &other) to return the cross product of two vectors.
// 3. The main function should test all these functions according to the specified tests.

// Testspecs:
// 1. Create vectors and check if their components are correctly set.
// 2. Test vector addition, subtraction, multiplication, and division.
// 3. Test the calculation of the norm, unit vector, dot product, and cross product.
// 4. Ensure that the show functions display the correct information.
// 5. Test the behavior when dividing by zero for safety.

// Design:
// The program is designed to implement basic vector operations in a structured manner.
// The use of a struct for Vec3D allows the representation of 3D vectors with x, y, and z components.
// Functions are designed to operate on Vec3D instances and perform mathematical operations.
// Scalar functions are overloaded to print both vectors and float values.

#include <iostream>
#include <cmath>
#include <string>

// Define the Vec3D struct
struct Vec3D {
    float x, y, z;
};

// Function to create a Vec3D
Vec3D makeVec3D(float x, float y, float z) {
    return Vec3D{x, y, z};
}

// Function to display a Vec3D with a label
void show(std::string label, Vec3D const &self) {
    std::cout << label << "(" << self.x << ", " << self.y << ", " << self.z << ")\n";
}

// Function to display a float scalar with a label
void show(std::string label, float scalar) {
    std::cout << label << ": " << scalar << "\n";
}

// Function to print a newline
void show() {
    std::cout << "\n";
}

// Function to return the opposite direction of a Vec3D
Vec3D minus(Vec3D const &self) {
    return Vec3D{-self.x, -self.y, -self.z};
}

// Function to add two Vec3D vectors
Vec3D add(Vec3D const &self, Vec3D const &other) {
    return Vec3D{self.x + other.x, self.y + other.y, self.z + other.z};
}

// Function to subtract two Vec3D vectors
Vec3D sub(Vec3D const &self, Vec3D const &other) {
    return Vec3D{self.x - other.x, self.y - other.y, self.z - other.z};
}

// Function to multiply a Vec3D by a scalar
Vec3D mul(Vec3D const &self, float scalar) {
    return Vec3D{self.x * scalar, self.y * scalar, self.z * scalar};
}

// Function to divide a Vec3D by a scalar
Vec3D div(Vec3D const &self, float scalar) {
    if (scalar == 0.0f) {
        std::cerr << "Error: Division by zero.\n";
        return self; // Return original vector as fallback
    }
    return Vec3D{self.x / scalar, self.y / scalar, self.z / scalar};
}

// Function to calculate the norm (length) of a Vec3D
float norm(Vec3D const &self) {
    return std::sqrt(self.x * self.x + self.y * self.y + self.z * self.z);
}

// Function to normalize a Vec3D (unit vector)
Vec3D unit(Vec3D const &self) {
    float length = norm(self);
    if (length == 0.0f) {
        std::cerr << "Error: Cannot normalize a zero-length vector.\n";
        return self; // Return original vector as fallback
    }
    return div(self, length);
}

// Function to calculate the dot product of two Vec3D vectors
float dot(Vec3D const &self, Vec3D const &other) {
    return self.x * other.x + self.y * other.y + self.z * other.z;
}

// Function to calculate the cross product of two Vec3D vectors
Vec3D cross(Vec3D const &self, Vec3D const &other) {
    return Vec3D{
        self.y * other.z - self.z * other.y,
        self.z * other.x - self.x * other.z,
        self.x * other.y - self.y * other.x
    };
}

// Main function to test all implemented functions
int main() {
    // Create test vectors
    Vec3D v1 = makeVec3D(1.0f, 2.0f, 3.0f);
    Vec3D v2 = makeVec3D(4.0f, 5.0f, 6.0f);

    // Test vector creation and show function
    show("Vector v1", v1);
    show("Vector v2", v2);
    show();

    // Test vector addition
    Vec3D v_add = add(v1, v2);
    show("v1 + v2", v_add);

    // Test vector subtraction
    Vec3D v_sub = sub(v1, v2);
    show("v1 - v2", v_sub);

    // Test scalar multiplication
    Vec3D v_mul = mul(v1, 2.0f);
    show("v1 * 2.0", v_mul);

    // Test scalar division
    Vec3D v_div = div(v1, 2.0f);
    show("v1 / 2.0", v_div);

    // Test vector negation
    Vec3D v_neg = minus(v1);
    show("-v1", v_neg);

    // Test norm calculation
    float v1_norm = norm(v1);
    show("Norm of v1", v1_norm);

    // Test unit vector calculation
    Vec3D v1_unit = unit(v1);
    show("Unit vector of v1", v1_unit);

    // Test dot product calculation
    float v_dot = dot(v1, v2);
    show("Dot product of v1 and v2", v_dot);

    // Test cross product calculation
    Vec3D v_cross = cross(v1, v2);
    show("Cross product of v1 and v2", v_cross);

    // End of tests
    show();
    return 0;
}
