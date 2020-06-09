#ifndef ENEMIGOESTATICO_H
#define ENEMIGOESTATICO_H
#include <Enemigo.h>


class EnemigoEstatico : public Enemigo
{
    public:
        EnemigoEstatico(float posX, float posY);
        virtual ~EnemigoEstatico();

        void update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa, sf::Time timeElapsed);
        void render(sf::RenderWindow *window, double percentTick);
        void animacionExplosion();
        void animacionMovimineto();
        void bajarVidaJugador1(Jugador *jugador1);
        void bajarVidaJugador2(Jugador *jugador2);
        void calcularDireccion(float distancia1, float distancia2, Jugador *jugador1, Jugador *jugador2);
        void animacionDisparo();
        void animacionReposo();
        void chocarBalas(sf::Time timeElapsed, Jugador *jugador1, Jugador *jugador2, vector<RectangleShape *> *rectangulos );
        void anyadirBala();

    private:
        sf::Texture texBala;
        sf::Sprite* bala0;
        sf::Clock rangeClock;
        sf::Clock animacionClock;
        sf::Clock tocadoClock;
        std::vector<sf::Sprite*> todasBalas0;
        std::vector<float> posXAnterior;
        std::vector<float> posYAnterior;
        std::vector<float> posXSiguiente;
        std::vector<float> posYSiguiente;
        std::vector<int> rotAnterior;
        std::vector<int> rotSiguiente;


        std::vector<float> unitarioX;
        std::vector<float> unitarioY;

        int direccion_enemigo2;
        bool bala_eliminada; //paa saber si la bala se ha eliminado ya
        bool colision_personaje;

        float angleRads;
        float angleDegs;
        float PI;

        float vectorX;
        float vectorY;
        float vMagnitud;
        float divisorUnitario;
        float distancia;

        bool dentroDelRadio;
        bool tocado;
};

#endif // ENEMIGOESTATICO_H
