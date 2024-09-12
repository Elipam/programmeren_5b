#include <iostream>
#include <cmath>
#include <array>

int main()
{
    // Constants for board and circle dimensions
    const int boardWidth = 300;
    const int boardHeight = 100;

    const int middleX = boardWidth / 2;
    const int middleY = boardHeight / 2;

    const float tileWidthX = 20;
    const float tileWidthY = 8;

    const double outerRadius = 80.0;
    const double innerRadius = 40.0;

    // Characters to be printed
    std::array<char, 3> chars = {' ', 'L', 'N'};

    // Switcher to toggle the chessboard pattern
    int switcher = 0;
    int num;
    int num2;

    // Loop for the Y axis to generate rows
    for (int countY = 0; countY < boardHeight; countY++)
    {
        num = std::floor(countY / tileWidthY);
        switcher = (num % 2 == 0) ? 1 : 0;

        // Loop for the X axis to generate columns
        for (int countX = 0; countX < boardWidth; countX++)
        {
            int character = 0;
            num2 = std::floor(countX / tileWidthX) + switcher;
            if (num2 % 2 == 0)
            {
                character += 1;
            }

            // Calculate the distance from the center using Pythagoras
            float pythagoras = std::sqrt((countX - middleX) * (countX - middleX) + 5 * (countY - middleY) * (countY - middleY));
            if (pythagoras <= outerRadius && pythagoras >= innerRadius)
            {
                character += 1;
            }

            // Output the corresponding character
            std::cout << chars[character];
        }
        // Newline at the end of each row
        std::cout << std::endl;
    }

    return 0;
}
