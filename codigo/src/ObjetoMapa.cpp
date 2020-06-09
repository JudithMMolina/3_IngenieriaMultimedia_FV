#include <SFML/Graphics.hpp>
#include <iostream>
#include "ObjetoMapa.h"
using namespace sf;
using namespace std;


ObjetoMapa::ObjetoMapa(float posX, float posY, int tipo)
{
    //ctor
    sprite = new Sprite();
    sprite->setPosition(posX, posY);
    cogible = true;
    pintable = true;
}

ObjetoMapa::~ObjetoMapa()
{
    //dtor
}

void ObjetoMapa::update(){
    //std::cout<<"Update mapa"<<std::endl;
}
