#ifndef ENEMIGOEXPLOSIVO_H
#define ENEMIGOEXPLOSIVO_H
#include "Enemigo.h"

class EnemigoExplosivo : public Enemigo
{
    public:
        EnemigoExplosivo(int posX,int posY);
        virtual ~EnemigoExplosivo();

        void update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa);
        void render(sf::RenderWindow *window);
        void animacionExplotar();
        void animacionMovimiento();
        void moverBloqueo(sf::Sprite &sprite ,sf::Sprite &spriteMuro, int direccionEnemigo1);
        void calcularColisionesMapa(int direccionEnemigo1 ,vector<RectangleShape *> *rectangulos, float angulo);
        void bajarVidaJugador1(Jugador *jugador1);
        void bajarVidaJugador2(Jugador *jugador2);
        void animacionReposo();



    protected:

    private:
        sf::Clock animacionExplosion;
        sf::Clock animacionAndarClock;
        sf::Clock rangeClock;

        static const int RANGO_DETECCION;
        static const int RANGO_PARPADEO;
        float distancia;
        bool dentroDelRadio;
        sf::Sprite *spriteExplosion;
        bool mostrar;
        bool animacionExplotarMuerte;

};

#endif // ENEMIGOEXPLOSIVO_H
