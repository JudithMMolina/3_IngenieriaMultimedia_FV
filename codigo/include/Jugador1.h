#ifndef JUGADOR1_H
#define JUGADOR1_H

#include <Jugador.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Jugador1 : public Jugador
{
    public:
        Jugador1();
        virtual ~Jugador1();
        virtual void update(sf::Time timeElapsed);

        const int static kDanyoElectricidad = -5;

    protected:
        void comprobarElectricidad(vector<RectangleShape *> *);
        void comprobarElectricidadEnUnaDireccion(RectangleShape *);

        bool enElectricidad;

        sf::Time tiempoElectricidadAceleracion;
        sf::Time tiempoElectricidadDeceleracion;

    private:

};

#endif // JUGADOR1_H
