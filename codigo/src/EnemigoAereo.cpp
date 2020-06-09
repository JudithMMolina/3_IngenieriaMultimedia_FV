#include "EnemigoAereo.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>



EnemigoAereo::EnemigoAereo(int posX, int posY)
{
    direccion_enemigo2 = 3;
    distancia = 0.f;
    dentroDelRadio = false;
    vida=40;
    item=0;
    bajarVidaJugador = false;

    sf::Texture *tex2 = new Texture();
    if (!tex2->loadFromFile("resources/enemigo_volador.png"))
    {
        std::cerr << "Error cargando la imagen enemigo_volador.png";
        exit(0);
    }

    sprite = new sf::Sprite(*tex2);
    sprite->setOrigin(32/2,32/1.2);
    sprite->setTextureRect(sf::IntRect(0, 6, 34, 32));
    sprite->scale(1.5,1.5);
    sprite->setPosition(posX, posY);

    enemigoVivo=true;
    atacar=false;

    siguientePosX = sprite->getPosition().x;
    siguientePosY = sprite->getPosition().y;
}

EnemigoAereo::~EnemigoAereo()
{
    //dtor
}

void EnemigoAereo::render(sf::RenderWindow *window)
{
    //if(enemigoVivo==true)
    /*
        for(int i=0; i<rectangulos.size(); i++)
        {
            window->draw(rectangulos.at(i));
        }
        for(int i=0; i<soluciones.size(); i++)
            window->draw(soluciones.at(i));
    */
        window->draw(*sprite);
}



void EnemigoAereo::update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa)
{
    float distancia1=0.0;
    float distancia2=0.0;
    mapa2 = mapa->getMapaCalorParedes();
    int cols = mapa->getMapTileWidth();
    int rows = mapa->getMapTileHeight();

    if(vida <= 0)
        enemigoVivo = false;
    if(enemigoVivo==true)
    {
        distancia1=pow((pow((jugador1->getBody()->getPosition().x+32-sprite->getPosition().x),2)+pow(jugador1->getBody()->getPosition().y+32-sprite->getPosition().y,2)),0.5);
        distancia2=pow((pow((jugador2->getBody()->getPosition().x+32-sprite->getPosition().x),2)+pow(jugador2->getBody()->getPosition().y+32-sprite->getPosition().y,2)),0.5);

        if(distancia1<=distancia2)
            distancia=distancia1;
        else
            distancia=distancia2;

        if(distancia<500)
        {
            if(sprite->getGlobalBounds().intersects(jugador1->getBody()->getGlobalBounds()) || sprite->getGlobalBounds().intersects(jugador2->getBody()->getGlobalBounds()) )
            {
                atacar = true;
                if(distancia1<=distancia2)
                    bajarVidaJugador1(jugador1);
                else
                    bajarVidaJugador2(jugador2);
            }
            else{
                atacar = false;
            }

            if(dentroDelRadio==false)
            {
                dentroDelRadio=true;
                animacionClock.restart();
            }
            else
            {
                if(distancia1<=distancia2)
                    calcularDireccion(jugador1->getBody()->getPosition().x+32,jugador1->getBody()->getPosition().y+32,mapa,rows,cols); // Metodo que calcula la direccion del enemigo
                else
                    calcularDireccion(jugador2->getBody()->getPosition().x+32,jugador2->getBody()->getPosition().y+32,mapa,rows,cols); // Metodo que calcula la direccion del enemigo

                animacionMovimiento();
            }
        }
        else
        {
            dentroDelRadio=false;
            animacionReposo();
        }
    }
    if(recibirDanyo==true && tiempoEnRojo.getElapsedTime().asMilliseconds()>300.0)
        recibirDanyo=false;
}


void EnemigoAereo::animacionReposo()
{
    if(recibirDanyo==false){
        if(animacionReposoReloj.getElapsedTime().asSeconds()<0.1)
            sprite->setTextureRect(sf::IntRect(1, 122, 32, 35));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<0.2)
            sprite->setTextureRect(sf::IntRect(34, 122, 32, 35));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<0.3)
            sprite->setTextureRect(sf::IntRect(67, 122, 32, 35));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<0.4)
            sprite->setTextureRect(sf::IntRect(100, 122, 32, 35));
        else
            animacionReposoReloj.restart();
    }else{
        if(animacionReposoReloj.getElapsedTime().asSeconds()<0.1)
            sprite->setTextureRect(sf::IntRect(1+193, 122, 32, 35));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<0.2)
            sprite->setTextureRect(sf::IntRect(34+193, 122, 32, 35));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<0.3)
            sprite->setTextureRect(sf::IntRect(67+193, 122, 32, 35));
        else if(animacionReposoReloj.getElapsedTime().asSeconds()<0.4)
            sprite->setTextureRect(sf::IntRect(100+193, 122, 32, 35));
        else
            animacionReposoReloj.restart();
    }
}


/* Se calcula la direccion en la que va a moverse el enemigo */
void EnemigoAereo::calcularDireccion(float jugX, float jugY, Mapa *mapa, int filas, int columnas)
{
    float vectorX = 0.0;
    float vectorY = 0.0;
    float vMagnitud = 0.0;
    float divisorUnitario = 0.0;
    float angleRads = 0.0;
    float angleDegs = 0.0;
    float PI = 3.14159265359;

    vectorX=jugX-sprite->getPosition().x;
    vectorY=jugY-sprite->getPosition().y;

    vMagnitud= (vectorX*vectorX)+(vectorY*vectorY);
    divisorUnitario=sqrt(vMagnitud);

    angleRads = atan2(-vectorY, vectorX);
    angleDegs = angleRads * 180 / PI;


    if(angleDegs >=-45 && angleDegs <= 150){ //entre 0 y 180 grados                 REVISAR !!!!!!
        if(angleDegs >=-45 && angleDegs <= 30){ // entre 0 y 90 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(1, 122, 32, 35));
            else
                sprite->setTextureRect(sf::IntRect(1+193, 122, 32, 35));
            direccion_enemigo2 = 1;
        }else{ //entre 90 y 180 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(1, 85, 32, 32));
            else
                sprite->setTextureRect(sf::IntRect(1+193, 85, 32, 32));
            direccion_enemigo2 = 2;
        }
    }else{
         if(angleDegs > -135 && angleDegs <= 150){ // entre 0 y 90 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(1, 6, 32, 32));
            else
                sprite->setTextureRect(sf::IntRect(1+193, 6, 32, 32));
            direccion_enemigo2 = 3;
        }else{ //entre 90 y 180 grados
            if(recibirDanyo==false)
                sprite->setTextureRect(sf::IntRect(1, 43, 32, 35));
            else
                sprite->setTextureRect(sf::IntRect(1+193, 43, 32, 35));
            direccion_enemigo2 = 4;
        }
    }
    if(distancia<500 && atacar == false)
        movimientoEnemigo(sprite->getPosition().x, sprite->getPosition().y, jugX, jugY, VELOCIDAD_ENEMIGO_3,  filas,  columnas);
}



/* Se anima el movimiento del pajaro cambiando sprites */
void EnemigoAereo::animacionMovimiento()
{
    if(animacionClock.getElapsedTime().asSeconds()<0.4)
    {
        if(recibirDanyo==false){
            if(direccion_enemigo2 == 1){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1, 122, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34, 122, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67, 122, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(100, 122, 32, 35));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1, 122, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(100, 159, 32, 39));
                }
            }
            if(direccion_enemigo2 == 2){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1, 85, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34, 85, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67, 85, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(100, 85, 32, 32));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1, 85, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(67, 159, 32, 39));
                }
            }
            if(direccion_enemigo2 == 3){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1, 6, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34, 6, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67, 6, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(100, 6, 32, 32));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1, 6, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(1, 160, 32, 38));
                }
            }
            if(direccion_enemigo2 == 4){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1, 43, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34, 43, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67, 43, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(100, 43, 32, 35));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1, 43, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(34, 159, 32, 39));
                }
            }
        }else{ // aquiiiiiiii
            if(direccion_enemigo2 == 1){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1+193, 122, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34+193, 122, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67+193, 122, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(100+193, 122, 32, 35));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1+193, 122, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(100+193, 159, 32, 39));
                }
            }
            if(direccion_enemigo2 == 2){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1+193, 85, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34+193, 85, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67+193, 85, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(100+193, 85, 32, 32));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1+193, 85, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(67+193, 159, 32, 39));
                }
            }
            if(direccion_enemigo2 == 3){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1+193, 6, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34+193, 6, 32, 32));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67+193, 6, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(100+193, 6, 32, 32));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1+193, 6, 32, 32));
                    else
                        sprite->setTextureRect(sf::IntRect(1+193, 160, 32, 38));
                }
            }
            if(direccion_enemigo2 == 4){
                if(atacar == false)
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.1)
                        sprite->setTextureRect(sf::IntRect(1+193, 43, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(34+193, 43, 32, 35));
                    else if(animacionClock.getElapsedTime().asSeconds()<0.3)
                        sprite->setTextureRect(sf::IntRect(67+193, 43, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(100+193, 43, 32, 35));
                }
                else
                {
                    if(animacionClock.getElapsedTime().asSeconds()<0.2)
                        sprite->setTextureRect(sf::IntRect(1+193, 43, 32, 35));
                    else
                        sprite->setTextureRect(sf::IntRect(34+193, 159, 32, 39));
                }
            }
        }
    }

    if(animacionClock.getElapsedTime().asSeconds() >= 0.4)
        animacionClock.restart();
    if(recibirDanyo==true && tiempoEnRojo.getElapsedTime().asMilliseconds()>400.0)
        recibirDanyo=false;

}

/* Controla el ataque a el jugador */
void EnemigoAereo::bajarVidaJugador1(Jugador *jugador1)
{
    if(animacionClock.getElapsedTime().asSeconds()<0.1)
        bajarVidaJugador=false;
    if(animacionClock.getElapsedTime().asSeconds()>0.3 && bajarVidaJugador==false){
        if(atacar == true){
            //std::cout << "Vida del jugador 1 reducida POR EL AEREO" << std::endl;
            bajarVidaJugador = true;
            jugador1->modificarVida(-DANYO_ENEMIGO_3);
        }
    }

}

void EnemigoAereo::bajarVidaJugador2(Jugador *jugador2)
{
    if(animacionClock.getElapsedTime().asSeconds()<0.1)
        bajarVidaJugador=false;
    if(animacionClock.getElapsedTime().asSeconds()>0.3 && bajarVidaJugador==false){
        if(atacar == true){
            //std::cout << "Vida del jugador 2 reducida POR EL AEREO" << std::endl;
            bajarVidaJugador = true;
            jugador2->modificarVida(-DANYO_ENEMIGO_3);
        }
    }

}
