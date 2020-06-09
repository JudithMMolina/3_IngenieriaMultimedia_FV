#ifndef POCION_H
#define POCION_H
#include <iostream>
#include <ObjetoMapa.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Pocion : public ObjetoMapa
{
    public:
        Pocion(float posX, float posY, int tipoPocion);
        virtual ~Pocion();
        void update();

        int getVida(){return vida;}

    protected:

    private:
        int tipo; // 0->buena  1 o 2 --> random, la primera buena y la segunda mala
        int vida;

        const int TIPO_POCION_BUENA = 1;
        const int TIPO_POCION_MALA = 2;
        const int TIPO_POCION_SORPRESA = 3;
};

#endif // POCION_H
