#ifndef MAPA_H
#define MAPA_H

#include <SFML/Graphics.hpp>
#include <TileMap.h>

using namespace sf;

class Mapa : public sf::Drawable
{
    public:
        Mapa();
        virtual ~Mapa();
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
        void pintarDelante(sf::RenderWindow &);
        void pintarDetras(sf::RenderWindow &);
        void pintarRectangulosParedes(sf::RenderWindow &);
        void pintarRectangulosElectricidad(sf::RenderWindow &);
        void pintarRectangulosAgua(sf::RenderWindow &);
        void pintarRectangulosEscaleras(sf::RenderWindow &);
        void pintarRectangulosCajas(sf::RenderWindow &);

        static const int tamanyoZonaCalienteDch = 256;
        static const int tamanyoZonaCalienteIzq = tamanyoZonaCalienteDch - 64;
        static const int tamanyoZonaCalienteAbajo = 220;
        static const int tamanyoZonaCalienteArriba = 100;


        // --------GETTERS y SETTERS---------
        vector<sf::RectangleShape *> *getRectangulosParedes() {
            return rectangulosParedes;
        }
        vector<sf::RectangleShape *> *getRectangulosAgua() {
            return rectangulosAgua;
        }
        vector<sf::RectangleShape *> *getRectangulosElectricidad() {
            return rectangulosElectricidad;
        }
        vector<sf::RectangleShape *> *getRectangulosEscaleras() {
            return rectangulosEscaleras;
        }
        vector<TileMap *> *getTileMapsDelante() {
            return tilemapsDelante;
        }
        vector<TileMap *> *getTileMapsDetras() {
            return tilemapsDetras;
        }
        void setMapaCalorParedes(int **mapaNuevo) {
            mapaCalorParedes = mapaNuevo;
        }
        int **getMapaCalorParedes() {
            return mapaCalorParedes;
        }
        void setMapTileWidth(int mapTileWidthNew){
            mapTileWidth = mapTileWidthNew;
        }
        void setMapTileHeight(int mapTileHeightNew){
            mapTileHeight = mapTileHeightNew;
        }
        void setTileSizeX(int tileSizeXNew){
            tileSizeX = tileSizeXNew;
        }
        void setTileSizeY(int tileSizeYNew){
            tileSizeY = tileSizeYNew;
        }
        int getMapTileWidth(){
            return mapTileWidth;
        }
        int getMapTileHeight(){
            return mapTileHeight;
        }
        int getTileSizeX(){
            return tileSizeX;
        }
        int getTileSizeY(){
            return tileSizeY;
        }

        // --------END GETTERS---------

    protected:

    private:
        vector<TileMap *> *tilemapsDelante;
        vector<TileMap *> *tilemapsDetras;
        vector<sf::RectangleShape *> *rectangulosParedes;
        vector<sf::RectangleShape *> *rectangulosAgua;
        vector<sf::RectangleShape *> *rectangulosElectricidad;
        vector<sf::RectangleShape *> *rectangulosEscaleras;

        int **mapaCalorParedes;
        int tileSizeX;
        int tileSizeY;
        int mapTileHeight;
        int mapTileWidth;
};

#endif // MAPA_H
