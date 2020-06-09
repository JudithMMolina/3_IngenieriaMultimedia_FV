#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Constantes
{
    public:

        const static bool DEBUG = false;
        const static int TAMANYO_VENTANA_X = 1280;
        const static int TAMANYO_VENTANA_Y = 720;

        const int static posXhud1 = 10;
        const int static posYhud1 = 575;
        const int static posXhud2 = 950;
        const int static posYhud2 = 575;

        const int static posXdata1 = 142;
        const int static posYdata1 = 92;
        const int static posXdata2 = 26;
        const int static posYdata2 = 92;

        const int static posXbomb1 = 277;
        const int static posYbomb1 = 94;
        const int static posXbomb2 = 160;
        const int static posYbomb2 = 94;

        const int static posXllave1 = 14;
        const int static posYllave1 = 94;
        const int static posXllave2 = 273;
        const int static posYllave2 = 94;

        const int static posXvida1 = 140;
        const int static posYvida = 40;
        const int static posXvida2 = 75;

        const int static posXarma11 = 183;
        const int static posXarma12 = 231;
        const int static posYarma  = 93;
        const int static posXarma21 = 63;
        const int static posXarma22 = 113;

        static bool PUEDE_NIVEL_MSX;

        static const string JSON_NIVEL_DEFAULT;
        static const string JSON_NIVEL_AMERICA;
        static const string JSON_NIVEL_AFRICA;
        static const string JSON_NIVEL_EUROPA;
        static const string JSON_NIVEL_ANTARTIDA;
        static const string ARCHIVO_SAVE;

        static bool PUEDE_PARAR_MUSICA_INGAME;



    protected:

    private:

};

#endif // CONSTANTES_H
