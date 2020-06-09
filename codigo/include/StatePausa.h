#ifndef STATEPAUSA_H
#define STATEPAUSA_H

#include <State.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Constantes.h>

using namespace sf;
using namespace std;

class StatePausa : public State
{
    public:
        StatePausa();
        virtual ~StatePausa();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::PAUSA; };
        void setFondo(Texture *nuevoFondo) {
            texturaFondo = nuevoFondo;
            fondo->setTexture(*nuevoFondo);
        };

    protected:

    private:
        Text *textoTitulo;
        Sprite *fondo;
        Sprite *mascara;
        Texture *texturaMascara;
        Texture *texturaFondo;
        CircleShape *circuloElemSelec;
        vector<Text *> *opciones;
        void inicializarMenu();
        int elemActual = 0;

        float yMenuInicial = Constantes::TAMANYO_VENTANA_Y / 3;
        float xCirculo = 440;
        sf::Music *music;

};

#endif // STATEPAUSA_H
