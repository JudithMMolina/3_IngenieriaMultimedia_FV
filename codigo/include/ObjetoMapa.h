#ifndef OBJETOMAPA_H
#define OBJETOMAPA_H

#include <SFML/Graphics.hpp>
#include <Motor2D.h>

using namespace sf;


class ObjetoMapa
{
    public:
        ObjetoMapa(float posX, float posY, int tipoPocion);
        virtual ~ObjetoMapa();

        //virtual void update() {};
        virtual void update();

        Sprite* getSprite() {return sprite;}

        bool getCogible() { return cogible; }

        void setCogible( bool var ) { cogible = var; }

        bool getPintable() { return pintable; }

        void setPintable( bool var ) { pintable = var; }
        bool isVisible()
        {
            if(sprite->getGlobalBounds().intersects(Motor2D::getViewRect()))
                return true;
            return false;
        }

    protected:
        Sprite *sprite;
        bool cogible;
        bool pintable;

        Clock objetoClock;


    private:
};

#endif // OBJETOMAPA_H
