#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;

class Animacion
{
    public:
        Animacion(Sprite* sprite, sf::Time nuevoTiempoFrame = sf::seconds(0.2f), bool pausa = false);
        virtual ~Animacion();

        void anyadirFrame(sf::IntRect sprite);
        void anyadirFrames(int iniFrames, int finFrames, int fila, int rectMeasure); //Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight)
        const sf::Texture* getSpriteSheet() const;
        int getSize() const;
        void update(sf::Time tiempo);
        void play();
        void pause();
        void stop();
        void setFrame(int nuevoFrame, bool restaurarTiempo = true);
        void setTiempoFrame(sf::Time tiempo);
        sf::Time getTiempoFrame() const;

        void resetFrameActual(){
            frameActual = 0;
        }

        int getFrameActual() { return frameActual; }

    protected:

    private:
        Sprite* spritePadre;
        std::vector<sf::IntRect> frames;
        sf::Time tiempoFrame;
        sf::Time tiempoActual;
        int frameActual;
        bool estaPausado;
};

#endif // ANIMACION_H
