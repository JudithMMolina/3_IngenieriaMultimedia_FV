#include "StateSuperarNivel.h"
#include "SFML/Graphics.hpp"
#include "Globales.h"
#include "Constantes.h"
#include "Motor2D.h"
#include "Juego.h"
#include "iostream"

using namespace sf;
using namespace std;

StateSuperarNivel::StateSuperarNivel()
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
    texturaFondo->loadFromFile("resources/MePaseElNivel.png");
    spriteFondo = new Sprite(*texturaFondo);

    textoSuperior1 = Motor2D::getDefaultText();
    textoSuperior1->setString("Enhorabuena!");
    textoSuperior1->setPosition(Constantes::TAMANYO_VENTANA_X/2 - textoSuperior1->getGlobalBounds().width/2, 100);

    textoSuperior2 = Motor2D::getDefaultText();
    textoSuperior2->setString("Te has pasado el nivel");
    textoSuperior2->setPosition(Constantes::TAMANYO_VENTANA_X/2 - textoSuperior2->getGlobalBounds().width/2, 140);

    textoSuperior3 = Motor2D::getDefaultText();
    textoSuperior3->setString("Obtienes:");
    textoSuperior3->setPosition(Constantes::TAMANYO_VENTANA_X/2 - textoSuperior3->getGlobalBounds().width/2, 180);


    textoInferior = Motor2D::getDefaultText();
    int contador = 0;
    if(Globales::NIVEL_AFRICA_SUPERADO)
        contador++;
    if(Globales::NIVEL_AMERICA_SUPERADO)
        contador++;
    if(Globales::NIVEL_EUROPA_SUPERADO)
        contador++;
    textoInferior->setString("Cartucho " + to_string(contador) + "/5");
    textoInferior->setPosition(Constantes::TAMANYO_VENTANA_X/2 - textoInferior->getGlobalBounds().width/2, 600);
    Motor2D::centrarView();
}

StateSuperarNivel::~StateSuperarNivel()
{
    //dtor
}

void StateSuperarNivel::update()
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
                    Juego::getInstance()->setState(State::Estados::MAPA);
                }
                break;
        }
    }
}

void StateSuperarNivel::render()
{
    Juego::getInstance()->getWindow()->draw(*spriteFondo);
    Juego::getInstance()->getWindow()->draw(*textoInferior);
    Juego::getInstance()->getWindow()->draw(*textoSuperior1);
    Juego::getInstance()->getWindow()->draw(*textoSuperior2);
    Juego::getInstance()->getWindow()->draw(*textoSuperior3);
}
