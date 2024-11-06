// Requirements:
// Draw a chessboard pattern with 2 nested loops.
// Draw a circle with a hole in the middle on the chessboard pattern.
// Make sure the right characters are printed on the right places.
// Put constant numbers in constant variables.

// Testspecs:
// Testing the chessboard pattern by removing the cirkel character counter
// Testing the chessboard pattern by removing the chessboard pattern counter
// Testing the combination of the chessboard pattern and the cirkel character counter if they are working together

// Design:
// For the making of the chessboard, I chose to just print characters and calibrate to make the sqaures the right size.
// To make the squares alter form black to white on the vertical axis, I used a switcher that toggles between 0 and 1.
// For the circle, I used the Pythagorean theorem to calculate the distance from the center of the circle.

#include <iostream>
#include <cmath>
#include <array>

using namespace std;

int main()
{
    // Constant variables for board and circle dimensions
    const int boardWidth = 300;
    const int boardHeight = 100;

    const int middleX = boardWidth / 2;
    const int middleY = boardHeight / 2;

    const float tileWidthX = 20;
    const float tileHeight = 7;

    const double outerRadius = 80.0;
    const double innerRadius = 40.0;

    // Characters to be printed
    array<char, 3> chars = {' ', 'L', 'N'};

    // Switcher to toggle the chessboard pattern
    int switcher = 0;
    int num;
    int num2;

    // Loop for the Y axis to generate rows
    for (int countY = 0; countY < boardHeight; countY++)
    {
        num = floor(countY / tileHeight);
        switcher = (num % 2 == 0) ? 1 : 0;

        // Loop for the X axis to generate columns
        for (int countX = 0; countX < boardWidth; countX++)
        {
            int character = 0;
            num2 = floor(countX / tileWidthX) + switcher;
            if (num2 % 2 == 0)
            {
                character += 1;
            }

            // Calculate the distance from the center using Pythagoras
            float pythagoras = sqrt((countX - middleX) * (countX - middleX) + 7 * (countY - middleY) * (countY - middleY));
            if (pythagoras <= outerRadius && pythagoras >= innerRadius)
            {
                character += 1;
            }

            // Output the corresponding character
            cout << chars[character];
        }
        // Newline at the end of each row
        cout << endl;
    }

    return 0;
}
