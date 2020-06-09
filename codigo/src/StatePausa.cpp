#include "StatePausa.h"
#include "Motor2D.h"
#include "Juego.h"
#include "Constantes.h"
#include "SFML/Graphics.hpp"

using namespace sf;

StatePausa::StatePausa()
{
    //ctor
    textoTitulo = Motor2D::getDefaultText();
    textoTitulo->setString("Pausa, queridos amigos, ponednos buena nota");
    textoTitulo->setPosition(Constantes::TAMANYO_VENTANA_X / 2 - textoTitulo->getGlobalBounds().width / 2, 128);
    fondo = new Sprite();
    Juego::getInstance()->getView()->setCenter(Constantes::TAMANYO_VENTANA_X / 2, Constantes::TAMANYO_VENTANA_Y / 2);
    texturaMascara = new Texture();
    texturaMascara->loadFromFile("resources/mascara_roja.png");
    mascara = new Sprite(*texturaMascara);
    circuloElemSelec = new CircleShape();
    circuloElemSelec->setRadius(12);
    circuloElemSelec->setFillColor(Color::Blue);

    opciones = new vector<Text *>;
    inicializarMenu();

    music = new sf::Music();
	if (!music->openFromFile("resources/music/Mapa.ogg"))
    {
		std::cerr << "Error cargando la cancion resources/music/Mapa.ogg";
        //exit(0);
	}
    music->play();
}

StatePausa::~StatePausa()
{
    //dtor
}

void StatePausa::inicializarMenu()
{
    Text *textoVolver = Motor2D::getDefaultText();
    textoVolver->setString("Volver");
    Text *textoReiniciar = Motor2D::getDefaultText();
    textoReiniciar->setString("Reiniciar nivel");
    Text *textoMapa = Motor2D::getDefaultText();
    textoMapa->setString("Volver al mapa");
    Text *textoMenu = Motor2D::getDefaultText();
    textoMenu->setString(L"Volver al menu");
    Text *textoSalir = Motor2D::getDefaultText();
    textoSalir->setString("Salir del juego");

    opciones->push_back(textoVolver);
    opciones->push_back(textoReiniciar);
    opciones->push_back(textoMapa);
    opciones->push_back(textoMenu);
    opciones->push_back(textoSalir);

    float separacionEntreOpciones = textoVolver->getGlobalBounds().height + 30;
    float x = Constantes::TAMANYO_VENTANA_X / 2 - textoSalir->getGlobalBounds().width / 2;

    for(unsigned int i = 0; i < opciones->size(); i++)
    {
        Text *textoActual = (*opciones)[i];
        float nuevaY = yMenuInicial + i * separacionEntreOpciones;
        textoActual->setPosition(x, nuevaY);
    }
}

void StatePausa::render()
{
    Juego::getInstance()->getWindow()->draw(*fondo);
    Juego::getInstance()->getWindow()->draw(*mascara);
    Juego::getInstance()->getWindow()->draw(*textoTitulo);

    for(unsigned int i = 0; i < opciones->size(); i++)
        Juego::getInstance()->getWindow()->draw(*(*opciones)[i]);

    Juego::getInstance()->getWindow()->draw(*circuloElemSelec);
}

void StatePausa::update()
{
    State::update();
    RenderWindow *window = Juego::getInstance()->getWindow();

    window->setKeyRepeatEnabled(false);

    //cout << "Musica en pausa " << music->getStatus() << endl;
    if(music->getStatus() == 0 || music->getStatus() == 1) {
        music->play();
    }

    Event event;

    while (window->pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                window->close();
                break;
            case Event::KeyPressed:
                if(event.key.code == Keyboard::Space) {
                    music->pause();
                    Juego::getInstance()->volverDePausa();
                }
                break;

            case Event::KeyReleased:
                cout << "Estamos en key released" << endl;
                if(event.key.code == Keyboard::Up || event.key.code == Keyboard::Left)
                {
                    if(elemActual > 0)
                        elemActual--;
                    else
                        elemActual = opciones->size() - 1;
                }
                else if(event.key.code == Keyboard::Down || event.key.code == Keyboard::Right)
                {
                    if(elemActual < opciones->size() - 1)
                        elemActual++;
                    else
                        elemActual = 0;
                }
                else if(event.key.code == Keyboard::Return)
                {
                    switch(elemActual)
                    {
                        // volver al juego
                        case 0: {
                            music->stop();
                            Juego::getInstance()->volverDePausa();
                            break;
                        }

                        // reiniciar nivel
                        case 1: {
                            music->stop();
                            Juego::getInstance()->borrarStateAnterior();
                            Juego::getInstance()->setState(State::Estados::INGAME);
                            break;
                        }

                        // volver al mapa
                        case 2: {
                            music->stop();
                            Juego::getInstance()->borrarStateAnterior();
                            Juego::getInstance()->setState(State::Estados::MAPA);
                            break;
                        }

                        // volver al menú
                        case 3: {
                            music->stop();
                            Juego::getInstance()->borrarStateAnterior();
                            Juego::getInstance()->setState(State::Estados::MENU);
                            break;
                        }

                        // salir del juego
                        case 4: {
                            music->stop();
                            window->close();
                            break;
                        }

                    }
                }
                break;
        }
    }

    circuloElemSelec->setPosition(xCirculo, (*opciones)[elemActual]->getPosition().y + 6);
}
