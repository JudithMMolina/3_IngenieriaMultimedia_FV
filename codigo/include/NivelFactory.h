#ifndef NIVELFACTORY_H
#define NIVELFACTORY_H

#include <iostream>
#include <Nivel.h>

using namespace std;

class NivelFactory
{
    public:
        NivelFactory();
        virtual ~NivelFactory();
        static void crearNivel(std::string json, Nivel *nivel);

    protected:

    private:
        static constexpr char *nombreCapaParedes = "paredes";
        static const string nombreTileSet;
};

#endif // NIVELFACTORY_H
