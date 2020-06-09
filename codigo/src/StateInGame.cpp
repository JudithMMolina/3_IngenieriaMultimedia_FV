#include "StateInGame.h"
#include "Juego.h"
#include "NivelFactory.h"
#include "Globales.h"
#include "Constantes.h"
#include "SFML/Graphics.hpp"
#include "iostream"

using namespace std;
using namespace sf;

StateInGame::StateInGame()
{
    //ctor
    music = new sf::Music();

    nivel = new Nivel();
    string json = Constantes::JSON_NIVEL_DEFAULT;

    if(Globales::JSON_NIVEL_SELECCIONADO != "") {
        json = Globales::JSON_NIVEL_SELECCIONADO;
        if(Globales::JSON_NIVEL_SELECCIONADO == "./mapas/Nivel0.json") {
            if (!music->openFromFile("resources/music/Solve The Puzzle.ogg"))
            {
                std::cerr << "Error cargando la cancion resources/music/Solve The Puzzle.ogg";
                //exit(0);
            }
        } else if(Globales::JSON_NIVEL_SELECCIONADO == "./mapas/Nivel1.json") {
            if (!music->openFromFile("resources/music/La Verdad.ogg"))
            {
                std::cerr << "Error cargando la cancion resources/music/La Verdad.ogg";
                //exit(0);
            }
        } else if(Globales::JSON_NIVEL_SELECCIONADO == "./mapas/NivelFinal.json") {
            if (!music->openFromFile("resources/music/Heroic Intrusion.ogg"))
            {
                std::cerr << "Error cargando la cancion resources/music/Heroic Intrusion.ogg";
                //exit(0);
            }
        }

    }
    music->play();
    music->setVolume(60);


    NivelFactory::crearNivel(json, nivel);

    Vector2f *posJugador1 = (*nivel->getSpawns())[0];
    Vector2f *posJugador2 = (*nivel->getSpawns())[1];

    cout << "La pos inicial del jugador 1 es " << posJugador1->x << "," << posJugador1->y << endl;
    cout << "La pos inicial del jugador 2 es " << posJugador2->x << "," << posJugador2->y << endl;


    jugador1 = new Jugador1();
    jugador2 = new Jugador2();
    jugador1->setDatos((Jugador*)jugador2, nivel->getMapa(), nivel->getObjetos(), nivel->getEnemigos(), posJugador1);
    jugador2->setDatos((Jugador*)jugador1, nivel->getMapa(), nivel->getObjetos(), nivel->getEnemigos(), posJugador2);
    hud1 = new Hud(1, jugador1);
    hud2 = new Hud(2, jugador2);

    // interpolacion camara

    Juego::getInstance()->getView()->setCenter(*posJugador1);

    posSigX=Juego::getInstance()->getView()->getCenter().x;
    posSigY=Juego::getInstance()->getView()->getCenter().y;
    posAntX=posSigX;
    posAntY=posSigY;
}

StateInGame::~StateInGame()
{
    //dtor
    delete nivel;
    delete jugador1;
    delete jugador2;
    delete hud1;
    delete hud2;
}

void StateInGame::update(sf::Time timeElapsed)
{
    RenderWindow *window = Juego::getInstance()->getWindow();

    //cout << "Musica in game " << music->getStatus() << endl;
    if(music->getStatus() == 0 || music->getStatus() == 1) { //si esta parada/reanudada (stop) o pausada (pause)
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
                if(event.key.code == Keyboard::Space){
                    if(music->getStatus() == 2) { //si esta sonando (play)
                        music->pause();
                    }
                    Juego::getInstance()->pausar();
                }
                break;
        }
    }
    posAntX=posSigX;
    posAntY=posSigY;

    Juego::getInstance()->getDireccionView()->x = 0.f;
    Juego::getInstance()->getDireccionView()->y = 0.f;
    nivel->update(jugador1, jugador2, timeElapsed);
    jugador1->update(timeElapsed);
    jugador2->update(timeElapsed);

    posSigX = posAntX + ((*Juego::getInstance()->getDireccionView()).x * 8.d) *timeElapsed.asMilliseconds()*0.02;
    posSigY = posAntY + ((*Juego::getInstance()->getDireccionView()).y * 8.d) *timeElapsed.asMilliseconds()*0.02;

    hud1->update();
    hud2->update();

    if( (jugador1->getVida() <= 0 || jugador2->getVida() <= 0) && (jugador1->getAnimMuerte() || jugador2->getAnimMuerte()) )
    {
        music->stop();
        cambiarAGameOver();
    }
    if(Constantes::PUEDE_PARAR_MUSICA_INGAME) {
        music->stop();
        Constantes::PUEDE_PARAR_MUSICA_INGAME = false;
    }
}

void StateInGame::render(double percentTick)
{
    //Interpolacion camara
    double posFinX = (posSigX-posAntX)*percentTick+posAntX;
    double posFinY = (posSigY-posAntY)*percentTick+posAntY;
    Juego::getInstance()->getView()->setCenter(posFinX,posFinY);

    nivel->getMapa()->pintarDelante(*Juego::getInstance()->getWindow());
    nivel->pintarObjetos(*Juego::getInstance()->getWindow());

    if(jugador1->getSprite()->getPosition().y > jugador2->getSprite()->getPosition().y){
        jugador2->render(percentTick);
        jugador1->render(percentTick);
    } else {
        jugador1->render(percentTick);
        jugador2->render(percentTick);
    }

    nivel->pintarEnemigos(*Juego::getInstance()->getWindow(), percentTick);
    nivel->getMapa()->pintarDetras(*Juego::getInstance()->getWindow());
    nivel->getMapa()->pintarRectangulosParedes(*Juego::getInstance()->getWindow());
    nivel->getMapa()->pintarRectangulosAgua(*Juego::getInstance()->getWindow());
    nivel->getMapa()->pintarRectangulosElectricidad(*Juego::getInstance()->getWindow());
    nivel->getMapa()->pintarRectangulosEscaleras(*Juego::getInstance()->getWindow());

    jugador1->pintarBarras();
    jugador2->pintarBarras();

    hud1->render();
    hud2->render();
}

/*void StateInGame::cambiarAGameOver() {
    //cout << "El jugador ha muerto, hay que cambiar de estado" << endl;
}*/


