#ifndef STATEJUEGOSUPERADO_H
#define STATEJUEGOSUPERADO_H

#include <State.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class StateJuegoSuperado : public State
{
    public:
        StateJuegoSuperado();
        virtual ~StateJuegoSuperado();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::JUEGO_SUPERADO; };

    protected:

    private:
        Texture *texturaFondo;
        Sprite *spriteFondo;
        Texture *texturaMascara;
        Sprite *spriteMascara;

        Text *texto;
        sf::Music *music;
};

#endif // STATEJUEGOSUPERADO_H
