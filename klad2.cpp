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

float calcTileWidth(int center, int current) {
    float tileWidth;
    float diff = center - current;
    if (current < 0)
    {
        current = -current;
    }
    
    return tileWidth = diff * ;
}

int main()
{
    // Constant variables for board and circle dimensions
    const int boardWidth = 300;
    const int boardHeight = 100;
    const int horizon = -1;

    const int middleX = boardWidth / 2;
    const int middleY = boardHeight / 2;

    const float tileWidth = 20;
    float tileHeight = 7;

    const double outerRadius = 80.0;
    const double innerRadius = 40.0;

    // Characters to be printed
    std::array<char, 3> chars = {' ', 'L', 'N'};

    // Switcher to toggle the chessboard pattern
    bool boolX = false;
    bool boolY = false;
    bool lastBoolY = true;
    int switcher = 0;
    int num = -1;
    int lastNum;
    int count2Y = 0;
    int num2;

    // Loop for the Y axis to generate rows
    for (int i = 0; i < boardHeight; i++)
    {
        for (int j = 0; i < tileHeight; j++)
        {
            for (int k = 0; k < boardWidth; k++)
            {
                for (int l = 0; l < tileWidth; l++)
                {
                    if (i > horizon)
                    {
                        
                    }
                    {
                        /* code */
                    }
                    
                }
                
            }
            
        }
        
    }
    

    return 0;
}
