#ifndef JUGADOR2_H
#define JUGADOR2_H

#include <Jugador.h>

class Jugador2 : public Jugador
{
    public:
        Jugador2();
        virtual ~Jugador2();
        virtual void update(sf::Time timeElapsed);

        const int static kDanyoAgua = -5;

    protected:
        void comprobarAgua(vector<RectangleShape *> *);
        void comprobarAguaEnUnaDireccion(RectangleShape *);
        void comprobarEscaleras(vector<RectangleShape *> *);
        void comprobarEscalerasEnUnaDireccion(RectangleShape *, char);
        void comprobarColisiones(vector<RectangleShape *> *);
        void comprobarColisionesEnUnaDireccion(RectangleShape *, char);
        void moverRoca();

        bool enAgua;

        sf::Time tiempoAguaAceleracion;
        sf::Time tiempoAguaDeceleracion;

    private:
};

#endif // JUGADOR2_H
