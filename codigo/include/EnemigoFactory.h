#ifndef ENEMIGOFACTORY_H
#define ENEMIGOFACTORY_H
#include "Enemigo.h"
#include "EnemigoExplosivo.h"
#include "EnemigoAereo.h"
#include "EnemigoEstatico.h"
#include "EnemigoMSX.h"

class EnemigoFactory
{
    public:
        EnemigoFactory();
        virtual ~EnemigoFactory();

        static Enemigo* crearEnemigo(int posX, int posY, int tipoEnemigo);

    private:
};

#endif // ENEMIGOFACTORY_H
