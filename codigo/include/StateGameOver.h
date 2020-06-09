#ifndef STATEGAMEOVER_H
#define STATEGAMEOVER_H

//#include <State.h> //seria para el enum, pero, en principio no hace falta, ya que lo incluye Juego.h
#include <Juego.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <StateMapa.h> //esto era antes cuando a setState le pasabamos el puntero al estado

class StateGameOver : public State
{
    public:
        StateGameOver();
        virtual ~StateGameOver();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::GAMEOVER; };

    protected:

    private:
        /*void cambiarAMapa() {
            Juego::getInstance()->setState(new StateMapa());
        }*/
        void cambiarAMapa() {
            Juego::getInstance()->setState(State::Estados::MAPA);
        }
        sf::Texture *tFondo;
        sf::Sprite *sFondo;
        sf::Music *music;
};

#endif // STATEGAMEOVER_H
