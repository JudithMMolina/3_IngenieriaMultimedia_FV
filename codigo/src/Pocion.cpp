#include "Pocion.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


Pocion::Pocion(float posX, float posY, int tipoPocion) : ObjetoMapa(posX, posY, tipoPocion)
{
    tipo = tipoPocion;
    vida = 20;
    if(tipoPocion == TIPO_POCION_MALA)
        vida *= -1;
    else if(tipoPocion == TIPO_POCION_SORPRESA)
        vida = Utils::random(-20, 30);

    string archivo = "resources/pocionBuena.png";
    if(tipoPocion != TIPO_POCION_BUENA)
        archivo = "resources/pocionSorpresa.png";

    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
    sprite->setScale(1.5, 1.5);
    //sprite->setOrigin(16/2,17/2); Comentario de relleno para la version
}

Pocion::~Pocion()
{
    //dtor
}

void Pocion::update() {

}
