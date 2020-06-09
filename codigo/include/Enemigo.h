#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Jugador.h"
#include "Mapa.h"
#include "Nodo.h"
#include "Animacion.h"

using namespace std;

class Enemigo
{
    public:
        Enemigo();
        //enmigoExplosivo crearEnemigo(float posX, float posY, int tipoEnemigo);
        virtual ~Enemigo();

        int getVida(){return vida;}
        bool getVivo(){return enemigoVivo;}
        void setVida(int salud){vida=salud;}
        void bajarVida(int vidaMenos);
        int getItem(){return item;}
        virtual void update();
        virtual void update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa, sf::Time timeElapsed);
        virtual void update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa);
        virtual void render(sf::RenderWindow *window);
        virtual void render(sf::RenderWindow *window, double percentTick);
        virtual void animacionReposo();
        bool isVisible();

        Sprite* getSprite(){return sprite;};
        virtual int getGenerarEnemigos(){return 0;}


    protected:

        void movimientoEnemigo(float eneX, float eneY, float jugX, float jugY,float velocidadEnemigo, int mapDimX, int mapDimY);
        void calcularCamino(float eneX, float eneY, float jugX, float jugY, int mapDimX, int mapDimY);

        float vida;
        int item;
        Sprite* sprite;
        bool enemigoVivo;
        float velocidad_enemigo;
        static float VELOCIDAD_ENEMIGO_1;
        static float VELOCIDAD_BALA_ENEMIGO_2;
        static float VELOCIDAD_ENEMIGO_3;

        static int DANYO_ENEMIGO_1;
        static int DANYO_BALA_ENEMIGO_2;
        static int DANYO_ENEMIGO_3;


        bool primeraVezGrid = false;
        Nodo ***todosNodos;

        int **mapa2;

        std::vector<Nodo*> listaInterior;
        std::vector<Nodo*> listaFrontera;
        std::vector<Nodo*> listaNodosPadres;
        bool soyElEnemigo = false;
        bool meVoyaDormir = false;
        bool salir = false;
        int enemigoPos=0;
        int inicioX;
        int inicioY;
        int finalX;
        int finalY;
        float siguientePosX;
        float siguientePosY;
        bool primeraVez= true;

        bool recibirDanyo=false;
        sf::Clock tiempoEnRojo;
        sf::Clock animacionReposoReloj;
        int distanciaNodosJugador;
        //std::vector<sf::RectangleShape> rectangulos;
        //sf::RectangleShape nodoSolucion;
        //std::vector<sf::RectangleShape> soluciones;

        // animaciones
        /*Animacion* animacionActual;
        Animacion* animacionStop;

        Animacion* animacionUp;
        Animacion* animacionLeft;
        Animacion* animacionDown;
        Animacion* animacionRight;

        Animacion* animacionUpAtaque;
        Animacion* animacionLeftAtaque;
        Animacion* animacionDownAtaque;
        Animacion* animacionRightAtaque;*/

};

#endif // ENEMIGO_H
