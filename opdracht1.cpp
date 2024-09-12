#include <iostream>
#include <stdio.h>
#include <math.h>

int main()
{
    // Making variables for the board and circle.
    int boardWidth = 300;
    int boardHeight = 100;

    int middleX = boardWidth / 2;
    int middleY = boardHeight / 2;

    float tileWidthX = 20;
    float tileWidthY = 8;

    double outerRadius = 80.0;
    double innerRadius = 40.0;

    // character is the character that will be printed and is determined by the distance from the center of the circle and the chessboard pattern.
    int character = 0;

    char chars[] = {' ', 'L', 'N'};

    // The switcher is used to switch from blank tile to filled tile.
    int switcher = 0;
    int num;
    int num2;

    // Loop for the Y axis and switching the switcher so the board becomes a chessboard pattern.
    for (int countY = 0; countY < boardHeight; countY++)
    {
        num = floor(countY / tileWidthY);
        if (num % 2 == 0)
        {
            switcher = 1;
        }
        else
        {
            switcher = 0;
        }
        // Loop for the X axis and calculating the distance from the center of the circle so the right character can be printed.
        for (int countX = 0; countX < boardWidth; countX++)
        {
            character = 0;
            num2 = floor(countX / tileWidthX) + switcher;
            if (num2 % 2 == 0)
            {
                character = character + 1;
            }
            float pythagoras = std::sqrt((countX - middleX) * (countX - middleX) + 5 * (countY - middleY) * (countY - middleY));
            if (pythagoras <= outerRadius && pythagoras >= innerRadius)
            {
                character = character + 1;
            }

            if (character == 0)
            {
                printf("%c", chars[0]);
            }
            else if (character == 1)
            {
                printf("%c", chars[1]);
            }
            else if (character == 2)
            {
                printf("%c", chars[2]);
            }
        }
        printf("\n");
    }
    return 0;
}
