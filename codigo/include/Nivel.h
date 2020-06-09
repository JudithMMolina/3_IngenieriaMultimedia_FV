#ifndef NIVEL_H
#define NIVEL_H

#include <Mapa.h>
#include <Enemigo.h>
#include <Pocion.h>

#include <iostream>
#include <vector>
#include "EnemigoFactory.h"
#include "Jugador.h"
#include "Bala.h"

class Nivel
{
    public:
        Nivel();
        virtual ~Nivel();

        void pintarEnemigos(sf::RenderWindow &, double percentTick);
        void pintarObjetos(sf::RenderWindow &);
        void pintarBalas1(sf::RenderWindow &);
        void pintarBalas2(sf::RenderWindow &);

        void update(Jugador *jugador1, Jugador *jugador2, sf::Time timeElapsed);

        void generarEnemigo(int numEnemigos);



        // --------------- GETTERS & SETTERS ----------------------
        Mapa *getMapa() { return mapa; }
        std::vector<Enemigo *> *getEnemigos() { return enemigos; }
        std::vector<ObjetoMapa *> *getObjetos() { return objetos; }
        std::vector<sf::Vector2f *> *getSpawns() { return spawns;}
        // --------------- FIN GETTERS & SETTERS ----------------------

    protected:

    private:
        Mapa *mapa;
        std::vector<Enemigo *> *enemigos;
        std::vector<ObjetoMapa *> *objetos;
        std::vector<Bala *> *balas1;
        std::vector<Bala *> *balas2;
        std::vector<sf::Vector2f *> *spawns;
};

#endif // NIVEL_H
