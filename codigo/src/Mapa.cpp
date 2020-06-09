#include "Mapa.h"
#include "Constantes.h"

using namespace std;
using namespace sf;

Mapa::Mapa()
{
    //ctor
    tilemapsDelante = new vector<TileMap*>();
    tilemapsDetras = new vector<TileMap*>();
    rectangulosAgua = new vector<RectangleShape*>();
    rectangulosElectricidad = new vector<RectangleShape*>();
    rectangulosParedes = new vector<RectangleShape*>();
    rectangulosEscaleras = new vector<RectangleShape*>();
}

Mapa::~Mapa()
{
    //dtor
    tilemapsDelante->clear();
    tilemapsDelante->shrink_to_fit();
    delete tilemapsDelante;
    tilemapsDetras->clear();
    tilemapsDetras->shrink_to_fit();
    delete tilemapsDetras;
    rectangulosAgua->clear();
    rectangulosAgua->shrink_to_fit();
    delete rectangulosAgua;
    rectangulosElectricidad->clear();
    rectangulosElectricidad->shrink_to_fit();
    delete rectangulosElectricidad;
    rectangulosParedes->clear();
    rectangulosParedes->shrink_to_fit();
    delete rectangulosParedes;
    rectangulosEscaleras->clear();
    rectangulosEscaleras->shrink_to_fit();
    delete rectangulosEscaleras;
}

void Mapa::draw(RenderTarget& target, RenderStates states) const
{

}

void Mapa::pintarDelante(RenderWindow &window) {
    int numTileMaps = tilemapsDelante->size();
    for(int i = 0; i < numTileMaps; i++) {
        window.draw(*(*tilemapsDelante)[i]);
    }
}

void Mapa::pintarDetras(sf::RenderWindow &window) {
    int numTileMaps = tilemapsDetras->size();
    for(int i = 0; i < numTileMaps; i++) {
        window.draw(*(*tilemapsDetras)[i]);
    }
}

void Mapa::pintarRectangulosParedes(sf::RenderWindow &window) {
    if(Constantes::DEBUG) {
        int numTileMaps = rectangulosParedes->size();
        for(int i = 0; i < numTileMaps; i++) {
            window.draw(*(*rectangulosParedes)[i]);
        }
    }
}

void Mapa::pintarRectangulosAgua(sf::RenderWindow &window) {
    if(Constantes::DEBUG) {
        int numTileMaps = rectangulosAgua->size();
        for(int i = 0; i < numTileMaps; i++) {
            window.draw(*(*rectangulosAgua)[i]);
        }
    }
}

void Mapa::pintarRectangulosElectricidad(sf::RenderWindow &window) {
    if(Constantes::DEBUG) {
        int numTileMaps = rectangulosElectricidad->size();
        for(int i = 0; i < numTileMaps; i++) {
            window.draw(*(*rectangulosElectricidad)[i]);
        }
    }
}


void Mapa::pintarRectangulosEscaleras(sf::RenderWindow &window) {
    if(Constantes::DEBUG) {
        int numTileMaps = rectangulosEscaleras->size();
        for(int i = 0; i < numTileMaps; i++) {
            window.draw(*(*rectangulosEscaleras)[i]);
        }
    }
}
