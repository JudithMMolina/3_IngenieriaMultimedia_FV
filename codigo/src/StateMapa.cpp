#include "StateMapa.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Juego.h>
#include <Motor2D.h>
#include <Constantes.h>
#include <Globales.h>

using namespace sf;

StateMapa::StateMapa()
{
    //ctor
    posAmerica.x = 280;
    posAmerica.y = 330;
    posAfrica.x = 655;
    posAfrica.y = 310;
    posEuropa.x = 700;
    posEuropa.y = 150;
    posAsia.x = 920;
    posAsia.y = 190;
    posOceania.x = 1130;
    posOceania.y = 500;
    posAntartida.x = 600;
    posAntartida.y = 675;
    posIrAMenu.x = 10;
    posIrAMenu.y = 10;

    posicionesMapa[0] = posAmerica;
    posicionesMapa[1] = posAfrica;
    posicionesMapa[2] = posEuropa;
    posicionesMapa[3] = posAsia;
    posicionesMapa[4] = posOceania;
    posicionesMapa[5] = posAntartida;
    posicionesMapa[6] = posIrAMenu;

    tFondo = new sf::Texture();
    if(!tFondo->loadFromFile("resources/screen_mapa.png"))
    {
        std::cerr << "Error cargando la imagen screen_mapa.png";
        //exit(0);
    }
    sFondo = new sf::Sprite();
    sFondo->setTexture(*tFondo);

    selector = new sf::CircleShape();
    selector->setRadius(10.f);
    selector->setFillColor(sf::Color::Cyan);
    selector->setOutlineColor(sf::Color::Blue);
    selector->setOutlineThickness(5);
    //El selector empieza en la posicion de America
    Vector2i vectorPosActual = posicionesMapa[posActual];
    selector->setPosition(vectorPosActual.x, vectorPosActual.y);

    music = new sf::Music();
	if (!music->openFromFile("resources/music/Mapa.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/Mapa.ogg";
        //exit(0);
	}
    music->play();

    texturaEstrella = new Texture();
    texturaEstrella->loadFromFile("resources/star.png");

    spriteEstrellaAfrica = new Sprite(*texturaEstrella);
    spriteEstrellaAfrica->setScale(ESCALA_ESTRELLA, ESCALA_ESTRELLA);
    spriteEstrellaAfrica->setPosition(posAfrica.x - 40, posAfrica.y);

    spriteEstrellaAsia = new Sprite(*texturaEstrella);
    spriteEstrellaAsia->setScale(ESCALA_ESTRELLA, ESCALA_ESTRELLA);
    spriteEstrellaAsia->setPosition(posAsia.x - 40, posAsia.y);

    spriteEstrellaEuropa = new Sprite(*texturaEstrella);
    spriteEstrellaEuropa->setScale(ESCALA_ESTRELLA, ESCALA_ESTRELLA);
    spriteEstrellaEuropa->setPosition(posEuropa.x - 40, posEuropa.y);

    spriteEstrellaAntartida = new Sprite(*texturaEstrella);
    spriteEstrellaAntartida->setScale(ESCALA_ESTRELLA, ESCALA_ESTRELLA);
    spriteEstrellaAntartida->setPosition(posAntartida.x - 40, posAntartida.y);

    spriteEstrellaAmerica = new Sprite(*texturaEstrella);
    spriteEstrellaAmerica->setScale(ESCALA_ESTRELLA, ESCALA_ESTRELLA);
    spriteEstrellaAmerica->setPosition(posAmerica.x - 40, posAmerica.y);

    Motor2D::centrarView();
}

StateMapa::~StateMapa()
{
    //dtor
}

void StateMapa::render()
{
    sf::RenderWindow *window = Juego::getInstance()->getWindow();
    window->draw(*sFondo);
    window->draw(*selector);

    if(Globales::NIVEL_AMERICA_SUPERADO)
        window->draw(*spriteEstrellaAmerica);

    if(Globales::NIVEL_AFRICA_SUPERADO)
        window->draw(*spriteEstrellaAfrica);

    if(Globales::NIVEL_EUROPA_SUPERADO)
        window->draw(*spriteEstrellaEuropa);

    if(Globales::NIVEL_ASIA_SUPERADO)
        window->draw(*spriteEstrellaAsia);

    if(Globales::NIVEL_ANTARTIDA_SUPERADO)
        window->draw(*spriteEstrellaAntartida);
}

void StateMapa::update()
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
                if(event.key.code == sf::Keyboard::C) {
                    //std::cout << "C habilita niveles" << std::endl;
                    if(!Constantes::PUEDE_NIVEL_MSX) {
                        Constantes::PUEDE_NIVEL_MSX = true;
                    } else {
                        Constantes::PUEDE_NIVEL_MSX = false;
                    }
                }
                //Para saber a la posición del mapa a la que me muevo
                if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Right) {
                    posActual++;
                    if(posActual == POS_ANTARTIDA && !Constantes::PUEDE_NIVEL_MSX ) { //El nivel de MSX
                        posActual++;
                    }
                    if(posActual >= MAX_POS_MAPA) {
                        posActual = 0;
                    }

                }
                if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left) {
                    posActual--;
                    if(posActual == POS_ANTARTIDA && !Constantes::PUEDE_NIVEL_MSX ) { //El nivel de MSX
                        posActual--;
                    }
                    if(posActual < 0) {
                        posActual = MAX_POS_MAPA-1;
                    }
                }
                Vector2i vectorPosActual = posicionesMapa[posActual];
                selector->setPosition(vectorPosActual.x, vectorPosActual.y);

                //Si le da a enter para saber a que State cambiar
                if(event.key.code == sf::Keyboard::Return) {
                    switch(posActual) {
                        case POS_AMERICA:
                            Globales::JSON_NIVEL_SELECCIONADO = "./mapas/Nivel0.json";
                            music->stop();
                            cambiarAInGame();
                            break;
                        case POS_EUROPA:
                            Globales::JSON_NIVEL_SELECCIONADO = "./mapas/Nivel1.json";
                            music->stop();
                            cambiarAInGame();
                            break;
                        case POS_ANTARTIDA:
                            Globales::JSON_NIVEL_SELECCIONADO = "./mapas/NivelFinal.json";
                            music->stop();
                            cambiarAInGame();
                            break;
                        case POS_ASIA:
                            /*Globales::JSON_NIVEL_SELECCIONADO = "";
                            music->stop();
                            cambiarAInGame();*/
                            break;
                        case POS_OCEANIA:
                            /*Globales::JSON_NIVEL_SELECCIONADO = "";
                            music->stop();
                            cambiarAInGame();*/
                            break;
                        case POS_AFRICA:
                            /*Globales::JSON_NIVEL_SELECCIONADO = "";
                            music->stop();
                            cambiarAInGame();*/
                            break;
                        case POS_IR_A_MENU:
                            music->stop();
                            cambiarAMenu();
                            break;
                    }
                }
                break;
            }
        }
    }
}
