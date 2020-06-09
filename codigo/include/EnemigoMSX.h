#ifndef ENEMIGOMSX_H
#define ENEMIGOMSX_H

#include <vector>
#include <stdlib.h>
#include <math.h>

#include <Enemigo.h>

#include <SFML/Graphics.hpp>

class EnemigoMSX: public Enemigo
{
    public:
        EnemigoMSX(int w,int h);
        virtual ~EnemigoMSX();

        void update(Jugador *jugador1, Jugador *jugador2, Mapa *mapa);
        void render(sf::RenderWindow *window);
        void resetPositionBall();
        void resetPositionBall(int bola);
        void resetPositionSuperf(int supef);
        void calculPositionSuperf();
        void movimientoBolaHielo(Jugador *jugador1, Jugador *jugador2);
        void animacionExplosion();
        void fasesEnemigo();
        void animarDanyo();
        void animarBola();
        void pintarVida(sf::RenderWindow *window);

        int getGenerarEnemigos(){return generarEnemigos;}

    protected:

    private:
        sf::Texture texture;
        sf::Texture texBolaHielo;
        sf::Texture texSuperficie;
        sf::Texture texExplosion;
        sf::Sprite bolaHielo;
        sf::Sprite superficie;
        sf::RectangleShape centroBolaHielo;
        sf::Clock animacionClock;
        sf::Clock explosionClock;
        sf::Clock explosionClock2;
        sf::Clock explosionClock3;
        sf::Clock explosionClock4;
        sf::Clock explosionClock5;
        sf::Clock spawnEnemigos;
        sf::Sprite explosion;
        sf::Sprite explosion2;
        sf::Sprite explosion3;
        sf::Sprite explosion4;
        sf::Sprite explosion5;


        bool resetearRelojExplosion;
        bool resetearRelojExplosion2;
        bool resetearRelojExplosion3;
        bool resetearRelojExplosion4;
        bool resetearRelojExplosion5;
        bool regenerarSuperf;
        int generarEnemigos;


        std::vector<sf::Sprite> bolasHielo;
        std::vector<sf::Sprite> superficies;
        std::vector<sf::RectangleShape> bolasCentro; // para tener una colision mas realista donde la bola baje del todo
        std::vector<float> unitarioX;
        std::vector<float> unitarioY;
        std::vector<float> explosionPosX;
        std::vector<float> explosionPosY;


        float vecBolaSuperfX;
        float vecBolaSuperfY;
        float vecMagBolaSuperf;
        float divVecBolaSuperf;
        float angleRads;
        float angleDegs;
        float PI;
        bool empezarMovimiento;
        int ancho;
        int alto;

        static const float VELOCIDAD_BOLAS_MSX;




};

#endif // ENEMIGOMSX_H
