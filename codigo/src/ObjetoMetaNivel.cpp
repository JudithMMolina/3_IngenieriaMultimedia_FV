#include "ObjetoMetaNivel.h"
#include "SFML/Graphics.hpp"
#include "Motor2D.h"
#include "iostream"

using namespace std;
using namespace sf;

ObjetoMetaNivel::ObjetoMetaNivel(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    //ctor
    string archivo = "resources/chip.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
}

ObjetoMetaNivel::~ObjetoMetaNivel()
{
    //dtor
}
