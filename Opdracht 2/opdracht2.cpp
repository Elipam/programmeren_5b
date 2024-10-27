// Requirements:
// 1. Define a struct type Vec3D to represent a 3D vector with x, y, and z components.
// 2. Implement the following functions:
//    - Vec3D vec3D(float x, float y, float z) to create and return a Vec3D.
//    - void show(std::string label, Vec3D const &self) to print a vector with the label.
//    - void show(std::string label, float scalar) to print a scalar with the label.
//    - void show() to print a newline.
//    - Vec3D minus(Vec3D const &self) to return a vector pointing in the opposite direction.
//    - Vec3D add(Vec3D const &self, Vec3D const &self2) to return the sum of two vectors.
//    - Vec3D sub(Vec3D const &self, Vec3D const &self2) to return the difference of two vectors.
//    - Vec3D mul(Vec3D const &self, float scalar) to return the product of a vector and a scalar.
//    - Vec3D div(Vec3D const &self, float scalar) to return the quotient of a vector and a scalar.
//    - float norm(Vec3D const &self) to return the length of the vector.
//    - Vec3D unit(Vec3D const &self) to return vector with length 1 in the same direction.
//    - float dot(Vec3D const &self, Vec3D const &self2) to return the dot product of two vectors.
//    - Vec3D cross(Vec3D const &self, Vec3D const &self2) to return the cross product of two vectors.
// 3. The main function should test all these functions according to the specified tests.

// Testspecs:
// 1. Test if the show functions display the correct information.
// 2. Test vector addition, subtraction, multiplication,, dot product and division by calculating the answer.
// 3. Test the calculation of the norm and unit vector by using the norm on the unit vector.
// 4. Test th cross product by comparing it to a cross product calculator.
// 5. Test the behavior when dividing by zero.

// Design:
// The program is designed to by using simple math functions to calculate the properties of a 3D vector.
// A struct is used to define the vector, because it is a simple way to store the x, y and z components.
// The function definitions were already given in the assignment, so I only had to implement them and add the necessary code.
// Ruling out division by zero is done by checking if the scalar is zero before dividing.

#include <iostream>
#include <cmath>
#include <string>

namespace st = std;
const int square = 2;

// Define the vector
struct Vec3D {float x, y, z;};

// Function to create a vector
 Vec3D vec3D (float x, float y, float z) {
    return Vec3D{x, y, z};
}

// Function to display a vector with a label
void show (st::string label, Vec3D const &self) {
    std::cout << label << "(" << self.x << ", " << self.y << ", " << self.z << ")\n";
}

// Function to display a vector property with a label
void show (st::string label, float scalar)  {
    std::cout << label << ": " << scalar << "\n";
}

// Function to print a newline
void show () {
    std::cout << "\n";
}

// Function to return the opposite direction of a vector
Vec3D minus (Vec3D const &self) {
    return Vec3D{-self.x, -self.y, -self.z};
}

// Function to add two vectors
Vec3D add (Vec3D const &self, Vec3D const &self2) {
    return Vec3D{self.x + self2.x, self.y + self2.y, self.z + self2.z};
}

// Function to subtract two vectors
Vec3D sub (Vec3D const &self, Vec3D const &self2) {
    return Vec3D{self.x - self2.x, self.y - self2.y, self.z - self2.z};
}

// Function to multiply a vector by a scalar
Vec3D mul (Vec3D const &self, float scalar) {
    return Vec3D{self.x * scalar, self.y * scalar, self.z * scalar};
}

// Function to divide a vector by a scalar
Vec3D div (Vec3D const &self, float scalar) {
    if (scalar == 0) {
        std::cerr << "Error: Division by zero impossible.\n";
        return self;
    }
    return Vec3D{self.x / scalar, self.y / scalar, self.z / scalar};
}

// Function to calculate the norm (length) of a Vec3D
float norm (Vec3D const &self) {
    return st::sqrt(pow(self.x, square) + pow(self.y, square) + pow(self.z, square));
}

// Function to normalize a Vec3D (unit vector)
Vec3D unit (Vec3D const &self) {
    float length = norm(self);
    if (length == 0) {
        std::cerr << "Error: Cannot normalize a zero-length vector.\n";
        return self;
    }
    return div(self, length);
}

// Function to calculate the dot product of two Vec3D vectors
float dot (Vec3D const &self, Vec3D const &self2) {
    return self.x * self2.x + self.y * self2.y + self.z * self2.z;
}

// Function to calculate the cross product of two Vec3D vectors
Vec3D cross (Vec3D const &self, Vec3D const &self2) {
    return Vec3D{
        self.y * self2.z - self.z * self2.y,
        self.z * self2.x - self.x * self2.z,
        self.x * self2.y - self.y * self2.x
    };
}

int main () {
    // Create test vectors
    Vec3D v1 = vec3D(1.0f, 2.0f, 3.0f);
    Vec3D v2 = vec3D(4.0f, 5.0f, 6.0f);
    Vec3D testv1 = vec3D(1.0f, 3.0f, 4.0f);
    Vec3D testv2 = vec3D(2.0f, 7.0f, -5.0f);

    // Test vector creation and show functions
    show("Vector v1", v1);
    show("Vector v2", v2);

    float multiplier = 2.0;
    show("Multiplier", multiplier);

    show();

    // Test vector opposite 
    Vec3D minus_v1 = minus(v1);
    show("minus_v1 = -v1", minus_v1);

    // Test vector addition
    Vec3D v_add = add(v1, v2);
    show("v_add = v1 + v2", v_add);

    // Test vector subtraction
    Vec3D v_sub = sub(v1, v2);
    show("v_sub = v1 - v2", v_sub);

    // Test scalar multiplication
    Vec3D v_mul = mul(v1, multiplier);
    show("v_mul = v1 * 2.0", v_mul);

    // Test scalar division
    Vec3D v_div = div(v1, multiplier);
    show("v_div = v1 / 2.0", v_div);

    Vec3D v_div_zero = div(v1, 0);
    show("v_div_zero = v1 / 0", v_div_zero);

    Vec3D v_unit = unit(v1);
    show("v_unit = Unit vector of v1", v_unit);

    // Test norm calculation and unit vector
    float v_norm = norm(v_unit);
    show("Length of v_unit", v_norm);

    // Test dot product calculation
    float v_dot = dot(v1, v2);
    show("v_dot = Dot product of v1 and v2", v_dot);

    // Test cross product calculation
    Vec3D v_cross = cross(testv1, testv2);
    show("v_cross = Cross product of v1 and v2", v_cross);
}