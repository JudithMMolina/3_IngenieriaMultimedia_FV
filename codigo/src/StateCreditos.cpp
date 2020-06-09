#include "StateCreditos.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Juego.h>
#include <Motor2D.h>
#include "Utils.h"

StateCreditos::StateCreditos()
{
    //ctor
    framesTotales = 188;
    frameActual = 1;
    creditos = true;

    tFondo = new sf::Texture();
    if(!tFondo->loadFromFile("resources/creditos/scene_00001.png"))
	{
		std::cerr << "Error cargando la imagen resources/creditos/scene_00001.png";
        //exit(0);
	}
    sFondo = new sf::Sprite();
	sFondo->setTexture(*tFondo);

	music = new sf::Music();
	if (!music->openFromFile("resources/music/creditosClover.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/creditosClover.ogg";
        //exit(0);
	}
    music->play();
    music->setVolume(200);
}

StateCreditos::~StateCreditos()
{
    //dtor
}

void StateCreditos::render()
{
    sf::RenderWindow *window = Juego::getInstance()->getWindow();
    Motor2D::centrarView();
    window->draw(*sFondo);
}

void StateCreditos::update()
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
                //std::cout << "Se soltó una tecla" << std::endl;
                if(event.key.code == sf::Keyboard::Return) {
                    creditos = false;
                    music->stop();
                    cambiarAMenu();
                }
                break;
            case sf::Event::KeyPressed:
                //std::cout << "Se pulsó una tecla" << std::endl;
                break;
        }

    }

    //Video
    std::string nameScene;
    if(frameActual <= framesTotales && creditos)
    {
        if(frameActual < 10)
        {
            nameScene = "0000" + Utils::Int_to_String(frameActual);
        }
        else if(frameActual >=10 && frameActual < 100)
        {
            nameScene = "000" + Utils::Int_to_String(frameActual);
        }
        else if(frameActual >=100 && frameActual < 1000)
        {
            nameScene = "00" + Utils::Int_to_String(frameActual);
        }
        else if(frameActual >=1000 && frameActual < 10000)
        {
            nameScene = "0" + Utils::Int_to_String(frameActual);
        }

        if(!tFondo->loadFromFile("resources/creditos/scene_" + nameScene + ".png"))
        {
            std::cerr << "Error cargando la imagen resources/creditos/scene_" + nameScene + ".png";
            //exit(0);
        }

        sFondo->setTexture(*tFondo);
        frameActual++;
    }
    //cuando acaba el video
    else if(frameActual == int(framesTotales)+1)
    {
        creditos = false;
        frameActual = 0;
        music->stop();
        cambiarAMenu();
    }
}
