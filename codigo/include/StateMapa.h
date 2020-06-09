#ifndef STATEMAPA_H
#define STATEMAPA_H

//#include <State.h> //seria para el enum, pero, en principio no hace falta, ya que lo incluye Juego.h
#include <Juego.h>
//#include <StateInGame.h> //esto era antes cuando a setState le pasabamos el puntero al estado
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class StateMapa : public State
{
    public:
        StateMapa();
        virtual ~StateMapa();
        void update();
        void render();
        virtual Estados getEstado() { return State::Estados::MAPA; };

    protected:

    private:
        /*void cambiarAInGame() {
            Juego::getInstance()->setState(new StateInGame());
        }*/
        void cambiarAInGame() {
            Juego::getInstance()->setState(State::Estados::INGAME);
        }
        void cambiarAMenu() {
            Juego::getInstance()->setState(State::Estados::MENU);
        }

        const static int MAX_POS_MAPA = 7;

        const static int POS_AMERICA = 0;
        const static int POS_AFRICA = 1;
        const static int POS_EUROPA = 2;
        const static int POS_ASIA = 3;
        const static int POS_OCEANIA = 4;
        const static int POS_ANTARTIDA = 5;
        const static int POS_IR_A_MENU = 6;

        const float ESCALA_ESTRELLA = 0.2f;

        int posActual = 0;

        Vector2i posAmerica;
        Vector2i posAfrica;
        Vector2i posEuropa;
        Vector2i posAsia;
        Vector2i posOceania;
        Vector2i posAntartida;
        Vector2i posIrAMenu;

        Vector2i posicionesMapa[MAX_POS_MAPA];

        Texture *tFondo;
        Sprite *sFondo;

        Texture *texturaEstrella;
        Sprite *spriteEstrellaAmerica;
        Sprite *spriteEstrellaEuropa;
        Sprite *spriteEstrellaAsia;
        Sprite *spriteEstrellaAfrica;
        Sprite *spriteEstrellaAntartida;

        CircleShape *selector;

        sf::Music *music;

};

#endif // STATEMAPA_H
