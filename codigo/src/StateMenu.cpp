#include "StateMenu.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Juego.h>
#include <Motor2D.h>
#include <Utils.h>


StateMenu::StateMenu()
{
    posCargarPartida.x = posNuevaPartida.x = posControles.x = posCreditos.x = posSalir.x = 260;
    posCargarPartida.y = 175;
    posNuevaPartida.y = 245;
    posControles.y = 315;
    posCreditos.y = 385;
    posSalir.y = 455;

    posicionesMenu[0] = posCargarPartida;
    posicionesMenu[1] = posNuevaPartida;
    posicionesMenu[2] = posControles;
    posicionesMenu[3] = posCreditos;
    posicionesMenu[4] = posSalir;

    tFondo = new sf::Texture();
    if(!tFondo->loadFromFile("resources/screen_menu.png"))
    {
        std::cerr << "Error cargando la imagen screen_menu.png";
        //exit(0);
    }
    sFondo = new sf::Sprite();
    sFondo->setTexture(*tFondo);

    selector = new sf::CircleShape();
    selector->setRadius(10.f);
    selector->setFillColor(sf::Color::Cyan);
    selector->setOutlineColor(sf::Color::Blue);
    selector->setOutlineThickness(5);
    //El selector empieza en la posicion de cargar partida, que es la 1a opcion
    Vector2i vectorPosActual = posicionesMenu[posActual];
    selector->setPosition(vectorPosActual.x, vectorPosActual.y);

    music = new sf::Music();
	if (!music->openFromFile("resources/music/Hasta Mi Planeta.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/Hasta Mi Planeta.ogg";
        //exit(0);
	}
    music->play();
    music->setVolume(60);

    Motor2D::centrarView();
    //ctor
}

StateMenu::~StateMenu()
{
    //dtor
}

void StateMenu::render()
{
    sf::RenderWindow *window = Juego::getInstance()->getWindow();
    //sf::Text *text = Motor2D::getDefaultText();
    //text->setString("Estamos en StateMenu");
    //window->draw(*text);
    window->draw(*sFondo);
    window->draw(*selector);
}

void StateMenu::update()
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
                //Para saber a la posición del menu a la que me muevo
                if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Right) {
                    posActual++;
                    if(posActual >= MAX_POS_MENU){
                        posActual = 0;
                    }
                }
                if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Left) {
                    posActual--;
                    if(posActual < 0){
                        posActual = MAX_POS_MENU-1;
                    }
                }
                Vector2i vectorPosActual = posicionesMenu[posActual];
                selector->setPosition(vectorPosActual.x, vectorPosActual.y);

                //Si le da a enter para saber a que State cambiar
                if(event.key.code == sf::Keyboard::Return) {
                    switch(posActual) {
                        case POS_CARGAR_PARTIDA:
                            Utils::cargarPartida();
                            music->stop();
                            cambiarAMapa();
                            break;
                        case POS_NUEVA_PARTIDA:
                            Utils::borrarPartida();
                            music->stop();
                            cambiarAMapa();
                            break;
                        case POS_CONTROLES:
                            music->stop();
                            cambiarAControles();
                            break;
                        case POS_CREDITOS:
                            music->stop();
                            cambiarACreditos();
                            break;
                        case POS_SALIR:
                            window->close();
                            break;
                    }
                }
                break;
            }
        }
    }
}
