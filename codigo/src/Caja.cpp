#include "Caja.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Caja::Caja(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    string archivo = "resources/caja.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
}

Caja::~Caja()
{
    //dtor
}
