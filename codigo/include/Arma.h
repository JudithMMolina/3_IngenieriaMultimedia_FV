#ifndef ARMA_H
#define ARMA_H

#include <ObjetoMapa.h>
#include "Motor2D.h"
#include "Jugador.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Bala;
class Enemigo;
class Jugador;

class Arma : public ObjetoMapa
{
    public:
        Arma(float posX, float posY, int tipo);
        virtual ~Arma();
        int getTipoArma(){
            return tipoArma;
        }
        void disparar(vector<Enemigo *> *);
        void setJugador(Jugador *jugador) {
            duenyo = jugador;
            cout << "Mi dueño es " << jugador->getNombre() << endl;
        };
        Jugador *getJugador() { return duenyo; };
        void update();
        void render();


    protected:
        int tipoArma;

    private:
        vector<Bala *> *balas;
        Jugador *duenyo;

        sf::Clock *clockGun;
        float tiempoCadencia;
};

#endif // ARMA_H
