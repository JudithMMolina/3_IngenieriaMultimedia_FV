#ifndef ENEMIGOAEREO_H
#define ENEMIGOAEREO_H
#include "Enemigo.h"

#include <SFML/Graphics.hpp>

class EnemigoAereo : public Enemigo
{
    public:
        EnemigoAereo(int posX,int posY);
        virtual ~EnemigoAereo();

        void update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa);
        void render(sf::RenderWindow *window);
        void animacionMovimiento();
        void animacionReposo();
        void calcularDireccion(float posXJug, float posYJug, Mapa *mapa, int rows, int cols);
        void bajarVidaJugador1(Jugador *jugador1);
        void bajarVidaJugador2(Jugador *jugador2);


    protected:

    private:
        float distancia;
        int direccion_enemigo2;
        bool dentroDelRadio;
        bool atacar;
        bool bajarVidaJugador;

        sf::Clock animacionClock;
};

#endif // ENEMIGOAEREO_H
