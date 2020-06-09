#ifndef MOTOR2D_H
#define MOTOR2D_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Motor2D
{
    public:
        static Text* getDefaultText();
        static Texture* getTextureFromFile(string);
        static Texture* capturarPantalla();
        static void centrarView();
        static FloatRect getViewRect();

    protected:

    private:
};

#endif // MOTOR2D_H
