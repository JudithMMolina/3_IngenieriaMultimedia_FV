#include "Juego.h"
#include "Constantes.h"
#include <SFML/Graphics.hpp>
#include <State.h>
#include <StateIntro.h>
#include <StateMenu.h>
#include <StateControles.h>
#include <StateCreditos.h>
#include <StateMapa.h>
#include <StateInGame.h>
#include <StateGameOver.h>
#include <StateJuegoSuperado.h>
#include <StateSuperarNivel.h>
#include <StatePausa.h>
#include <Motor2D.h>

using namespace sf;
using namespace std;

Juego* Juego::juego = 0;

Juego::Juego()
{
    //ctor
    nombre = new string("MSXPlanet");
    direccionView = new Vector2f();
}

Juego::~Juego()
{
    //dtor
}


Juego* Juego::getInstance()
{
    if(juego == 0)
    {
        juego = new Juego();
    }
    return juego;
}


void Juego::setState(State::Estados tipoEstado)
{
    //std::cout << "TIPO DE ESTADO: " << tipoEstado << std::endl;
    switch(tipoEstado){
        case State::INTRO:
            stateActual = new StateIntro();
            break;
        case State::MENU:
            stateActual = new StateMenu();
            break;
        case State::CONTROLES:
            stateActual = new StateControles();
            break;
        case State::CREDITOS:
            stateActual = new StateCreditos();
            break;
        case State::MAPA:
            stateActual = new StateMapa();
            break;
        case State::INGAME:
            stateActual = new StateInGame();
            break;
        case State::GAMEOVER:
            stateActual = new StateGameOver();
            break;
        case State::JUEGO_SUPERADO:
            stateActual = new StateJuegoSuperado();
            break;
        case State::NIVEL_SUPERADO:
            stateActual = new StateSuperarNivel();
            break;
        default:
            cout << "Este estado no existe." << endl;
    }
}

void Juego::iniciar()
{
    window = new sf::RenderWindow(sf::VideoMode(Constantes::TAMANYO_VENTANA_X, Constantes::TAMANYO_VENTANA_Y), "MSXPlanet");
    view = new View();
    view->setSize(Vector2f(Constantes::TAMANYO_VENTANA_X, Constantes::TAMANYO_VENTANA_Y));
    view->setCenter(Constantes::TAMANYO_VENTANA_X / 2, 350);
    buclePrincipal();
}

void Juego::buclePrincipal()
{
    sf::Clock updateClock;
    sf::Time timeElapsed;
    double percentTick = 0.0;
    const double UPDATE_TICK_TIME = 1000.0 / 30.0;

    updateClock.restart();

    while (window->isOpen())
    {
        if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME)
        {
            //cout << "Vamos a hacer update" << endl;
            timeElapsed = updateClock.restart();  // este valor hay que usarlo para calcular el movimiento de forma correcta timeElapsed.asSeconds()
            if(stateActual->getEstado() == State::Estados::INGAME)
                stateActual->update(timeElapsed);
            else
                stateActual->update();
        }

        percentTick = min(1.0, (updateClock.getElapsedTime().asMilliseconds()) / (UPDATE_TICK_TIME * 1.d));

        window->clear();

        window->setView(*view);

        //cout << "Vamos a hacer render" << endl;
        //cout << "El percent tick es " << percentTick << endl;

          if(stateActual->getEstado() == State::Estados::INGAME)
            stateActual->render(percentTick);
        else
            stateActual->render();



        window->display();


    }
}

void Juego::pausar()
{
    Texture *fondo = Motor2D::capturarPantalla();
    stateAnterior = stateActual;
    StatePausa *pausa = new StatePausa();
    pausa->setFondo(fondo);
    stateActual = pausa;
}

void Juego::volverDePausa()
{
    delete stateActual;
    stateActual = stateAnterior;
}

void Juego::borrarStateAnterior()
{
    delete stateAnterior;
}
