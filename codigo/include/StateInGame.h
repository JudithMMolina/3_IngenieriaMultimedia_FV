#ifndef STATEINGAME_H
#define STATEINGAME_H

//#include <State.h> //seria para el enum, pero, en principio no hace falta, ya que lo incluye Juego.h
#include <Juego.h>
#include <Nivel.h>
#include <Jugador1.h>
#include <Jugador2.h>
#include <Mapa.h>
#include <Hud.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
//#include <StateGameOver.h> //esto era antes cuando a setState le pasabamos el puntero al estado

class StateInGame : public State
{
    public:
        StateInGame();
        virtual ~StateInGame();
        void update(sf::Time timeElapsed);
        void render(double percentTick);
        virtual Estados getEstado() { return State::Estados::INGAME; };

    protected:

    private:
        Nivel *nivel;
        Jugador1 *jugador1;
        Jugador2 *jugador2;

        Hud *hud1;
        Hud *hud2;
        /*void cambiarAGameOver() {
            Juego::getInstance()->setState(new StateGameOver());
        }*/
        void cambiarAGameOver() {
            Juego::getInstance()->setState(State::Estados::GAMEOVER);
        }

        double posAntX;
        double posAntY;
        double posSigX;
        double posSigY;
        sf::Music *music;
};

#endif // STATEINGAME_H
