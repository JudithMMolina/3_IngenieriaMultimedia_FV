#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>


class State
{
    public:
        enum Estados{ SIN_ESTADO, INTRO, MENU, MAPA, INGAME, GAMEOVER, PAUSA, JUEGO_SUPERADO, NIVEL_SUPERADO, CONTROLES, CREDITOS };
        State();
        virtual ~State();
        virtual void update() {};
        virtual void update(sf::Time timeElapsed) {};
        virtual void render() {};
        virtual void render(double percentTick) {};
        virtual Estados getEstado() { return Estados::SIN_ESTADO; };

    protected:

    private:
};

#endif // STATE_H
