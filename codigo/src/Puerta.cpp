#include "Puerta.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



Puerta::Puerta(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    //ctor
    string archivo = "resources/puerta.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
        cout<<"Se ha creado una puerta"<<endl;
    //sprite->setPosition(700,350);
    sprite->setOrigin(32/2,64/2);
    if(tipo == 2) sprite->setScale(-1,1);
    abrible = false;
    abierta = false;
    tipoLocal = tipo;
    cout<<"Tipo: " << tipoLocal;
}

Puerta::~Puerta()
{
    //dtor
}

void Puerta::abrir(){
    if(!abierta){
        if(tipoLocal == 1) sprite->move(-30,0);
        else if (tipoLocal == 2) sprite->move(30,0);
        abrible = false;
        abierta = true;
    }
}
