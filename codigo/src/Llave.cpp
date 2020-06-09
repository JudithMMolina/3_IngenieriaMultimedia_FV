#include "Llave.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



Llave::Llave(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    //ctor
    string archivo = "resources/llave.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
}

Llave::~Llave()
{
    //dtor
}
