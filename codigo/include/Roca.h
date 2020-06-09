#ifndef ROCA_H
#define ROCA_H

#include <ObjetoMapa.h>

using namespace sf;
using namespace std;

class Jugador;

class Roca : public ObjetoMapa
{
    public:
        Roca(float posX, float posY, int tipo);
        virtual ~Roca();

        bool getMovible(){
            return movible;
        }
        void setMovible(bool var){
            movible = var;
        }
        void mover(int, int, vector<RectangleShape *> *, vector<ObjetoMapa *> *, Jugador *);

    protected:

        bool movible;

        void comprobarParedesEnUnaDireccion(RectangleShape *, char, int, int);

        void comprobarObjetosEnUnaDireccion(ObjetoMapa *, char, int, int);


    private:
};

#endif // ROCA_H
