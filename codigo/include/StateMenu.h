#ifndef STATEMENU_H
#define STATEMENU_H

//#include <State.h> //seria para el enum, pero, en principio no hace falta, ya que lo incluye Juego.h
#include <Juego.h>
//#include <StateInGame.h> //esto era antes cuando a setState le pasabamos el puntero al estado
//#include <StateMapa.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StateMenu : public State
{
    public:
        StateMenu();
        virtual ~StateMenu();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::MENU; };

    protected:

    private:
        /*
        void cambiarAInGame() {
            Juego::getInstance()->setState(new StateInGame());
        }
        void cambiarAMapa() {
            Juego::getInstance()->setState(new StateMapa());
        }
        */
        void cambiarAInGame() {
            Juego::getInstance()->setState(State::Estados::INGAME);
        }
        void cambiarAMapa() {
            Juego::getInstance()->setState(State::Estados::MAPA);
        }
        void cambiarAControles() {
            Juego::getInstance()->setState(State::Estados::CONTROLES);
        }
        void cambiarACreditos() {
            Juego::getInstance()->setState(State::Estados::CREDITOS);
        }

        const static int MAX_POS_MENU = 5;

        const static int POS_CARGAR_PARTIDA = 0;
        const static int POS_NUEVA_PARTIDA = 1;
        const static int POS_CONTROLES = 2;
        const static int POS_CREDITOS = 3;
        const static int POS_SALIR = 4;

        int posActual = 0;

        Vector2i posCargarPartida;
        Vector2i posNuevaPartida;
        Vector2i posControles;
        Vector2i posCreditos;
        Vector2i posSalir;

        Vector2i posicionesMenu[MAX_POS_MENU];

        sf::Texture *tFondo;
        sf::Sprite *sFondo;

        sf::CircleShape *selector;

        sf::Music *music;

};

#endif // STATEMENU_H
