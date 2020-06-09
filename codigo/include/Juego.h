#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <State.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Juego
{
    public:
        static Juego* getInstance();
        //void setState(State *);
        void setState(State::Estados tipoEstado);
        State* getState() { return stateActual; };
        State* getStateAnterior() { return stateAnterior; };
        void iniciar();
        RenderWindow *getWindow() { return window; }
        View *getView() { return view; }
        Vector2f *getDireccionView() { return direccionView; }
        void pausar();
        void volverDePausa();
        void borrarStateAnterior();

    protected:


    private:
        std::string *nombre;
        static Juego *juego;
        State::Estados estadoActual;
        State *stateActual;
        State *stateAnterior;
        RenderWindow *window;
        View *view;
        Vector2f *direccionView;

        Juego();
        virtual ~Juego();
        void buclePrincipal();

};

#endif // JUEGO_H
