#ifndef BOMBA_H
#define BOMBA_H

#include <ObjetoMapa.h>
#include <Caja.h>
class Enemigo;

using namespace std;
using namespace sf;

class Bomba : public ObjetoMapa
{
    public:
        Bomba(float posX, float posY, int tipo);
        virtual ~Bomba();
        virtual void update();
        void explosion(vector<Enemigo *> *, vector<Caja *> *);

        bool getExplotado(){
            return explotado;
        }

    protected:
        int rango;
        int danyo;
        int tiempo;
        bool explotado;
        sf::Time tiempoBomba;
        vector<Enemigo *> *enemigos;
        vector<Caja *> *cajas;

        void animacionBomba();
    private:
        bool bombaSoltada;
        sf::Clock explosionAnimacion;
        sf::Sprite *spriteExplosion;
};

#endif // BOMBA_H
