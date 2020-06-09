#ifndef STATECREDITOS_H
#define STATECREDITOS_H

#include <Juego.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class StateCreditos : public State
{
    public:
        StateCreditos();
        virtual ~StateCreditos();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::CREDITOS; };

    protected:

    private:
        void cambiarAMenu() {
            Juego::getInstance()->setState(State::Estados::MENU);
        }

        int framesTotales;
        int frameActual;
        bool creditos;

        sf::Texture *tFondo;
        sf::Sprite *sFondo;
        sf::Music *music;
};

#endif // STATECREDITOS_H
