#ifndef BALA_H
#define BALA_H

#include <iostream>
#include <Enemigo.h>
#include <Juego.h>


using namespace std;
using namespace sf;

class Bala
{
    public:
        Bala(Arma*, vector<Enemigo *> *, int);
        virtual ~Bala();
        void update();
        void mover();
        void colisionaEnemigo();
        void colisionaParedes();
        void cambiaSprite(sf::Vector2f);

        sf::Sprite* getSprite(){return sprite;}
        bool getColisionado(){return colision;}
        void render();
        bool isVisible()
        {
            if(sprite->getGlobalBounds().intersects(Motor2D::getViewRect()))
                return true;
            return false;
        }


    protected:

    private:
        const float v_bala = 10.0f;
        Vector2f direccion;
        Sprite* sprite;
        vector<Enemigo *> *enemigos;
        Arma *arma;
        int danyo;
        bool colision;

        std::vector<RectangleShape*> *paredes;



};

#endif // BALA_H
