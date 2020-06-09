#ifndef STATESUPERARNIVEL_H
#define STATESUPERARNIVEL_H

#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "State.h"

using namespace sf;

class StateSuperarNivel : public State
{
    public:
        StateSuperarNivel();
        virtual ~StateSuperarNivel();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::NIVEL_SUPERADO; };

    protected:

    private:
        Texture *texturaFondo;
        Sprite *spriteFondo;
        Text *textoSuperior1;
        Text *textoSuperior2;
        Text *textoSuperior3;
        Text *textoInferior;
        sf::Music *music;
};

#endif // STATESUPERARNIVEL_H
