#include <iostream>
#include <stdio.h>
#include <math.h>

int main()
{
    int boardWidth = 300;
    int boardHeight = 100;

    int middleX = boardWidth / 2;
    int middleY = boardHeight / 2;

    double outerRadius = 80.0;
    double innerRadius = 40.0;

    int character = 0;

    int switcher = 0;
    int num;
    int num2;

    float tileWidthX = 20;
    float tileWidthY = 8;

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
        for (int countX = 0; countX < boardWidth; countX++)
        {
            num2 = floor(countX / tileWidthX) + switcher;
            float pythagoras = std::sqrt((countX - middleX) * (countX - middleX) + 5 * (countY - middleY) * (countY - middleY));
            if (num2 % 2 == 0)
            {
                printf("L");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
