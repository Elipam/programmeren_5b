#include <iostream>
#include <cmath> // Voor de sqrt() functie

int main()
{
    // Grootte van het raster
    const int width = 350;  // Breedte van het raster
    const int height = 100; // Hoogte van het raster

    // Middelpunt van de cirkel
    const int centerX = width / 2;
    const int centerY = height / 2;

    // Straal van de buitenste en binnenste cirkel (voor het gat)
    const double outerRadius = 80.0; // Straal van de buitenste cirkel
    const double innerRadius = 40.0; // Straal van het gat

    // Doorloop elk punt in het raster
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Bereken de afstand van het punt (x, y) tot het middelpunt (centerX, centerY)
            double distance = std::sqrt((x - centerX) * (x - centerX) + 5 * (y - centerY) * (y - centerY));

            // Controleer of het punt binnen de buitenste straal valt en buiten de binnenste straal
            if (distance <= outerRadius && distance >= innerRadius)
            {
                std::cout << "L"; // Print een "L" als het punt binnen de cirkel ligt
            }
            else
            {
                std::cout << " "; // Print een spatie als het punt buiten de cirkel of binnen het gat ligt
            }
        }
        std::cout << std::endl; // Ga naar de volgende regel na het voltooien van een rij
    }

    return 0;
}
