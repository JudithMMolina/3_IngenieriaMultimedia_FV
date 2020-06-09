#ifndef STATEINTRO_H
#define STATEINTRO_H

//#include <State.h> //seria para el enum, pero, en principio no hace falta, ya que lo incluye Juego.h
#include <Juego.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <StateMenu.h> //esto era antes cuando a setState le pasabamos el puntero al estado

class StateIntro : public State
{
    public:
        StateIntro();
        virtual ~StateIntro();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::INTRO; };

    protected:

    private:
        /*void cambiarAMenu() {
            Juego::getInstance()->setState(new StateMenu());
        }*/
        void cambiarAMenu() {
            Juego::getInstance()->setState(State::Estados::MENU);
        }

        int framesTotales;
        int frameActual;
        bool intro;

        sf::Texture *tFondo;
        sf::Sprite *sFondo;
        sf::Music *music;

};

#endif // STATEINTRO_H
