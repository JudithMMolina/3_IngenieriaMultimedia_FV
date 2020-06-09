#include "StateJuegoSuperado.h"
#include "SFML/Graphics.hpp"
#include "Motor2D.h"
#include "Juego.h"
#include "Constantes.h"

using namespace sf;

StateJuegoSuperado::StateJuegoSuperado()
{
    //ctor
    music = new sf::Music();
	if (!music->openFromFile("resources/music/Mapa.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/Mapa.ogg";
        //exit(0);
	}
    music->play();

    texturaFondo = new Texture();
    texturaFondo->loadFromFile("resources/endgame.png");
    spriteFondo = new Sprite(*texturaFondo);
    spriteFondo->setScale(0.75, 0.75);

    texturaMascara = new Texture();
    texturaMascara->loadFromFile("resources/mascara_negra.png");
    spriteMascara = new Sprite(*texturaMascara);

    texto = Motor2D::getDefaultText();
    texto->setString("Enhorabuena, has vencido a MSX\nEl planeta vuelve a estar a salvo");
    texto->setPosition(Constantes::TAMANYO_VENTANA_X/2 - texto->getGlobalBounds().width /2, Constantes::TAMANYO_VENTANA_Y/2 - texto->getGlobalBounds().height /2);
    Juego::getInstance()->getView()->setCenter(Constantes::TAMANYO_VENTANA_X / 2, Constantes::TAMANYO_VENTANA_Y / 2);
}

StateJuegoSuperado::~StateJuegoSuperado()
{
    //dtor
}


void StateJuegoSuperado::update()
{
    RenderWindow *window = Juego::getInstance()->getWindow();

    window->setKeyRepeatEnabled(false);

    Event event;

    while (window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                window->close();
                break;
            case Event::KeyPressed:
                //std::cout << "Se pulsó una tecla" << std::endl;
                break;

            case Event::KeyReleased:
                //cout << "Estamos en key released" << endl;
                if(event.key.code == Keyboard::Return) {
                    music->stop();
                    Juego::getInstance()->setState(State::Estados::MENU);
                }
                break;
        }
    }

}


void StateJuegoSuperado::render()
{
    Juego::getInstance()->getWindow()->draw(*spriteFondo);
    Juego::getInstance()->getWindow()->draw(*spriteMascara);
    Juego::getInstance()->getWindow()->draw(*texto);
}
