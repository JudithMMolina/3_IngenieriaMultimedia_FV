#ifndef JUGADOR_H
#define JUGADOR_H


#include <Jugador.h>
#include <Mapa.h>
#include <ObjetoMapa.h>

#include <Bomba.h>
#include <ObjetoMetaNivel.h>
#include <Llave.h>
#include <Roca.h>
#include <Pocion.h>
#include <Puerta.h>
#include <Caja.h>
#include <Animacion.h>

#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

using namespace sf;
using namespace std;

class Enemigo;
class Arma;

class Jugador
{
    public:
        //constexpr static float velocidad = 8.0; //Creo que necesitamos que sea una variable
        //static float velocidad = 8.0;

        Jugador();
        virtual ~Jugador();


        // -------- GETTERS Y SETTERS ---------------
        Sprite *getSprite() {
            return sprite;
        }
        sf::RectangleShape *getBody(){ return body;}

        Vector2f *getDireccion() {
            return direccion;
        }
        void setDireccionX(int var){
            direccion->x = var;
        }
        void setDireccionY(int var){
            direccion->y = var;
        }

        Vector2f *getDireccionBala(){
            return direccionBala;
        }

        float getVelocidad(){
            return velocidad;
        }

        int getVida(){
            return vida;
        }

        void modificarVida(int);
        void modificarVelocidad(float);


        bool tieneLlave(){
            if(llave != nullptr) return true;
            else return false;
        }
        bool tieneBomba(){
            if(bomba != nullptr) return true;
            else return false;
        }
        int queArma(){
            return arma;
        }
        int queTieneSeleccionado(){
            return seleccionado;
        }

        char *getNombre() {
            return nombre;
        }

        void setDatos(Jugador *, Mapa *, vector<ObjetoMapa *> *, vector<Enemigo *> *, Vector2f *posInicial);

        Mapa* getMapa(){return mapa;};

        //void setAnimacionActual(Animacion* nuevaAnimacion){animacionActual=nuevaAnimacion;}
        bool getAnimMuerte(){ return animMuerto;}

        // -------- FIN GETTERS Y SETTERS ---------------

        void pintarBarras();

        virtual void update(sf::Time timeElapsed);
        void render(double percentTick);



    protected:
        // ------ VARIABLES DE INSTANCIA ----------------
        Sprite *sprite;
        sf::RectangleShape *body;

        Animacion* animacionActual;
        Animacion* animacionStopUp;
        Animacion* animacionStopLeft;
        Animacion* animacionStopDown;
        Animacion* animacionStopRight;

        Animacion* animacionUp;
        Animacion* animacionLeft;
        Animacion* animacionDown;
        Animacion* animacionRight;

        Animacion* animacionUpCuchillo;
        Animacion* animacionLeftCuchillo;
        Animacion* animacionDownCuchillo;
        Animacion* animacionRightCuchillo;

        Animacion* animacionUpArcoCutre;
        Animacion* animacionLeftArcoCutre;
        Animacion* animacionDownArcoCutre;
        Animacion* animacionRightArcoCutre;

        Animacion* animacionUpArcoChachi;
        Animacion* animacionLeftArcoChachi;
        Animacion* animacionDownArcoChachi;
        Animacion* animacionRightArcoChachi;

        Animacion* animacionMuerte;
        bool animMuerto;
        int tiempoMuerto;


        Vector2f *direccion;
        Vector2f *direccionBala;

        Arma *armaCutre;
        Arma *armaChachi;
        char *nombre;

        int teclaArriba;
        int teclaAbajo;
        int teclaIzquierda;
        int teclaDerecha;

        int teclaDisparo;
        Clock relojDisparo;

        int teclaInteractuar;
        int teclaCambioArma;

        int teclaDios;
        bool modoDios;

        float velocidad;
        int vida;

        Llave *llave;
        Bomba *bomba;
        //int pocion;
        int arma;

        int seleccionado;

        vector<ObjetoMapa *> *todosObjetos; //Array de objetos

        vector<Arma *> *grupoArmas; //Array de armas
        vector<Llave *> *grupoLlaves; //Array de llaves
        vector<Bomba *> *grupoBombas; //Array de bombas
        vector<Pocion *> *grupoPociones; //Array de pociones
        vector<Roca *> *grupoRocas; //Array de rocas
        vector<Caja *> *grupoCajas; //Array de cajas
        vector<Puerta *> *grupoPuertas; //Array de puertas
        ObjetoMetaNivel *objetoMetaNivel;
        vector<Enemigo *> *enemigos; //Array de enemigos
        bool objetosUpdate; //Para saber si se han cargado los objetos o no

        Clock jugadorClock;
        sf::Time tiempoCambioArma;
        sf::Time tiempoCuchillada;
        sf::Time tiempoEncimaEnemigo;

        double posSigX;
        double posSigY;
        double posAntX;
        double posAntY;
        double posFinX;
        double posFinY;


        Clock ataqueClock;
        //RectangleShape barraVida;

        Mapa *mapa;
        Jugador *otro;

        // ------ FIN VARIABLES DE INSTANCIA ----------------




        // ------ MÉTODOS ----------------
        void mover(Jugador *);
        void comprobarColisiones(vector<RectangleShape *> *);
        void comprobarColisionesEnUnaDireccion(RectangleShape *, char);
        void separaObjetos(vector<ObjetoMapa *> *);
        void cogerArma(RectangleShape);
        void cogerLlave(RectangleShape);
        void cogerBomba(RectangleShape);
        void cogerPocion(RectangleShape);
        void cogerObjetoMetaNivel(RectangleShape);

        void comprobarRocas();
        void comprobarRocasEnUnaDireccion(Roca *, char);

        void comprobarCajas();
        void comprobarCajasEnUnaDireccion(Caja *, char);

        void comprobarPuertas();
        void comprobarPuertasEnUnaDireccion(Puerta *, char);
        void abrirPuerta();

        void comprobarEnemigos();
        void comprobarEnemigosEnUnaDireccion(Enemigo *, char);

        void cambiarArma();
        void acuchillar(vector<Enemigo *> *);
        void tirarBomba();
        void controles();

        //void comprobarEscaleras(vector<RectangleShape *> *);
        //void comprobarEscalerasEnUnaDireccion(RectangleShape *, char);
        // ------ FIN MÉTODOS ----------------






    private:

};

#endif // JUGADOR_H
