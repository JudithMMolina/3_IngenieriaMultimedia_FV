#include "StateGameOver.h"
//#include "StateMenu.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Juego.h>
#include <Motor2D.h>

#include <Juego.h>
#include <Constantes.h>

StateGameOver::StateGameOver()
{
    tFondo = new sf::Texture();
    if(!tFondo->loadFromFile("resources/screen_gameOver.png"))
	{
		std::cerr << "Error cargando la imagen resources/screen_gameOver.png";
        //exit(0);
	}
	sFondo = new sf::Sprite();
	sFondo->setTexture(*tFondo);

	music = new sf::Music();
	if (!music->openFromFile("resources/music/game over.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/game over.ogg";
        //exit(0);
	}
    music->play();
    music->setVolume(60);

    //Pongo la view en el inicio de nuevo
    Juego *juego = Juego::getInstance();
    juego->getView()->setCenter(Constantes::TAMANYO_VENTANA_X/2.f, Constantes::TAMANYO_VENTANA_Y/2.f);
    juego->getWindow()->setView(*(juego->getView()));
    //ctor
}

StateGameOver::~StateGameOver()
{
    //dtor
}


void StateGameOver::render()
{
    sf::RenderWindow *window = Juego::getInstance()->getWindow();
    //window->setView(NULL);
    window->draw(*sFondo);
}

void StateGameOver::update()
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
                    music->stop();
                    cambiarAMapa();
                }
                break;
            case sf::Event::KeyPressed:
                //std::cout << "Se pulsó una tecla" << std::endl;
                break;
        }

    }
}
