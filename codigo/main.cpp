#include <SFML/Graphics.hpp>
#include <Juego.h>

//#include <StateIntro.h> //esto era antes cuando a setState le pasabamos el puntero al estado
#include<SFML/System.hpp>

int main()
{
    Juego *juego = Juego::getInstance();
    //StateIntro *intro = new StateIntro();
    //juego->setState(intro); //cambio state
    juego->setState(State::Estados::INTRO);
    juego->iniciar();

    return EXIT_SUCCESS;
}
