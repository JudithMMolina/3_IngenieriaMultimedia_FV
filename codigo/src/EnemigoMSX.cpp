#include "EnemigoMSX.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#define iBolas 5
#define ancho 1280
#define alto 720
const float EnemigoMSX::VELOCIDAD_BOLAS_MSX = 14;

EnemigoMSX::EnemigoMSX(int w,int h)
{
    vida=400;
    enemigoVivo=true;
    item=0;

    if (!texture.loadFromFile("resources/msx_evolucion1.png"))
        exit(0);
    sprite = new sf::Sprite(texture);
    sprite->setOrigin(46/2,46/2);
    sprite->setPosition(w , h);
    sprite->setTextureRect(sf::IntRect(17, 13, 46, 46));
    sprite->scale(2,2);


    if (!texBolaHielo.loadFromFile("resources/roca_hielo.png"))
        exit(0);

    if (!texSuperficie.loadFromFile("resources/superficie.png"))
        exit(0);

    if (!texExplosion.loadFromFile("resources/explosion.png"))
        exit(0);

   for(int i=0; i<iBolas; i++)
   {
        bolaHielo = sf::Sprite(texBolaHielo);
        bolaHielo.setScale(1.5,1.5);
        bolaHielo.setOrigin(23/2 , 23/2);
        bolaHielo.setTextureRect(sf::IntRect(4, 2, 23, 23));
        bolasHielo.push_back(bolaHielo);

        superficie = sf::Sprite(texSuperficie);
        superficie.setOrigin(64/2 , 44/2);
        superficie.setTextureRect(sf::IntRect(1,9,64,44));
        superficie.setPosition(-100 , -100);
        superficies.push_back(superficie);

        centroBolaHielo.setSize(sf::Vector2f(2,2));
        centroBolaHielo.setOrigin(1,1);
        centroBolaHielo.setPosition(bolaHielo.getPosition().x , bolaHielo.getPosition().y - 10);

        bolasCentro.push_back(centroBolaHielo);
   }

   for(int i=0; i<iBolas; i++)
   {
       explosionPosX.push_back(-1);
       explosionPosY.push_back(-1);
   }

    resetearRelojExplosion = false;
    resetearRelojExplosion = false;
    resetearRelojExplosion2 = false;
    resetearRelojExplosion3 = false;
    resetearRelojExplosion4 = false;
    resetearRelojExplosion5 = false;
    regenerarSuperf = false;

    resetPositionBall();

   Clock explosionClock;
   Clock explosionClock2;
   Clock explosionClock3;
   Clock explosionClock4;
   Clock explosionClock5;

    resetPositionBall();


    explosion.setTexture(texExplosion);
    explosion.setOrigin(32/2 , 37/2);
    explosion.scale(2.5 , 2.5);
    explosion.setTextureRect(sf::IntRect(22, 0, 32, 37));
    explosion.setPosition(-10,-10);


    explosion2.setTexture(texExplosion);
    explosion2.setOrigin(32/2 , 37/2);
    explosion2.scale(2.5 , 2.5);
    explosion2.setTextureRect(sf::IntRect(22, 0, 32, 37));
    explosion2.setPosition(-10,-10);


    explosion3.setTexture(texExplosion);
    explosion3.setOrigin(32/2 , 37/2);
    explosion3.scale(2.5 , 2.5);
    explosion3.setTextureRect(sf::IntRect(22, 0, 32, 37));
    explosion3.setPosition(-10,-10);


    explosion4.setTexture(texExplosion);
    explosion4.setOrigin(32/2 , 37/2);
    explosion4.scale(2.5 , 2.5);
    explosion4.setTextureRect(sf::IntRect(22, 0, 32, 37));
    explosion4.setPosition(-10,-10);


    explosion5.setTexture(texExplosion);
    explosion5.setOrigin(32/2 , 37/2);
    explosion5.scale(2.5 , 2.5);
    explosion5.setTextureRect(sf::IntRect(22, 0, 32, 37));
    explosion5.setPosition(-10,-10);

    vecBolaSuperfX = 0.0;
    vecBolaSuperfY = 0.0;
    vecMagBolaSuperf = 0.0;
    divVecBolaSuperf = 0.0;
    angleRads = 0.0;
    angleDegs = 0.0;
    PI = 3.14159265359;
    empezarMovimiento = false;

    spawnEnemigos.restart();
    generarEnemigos=0;
}

EnemigoMSX::~EnemigoMSX()
{
    //dtor
}

void EnemigoMSX::render(sf::RenderWindow *window)
{
    if(enemigoVivo==true){
        window->draw(*sprite);
        window->draw(explosion);
        window->draw(explosion2);
        window->draw(explosion3);
        window->draw(explosion4);
        window->draw(explosion5);
        for(int i=0; i<bolasHielo.size(); i++)
        {
            window->draw(bolasHielo[i]);
        }
        for(int i=0; i<superficies.size(); i++)
        {
            window->draw(superficies[i]);
        }

        pintarVida(window);
    }
}


void EnemigoMSX::pintarVida(sf::RenderWindow *window){
    RectangleShape *VidaBarraMarco = new RectangleShape();
    VidaBarraMarco->setSize(Vector2f(400/3.0, 8));
    VidaBarraMarco->setPosition(sprite->getPosition().x-70, sprite->getPosition().y -70);
    VidaBarraMarco->setFillColor(Color(128, 128, 128, 170));
    VidaBarraMarco->setOutlineColor(Color(0, 0, 0, 255));
    VidaBarraMarco->setOutlineThickness(2);
    window->draw(*VidaBarraMarco);
    VidaBarraMarco = NULL;
    delete VidaBarraMarco;


    //Juego::getInstance()->getWindow()->draw(*VidaBarra);
    RectangleShape *VidaBarra = new RectangleShape();
    VidaBarra->setSize(Vector2f(vida/3.0, 8));
    VidaBarra->setPosition(sprite->getPosition().x-70, sprite->getPosition().y -70);
    VidaBarra->setFillColor(Color(255, 0, 0, 255));
    window->draw(*VidaBarra);
    VidaBarra = NULL;
    delete VidaBarra;
}

void EnemigoMSX::resetPositionBall()
{
    float salto = ancho/iBolas;
    float salto2 = 0;
    for(int i=0; i<iBolas; i++)
   {
        salto2 = salto2 + salto;
        bolasHielo[i].setPosition(salto2 - (ancho/iBolas)/2, -400);
        std::cout << salto2 << std::endl;
   }
}


void EnemigoMSX::resetPositionBall(int bola)
{
    float salto = ancho/iBolas;
    float salto2 = 0;
    for(int i=0; i<iBolas; i++)
   {
        salto2 = salto2 + salto;
        if( i == bola)
        {
            bolasHielo[i].setPosition(salto2 - (ancho/iBolas)/2, -400);
        }
   }
}


void EnemigoMSX::resetPositionSuperf(int superf)
{
    superficies[superf].setPosition(-100, -100);
}


void EnemigoMSX::calculPositionSuperf()
{
    float salto = ancho/iBolas;
    float salto2 = 0;
    for(int i=0; i<iBolas; i++)
    {
        float posicionFinalY = 0;
        if(i == 2)
        {
            posicionFinalY = rand() % 200 + 100;
            if(posicionFinalY >=150)
                posicionFinalY = rand() % 100 + 450;
        }
        else
        {
            posicionFinalY = rand() % 400 + 100;
        }
        salto2 = salto2 + salto;
        superficies[i].setPosition(salto2 - (ancho/iBolas)/2 , posicionFinalY);


        /*una vez hemos calculado la superficie calculamos su vecotr unitario a la roca*/
        vecBolaSuperfX=superficies[i].getPosition().x-bolasHielo[i].getPosition().x;
        vecBolaSuperfY=superficies[i].getPosition().y-bolasHielo[i].getPosition().y;

        vecMagBolaSuperf= (vecBolaSuperfX*vecBolaSuperfX)+(vecBolaSuperfY*vecBolaSuperfY);
        divVecBolaSuperf=sqrt(vecMagBolaSuperf);


        angleRads = atan2(-vecBolaSuperfY, vecBolaSuperfX);
        angleDegs = angleRads * 180 / PI;

        unitarioX.push_back(vecBolaSuperfX/divVecBolaSuperf);
        unitarioY.push_back(vecBolaSuperfY/divVecBolaSuperf);
    }
    empezarMovimiento = true;
}


void EnemigoMSX::movimientoBolaHielo(Jugador *jugador1, Jugador *jugador2)
{
    for(int i=0; i<bolasHielo.size() && i<superficies.size(); i++)
    {
        bolasCentro[i].setPosition(bolasHielo[i].getPosition().x , bolasHielo[i].getPosition().y);

        if(superficies[i].getPosition().x != -100 )
        {
            bolasHielo[i].setPosition(bolasHielo[i].getPosition().x + unitarioX[i] * VELOCIDAD_BOLAS_MSX,
                                    bolasHielo[i].getPosition().y + unitarioY[i] * VELOCIDAD_BOLAS_MSX);
        }
        bolasHielo[i].setRotation(bolasHielo[i].getRotation()+0.1);

        if(bolasCentro[i].getGlobalBounds().intersects(superficies[i].getGlobalBounds()))
        {
        if(superficies[i].getGlobalBounds().intersects( jugador1->getBody()->getGlobalBounds() ) )
        {
            jugador1->modificarVida(-20);
        }
        if(superficies[i].getGlobalBounds().intersects( jugador2->getBody()->getGlobalBounds() ) )
        {
            jugador2->modificarVida(-20);
        }

            explosionPosX[i] = superficies[i].getPosition().x;
            explosionPosY[i] = superficies[i].getPosition().y;
            resetPositionSuperf(i);
            resetPositionBall(i);
        }
    }
}



void EnemigoMSX::update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa)
{
    if(vida==0)
        enemigoVivo=false;

    if(enemigoVivo==true)
    {
        fasesEnemigo();
        if(animacionClock.getElapsedTime().asSeconds()>7 && animacionClock.getElapsedTime().asSeconds()<8)
        {
            if(regenerarSuperf == false)
            {
                calculPositionSuperf();
                regenerarSuperf = true;
            }
            sprite->setOrigin(86/2,86/2);
            sprite->setTextureRect(sf::IntRect(14, 247, 86, 86));
        }
        // animacion
        if(animacionClock.getElapsedTime().asSeconds()>8)
        {
            sprite->setOrigin(46/2,46/2);
            sprite->setTextureRect(sf::IntRect(17, 13, 46, 46));

            animacionClock.restart();

            regenerarSuperf = false;
        }
        animarDanyo();
    }

    if(empezarMovimiento == true)
        movimientoBolaHielo(jugador1,jugador2);

    animarBola();
}


void EnemigoMSX::fasesEnemigo(){
    if(spawnEnemigos.getElapsedTime().asSeconds()>15 && vida>0){
        spawnEnemigos.restart();
        if(vida>=350)
            generarEnemigos=1;
        else if(vida>=250)
            generarEnemigos=2;
        else if(vida>=100)
            generarEnemigos=3;
        else
            generarEnemigos=4;
        cout << "vida: " << vida << endl;
    }else{
        generarEnemigos=0;
    }
}

void EnemigoMSX::animarDanyo(){
    if(recibirDanyo==true && tiempoEnRojo.getElapsedTime().asMilliseconds()<300.0 && (animacionClock.getElapsedTime().asSeconds()<7 || animacionClock.getElapsedTime().asSeconds()>8)){
        if(tiempoEnRojo.getElapsedTime().asMilliseconds()<150.0)
            sprite->setTextureRect(sf::IntRect(136, 13, 46, 46));
        else
            sprite->setTextureRect(sf::IntRect(194, 13, 46, 46));
    }else if (animacionClock.getElapsedTime().asSeconds()<7 || animacionClock.getElapsedTime().asSeconds()>8){
        recibirDanyo=false;
        sprite->setTextureRect(sf::IntRect(17, 13, 46, 46));
    }
}


void EnemigoMSX::animarBola(){
    if(explosionPosY[0] != -1.0)
    {
        if(resetearRelojExplosion == false)
        {
            explosionClock.restart();
            resetearRelojExplosion = true;
            explosion.setPosition(explosionPosX[0],explosionPosY[0] - 30);
        }

        if(explosionClock.getElapsedTime().asSeconds() < 0.1)
            explosion.setTextureRect(sf::IntRect(11, 0, 32, 37));
        else if(explosionClock.getElapsedTime().asSeconds() < 0.2)
            explosion.setTextureRect(sf::IntRect(141, 0, 32, 37));
        else if(explosionClock.getElapsedTime().asSeconds() < 0.3)
            explosion.setTextureRect(sf::IntRect(176, 0, 32, 37));
        else if(explosionClock.getElapsedTime().asSeconds() < 0.4)
            explosion.setTextureRect(sf::IntRect(214, 0, 32, 37));
        else if(explosionClock.getElapsedTime().asSeconds() < 0.5)
            explosion.setTextureRect(sf::IntRect(254, 0, 32, 37));
        else if(explosionClock.getElapsedTime().asSeconds() < 0.6)
            explosion.setTextureRect(sf::IntRect(296, 0, 32, 37));
        else if(explosionClock.getElapsedTime().asSeconds() < 0.7)
            explosion.setTextureRect(sf::IntRect(332, 0, 32, 37));
        else
        {
            explosionPosX[0] = -1.0;
            explosionPosY[0] = -1.0;
            resetearRelojExplosion = false;
            explosionClock.restart();
            explosion.setPosition(-100,-100);
        }
    }
    if(explosionPosY[1] != -1.0)
    {
        if(resetearRelojExplosion2 == false)
        {
            explosionClock2.restart();
            resetearRelojExplosion2 = true;
            explosion2.setPosition(explosionPosX[1],explosionPosY[1] - 30);

            std::cout << explosionPosX[1] << std::endl;
        }
        if(explosionClock2.getElapsedTime().asSeconds() < 0.1)
            explosion2.setTextureRect(sf::IntRect(11, 0, 32, 37));
        else if(explosionClock2.getElapsedTime().asSeconds() < 0.2)
            explosion2.setTextureRect(sf::IntRect(141, 0, 32, 37));
        else if(explosionClock2.getElapsedTime().asSeconds() < 0.3)
            explosion2.setTextureRect(sf::IntRect(176, 0, 32, 37));
        else if(explosionClock2.getElapsedTime().asSeconds() < 0.4)
            explosion2.setTextureRect(sf::IntRect(214, 0, 32, 37));
        else if(explosionClock2.getElapsedTime().asSeconds() < 0.5)
            explosion2.setTextureRect(sf::IntRect(254, 0, 32, 37));
        else if(explosionClock2.getElapsedTime().asSeconds() < 0.6)
            explosion2.setTextureRect(sf::IntRect(296, 0, 32, 37));
        else if(explosionClock2.getElapsedTime().asSeconds() < 0.7)
            explosion2.setTextureRect(sf::IntRect(332, 0, 32, 37));
        else
        {
            explosionPosX[1] = -1.0;
            explosionPosY[1] = -1.0;
            resetearRelojExplosion2 = false;
            explosionClock2.restart();
            explosion2.setPosition(-10,-10);
        }
    }

    if(explosionPosY[2] != -1.0)
    {
        if(resetearRelojExplosion3 == false)
        {
            explosionClock3.restart();
            resetearRelojExplosion3 = true;
            explosion3.setPosition(explosionPosX[2],explosionPosY[2] - 30);

            std::cout << explosionPosX[1] << std::endl;
        }
        if(explosionClock3.getElapsedTime().asSeconds() < 0.1)
            explosion3.setTextureRect(sf::IntRect(11, 0, 32, 37));
        else if(explosionClock3.getElapsedTime().asSeconds() < 0.2)
            explosion3.setTextureRect(sf::IntRect(141, 0, 32, 37));
        else if(explosionClock3.getElapsedTime().asSeconds() < 0.3)
            explosion3.setTextureRect(sf::IntRect(176, 0, 32, 37));
        else if(explosionClock3.getElapsedTime().asSeconds() < 0.4)
            explosion3.setTextureRect(sf::IntRect(214, 0, 32, 37));
        else if(explosionClock3.getElapsedTime().asSeconds() < 0.5)
            explosion3.setTextureRect(sf::IntRect(254, 0, 32, 37));
        else if(explosionClock3.getElapsedTime().asSeconds() < 0.6)
            explosion3.setTextureRect(sf::IntRect(296, 0, 32, 37));
        else if(explosionClock3.getElapsedTime().asSeconds() < 0.7)
            explosion3.setTextureRect(sf::IntRect(332, 0, 32, 37));
        else
        {
            explosionPosX[2] = -1.0;
            explosionPosY[2] = -1.0;
            resetearRelojExplosion3 = false;
            explosionClock3.restart();
            explosion3.setPosition(-10,-10);
        }
    }

    if(explosionPosY[3] != -1.0)
    {
        if(resetearRelojExplosion4 == false)
        {
            explosionClock4.restart();
            resetearRelojExplosion4 = true;
            explosion4.setPosition(explosionPosX[3],explosionPosY[3] - 30);

            std::cout << explosionPosX[1] << std::endl;
        }
        if(explosionClock4.getElapsedTime().asSeconds() < 0.1)
            explosion4.setTextureRect(sf::IntRect(11, 0, 32, 37));
        else if(explosionClock4.getElapsedTime().asSeconds() < 0.2)
            explosion4.setTextureRect(sf::IntRect(141, 0, 32, 37));
        else if(explosionClock4.getElapsedTime().asSeconds() < 0.3)
            explosion4.setTextureRect(sf::IntRect(176, 0, 32, 37));
        else if(explosionClock4.getElapsedTime().asSeconds() < 0.4)
            explosion4.setTextureRect(sf::IntRect(214, 0, 32, 37));
        else if(explosionClock4.getElapsedTime().asSeconds() < 0.5)
            explosion4.setTextureRect(sf::IntRect(254, 0, 32, 37));
        else if(explosionClock4.getElapsedTime().asSeconds() < 0.6)
            explosion4.setTextureRect(sf::IntRect(296, 0, 32, 37));
        else if(explosionClock4.getElapsedTime().asSeconds() < 0.7)
            explosion4.setTextureRect(sf::IntRect(332, 0, 32, 37));
        else
        {
            explosionPosX[3] = -1.0;
            explosionPosY[3] = -1.0;
            resetearRelojExplosion4 = false;
            explosionClock4.restart();
            explosion4.setPosition(-10,-10);
        }
    }

    if(explosionPosY[4] != -1.0)
    {
        if(resetearRelojExplosion5 == false)
        {
            explosionClock5.restart();
            resetearRelojExplosion5 = true;
            explosion5.setPosition(explosionPosX[4],explosionPosY[4] - 30);

            std::cout << explosionPosX[1] << std::endl;
        }
        if(explosionClock5.getElapsedTime().asSeconds() < 0.1)
            explosion5.setTextureRect(sf::IntRect(11, 0, 32, 37));
        else if(explosionClock5.getElapsedTime().asSeconds() < 0.2)
            explosion5.setTextureRect(sf::IntRect(141, 0, 32, 37));
        else if(explosionClock5.getElapsedTime().asSeconds() < 0.3)
            explosion5.setTextureRect(sf::IntRect(176, 0, 32, 37));
        else if(explosionClock5.getElapsedTime().asSeconds() < 0.4)
            explosion5.setTextureRect(sf::IntRect(214, 0, 32, 37));
        else if(explosionClock5.getElapsedTime().asSeconds() < 0.5)
            explosion5.setTextureRect(sf::IntRect(254, 0, 32, 37));
        else if(explosionClock5.getElapsedTime().asSeconds() < 0.6)
            explosion5.setTextureRect(sf::IntRect(296, 0, 32, 37));
        else if(explosionClock5.getElapsedTime().asSeconds() < 0.7)
            explosion5.setTextureRect(sf::IntRect(332, 0, 32, 37));
        else
        {
            explosionPosX[4] = -1.0;
            explosionPosY[4] = -1.0;
            resetearRelojExplosion5 = false;
            explosionClock5.restart();
            explosion5.setPosition(-10,-10);
        }
    }
}




