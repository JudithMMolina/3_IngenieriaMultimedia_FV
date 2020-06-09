#include "StateControles.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Juego.h>
#include <Motor2D.h>
#include <Utils.h>

StateControles::StateControles()
{
    //ctor
    reloj.restart();
    reloj2.restart();
    cont = 0;
    cont2 = 0;
    tiempoRepeticion = 0.1;
    tiempoRepeticion2 = 0.5;

    texture = new sf::Texture();
    if (!texture->loadFromFile("resources/frame1.png"))
    {
        std::cerr << "Error cargando la imagen frame1.png";
        //exit(0);
    }

    texture2 = new sf::Texture();
    if (!texture2->loadFromFile("resources/sara1.png"))
    {
        std::cerr << "Error cargando la imagen sara1.png";
        //exit(0);
    }

    textureControl = new sf::Texture();
    if (!textureControl->loadFromFile("resources/jugador1Teclas.png"))
    {
        std::cerr << "Error cargando la imagen jugador1Teclas.png";
        //exit(0);
    }

    texture2Control = new sf::Texture();
    if (!texture2Control->loadFromFile("resources/jugador2Teclas.png"))
    {
        std::cerr << "Error cargando la imagen jugador2Teclas.png";
        //exit(0);
    }

    sprite2 = new sf::Sprite();
    sprite2->setTexture(*texture2);
    sprite2->setScale(0.5,0.5);
    sprite2->setPosition(200,140);

    sprite = new sf::Sprite();
    sprite->setTexture(*texture);
    sprite->setScale(0.5,0.5);
    sprite->setPosition(180,400);

    sprite2Control = new sf::Sprite();
    sprite2Control->setTexture(*texture2Control);
    sprite2Control->setPosition(450,430);

    spriteControl = new sf::Sprite();
    spriteControl->setTexture(*textureControl);
    spriteControl->setPosition(450,150);


    gameOver = Motor2D::getDefaultText();
    gameOver->setString("CONTROLES JUGADORES");
    gameOver->setCharacterSize(40); // in pixels, not points!
    gameOver->setColor(sf::Color::White);
    gameOver->setOrigin(600/2, 300/2);
    gameOver->setPosition(700,200);

    nombreRudolf = Motor2D::getDefaultText();
    nombreRudolf->setString("RUDOLFBOT");
    nombreRudolf->setCharacterSize(18); // in pixels, not points!
    nombreRudolf->setColor(sf::Color::White);
    nombreRudolf->setPosition(220,630);

    nombreSara = Motor2D::getDefaultText();
    nombreSara->setString("SARA");
    nombreSara->setCharacterSize(18); // in pixels, not points!
    nombreSara->setColor(sf::Color::White);
    nombreSara->setPosition(200,365);

    moverseSara = Motor2D::getDefaultText();
    moverseSara->setString("MOVERSE");
    moverseSara->setCharacterSize(20); // in pixels, not points!
    moverseSara->setColor(sf::Color::White);
    moverseSara->setPosition(510,575);

    moverseRudolfbot = Motor2D::getDefaultText();
    moverseRudolfbot->setString("MOVERSE");
    moverseRudolfbot->setCharacterSize(20); // in pixels, not points!
    moverseRudolfbot->setColor(sf::Color::White);
    moverseRudolfbot->setPosition(510,300);

    dispararSara = Motor2D::getDefaultText();
    dispararSara->setString("DISPARAR");
    dispararSara->setCharacterSize(20); // in pixels, not points!
    dispararSara->setColor(sf::Color::White);
    dispararSara->setPosition(1000,590);

    dispararRudolfbot = Motor2D::getDefaultText();
    dispararRudolfbot->setString("DISPARAR");
    dispararRudolfbot->setCharacterSize(20); // in pixels, not points!
    dispararRudolfbot->setColor(sf::Color::White);
    dispararRudolfbot->setPosition(1000,310);

    cambioSara = Motor2D::getDefaultText();
    cambioSara->setString("CAMBIAR ARMA");
    cambioSara->setCharacterSize(20); // in pixels, not points!
    cambioSara->setColor(sf::Color::White);
    cambioSara->setPosition(1000,520);

    cambioRudolfbot = Motor2D::getDefaultText();
    cambioRudolfbot->setString("CAMBIAR ARMA");
    cambioRudolfbot->setCharacterSize(20); // in pixels, not points!
    cambioRudolfbot->setColor(sf::Color::White);
    cambioRudolfbot->setPosition(1000,240);

    interactuarSara = Motor2D::getDefaultText();
    interactuarSara->setString("INTERACTUAR");
    interactuarSara->setCharacterSize(20); // in pixels, not points!
    interactuarSara->setColor(sf::Color::White);
    interactuarSara->setPosition(1000,555);

    interacturarRudolfbot = Motor2D::getDefaultText();
    interacturarRudolfbot->setString("INTERACTURAR");
    interacturarRudolfbot->setCharacterSize(20); // in pixels, not points!
    interacturarRudolfbot->setColor(sf::Color::White);
    interacturarRudolfbot->setPosition(1000,275);

    music = new sf::Music();
	if (!music->openFromFile("resources/music/Hasta Mi Planeta.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/Hasta Mi Planeta.ogg";
        //exit(0);
	}
    music->play();
    music->setVolume(60);

    Motor2D::centrarView();
}

StateControles::~StateControles()
{
    //dtor
}

void StateControles::render()
{
    sf::RenderWindow *window = Juego::getInstance()->getWindow();

    window->draw(*sprite);
    window->draw(*sprite2);
    window->draw(*gameOver);
    window->draw(*nombreRudolf);
    window->draw(*nombreSara);
    window->draw(*spriteControl);
    window->draw(*sprite2Control);
    window->draw(*moverseSara);
    window->draw(*moverseRudolfbot);
    window->draw(*cambioSara);
    window->draw(*cambioRudolfbot);
    window->draw(*interactuarSara);
    window->draw(*interacturarRudolfbot);
    window->draw(*dispararSara);
    window->draw(*dispararRudolfbot);
}

void StateControles::update()
{
    sf::RenderWindow *window = Juego::getInstance()->getWindow();
    // Process events
    sf::Event event;
    //input(window, event);
    while (window->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyReleased:
            {
                //std::cout << "Se soltó una tecla" << std::endl;
                if(event.key.code == sf::Keyboard::Return) {
                    music->stop();
                    cambiarAMenu();
                }
                break;
            }
        }
    }

    // Animacion controles
    if(reloj.getElapsedTime().asSeconds()>tiempoRepeticion) {
        reloj.restart();
        sf::Texture *texture2 = new sf::Texture();
        if(cont % 2 != 0) {
            if (!texture2->loadFromFile("resources/frame2.png"))
            {
                std::cerr << "Error cargando la imagen frame2.png";
                //exit(0);
            }
            sprite->setTexture(*texture2);
            tiempoRepeticion = 0.1;
        } else {
            if (!texture2->loadFromFile("resources/frame1.png"))
            {
                std::cerr << "Error cargando la imagen frame1.png";
                //exit(0);
            }
            sprite->setTexture(*texture2);
            tiempoRepeticion = 0.5;
            cont = 0;
        }
        cont += 1;

    }
    if(reloj2.getElapsedTime().asSeconds()>tiempoRepeticion2){
        reloj2.restart();
        sf::Texture *texture3 = new sf::Texture();
        if(cont % 2 != 0){
            if (!texture3->loadFromFile("resources/sara2.png"))
            {
                std::cerr << "Error cargando la imagen sara2.png";
                //exit(0);
            }
            sprite2->setTexture(*texture3);
            tiempoRepeticion2 = 1.0;
        }else{
            if (!texture3->loadFromFile("resources/sara1.png"))
            {
                std::cerr << "Error cargando la imagen sara1.png";
                //exit(0);
            }
            sprite2->setTexture(*texture3);
            tiempoRepeticion2 = 0.2;
            cont2 = 0;
        }
        cont2 += 1;

    }
}
