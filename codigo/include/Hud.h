#ifndef HUD_H
#define HUD_H

#include "SFML/Graphics.hpp"
#include <Jugador.h>

class Hud
{
    public:
        Hud(int, Jugador*);
        virtual ~Hud();

        void update();
        void render();

        void cargarTexturas();
        void queArma(std::string&, std::string&);

        void moverHud();

    protected:

    private:

        Jugador *jugador;

        sf::Text *textovida;

        sf::Sprite* fondo;
        sf::Sprite* daga;
        sf::Sprite* bomba;
        sf::Sprite* llave;
        sf::Sprite* arma1;
        sf::Sprite* arma2;
        sf::Sprite* seleccion;
        sf::Sprite* seleccion2;

        int tipoHud;


        std::string imgh1 = "./resources/Hud1.png";
        std::string imgh2 = "./resources/Hud2.png";
        std::string cuchillo = "./resources/cuchillo.png";
        std::string imgbomba = "./resources/bomba.png";
        std::string imgbombaG = "./resources/bombaG.png";
        std::string imgllave =  "./resources/llave.png";
        std::string imgllaveG =  "./resources/llaveG.png";
        std::string imgarma1 = "./resources/arma1.png";
        std::string imgarma2 = "./resources/arma2.png";
        std::string imgarma1G = "./resources/arma1G.png";
        std::string imgarma2G = "./resources/arma2G.png";
        std::string imgselec = "./resources/seleccion.png";
        std::string imgselec2 = "./resources/seleccion2.png";

};


#endif // HUD_H
