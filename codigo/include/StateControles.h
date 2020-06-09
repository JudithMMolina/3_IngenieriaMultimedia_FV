#ifndef STATECONTROLES_H
#define STATECONTROLES_H

#include <Juego.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class StateControles : public State
{
    public:
        StateControles();
        virtual ~StateControles();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::CONTROLES; };

    protected:

    private:
        void cambiarAMenu() {
            Juego::getInstance()->setState(State::Estados::MENU);
        }

        Texture *texture;
        Texture *texture2;
        Texture *textureControl;
        Texture *texture2Control;

        Sprite *sprite;
        Sprite *sprite2;
        Sprite *spriteControl;
        Sprite *sprite2Control;

        Text *gameOver;
        Text *nombreRudolf;
        Text *nombreSara;
        Text *moverseSara;
        Text *moverseRudolfbot;
        Text *dispararSara;
        Text *dispararRudolfbot;
        Text *cambioSara;
        Text *cambioRudolfbot;
        Text *interactuarSara;
        Text *interacturarRudolfbot;

        Clock reloj;
        Clock reloj2;

        int cont;
        int cont2;
        float tiempoRepeticion;
        float tiempoRepeticion2;

        Music *music;

};

#endif // STATECONTROLES_H
