#include "EnemigoFactory.h"

EnemigoFactory::EnemigoFactory()
{
    //ctor
}

EnemigoFactory::~EnemigoFactory()
{
    //dtor
}


Enemigo* EnemigoFactory::crearEnemigo(int posX, int posY, int tipoEnemigo)
{
    Enemigo *enemigoCreado;
    if(tipoEnemigo==1)
        enemigoCreado = new EnemigoExplosivo(posX, posY);
    else if(tipoEnemigo==2)
        enemigoCreado = new EnemigoAereo(posX, posY);
    else if (tipoEnemigo==3)
        enemigoCreado = new EnemigoEstatico(posX, posY);
    else if (tipoEnemigo==4)
        enemigoCreado = new EnemigoMSX(posX, posY);
    else
        int i=0;

    return enemigoCreado;
}



/*void enemigoFactory::update(enemigo *enemigoCreado)
{
    if(dynamic_cast<enemigoExplosivo*>(enemigoCreado)) {
        enemigoExplosivo *enemigoCreadoE = dynamic_cast<enemigoExplosivo*>(enemigoCreado);
    }
}*/
