#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace sf;

class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
        TileMap();
        virtual ~TileMap();
        TileMap(const string&, sf::Vector2u, const int*, unsigned int, unsigned int);
        bool load(const string&, sf::Vector2u, const int*, unsigned int, unsigned int);
        int getTilePositionFromCoords(int x, int y);
        vector<sf::Sprite *> GetVertexArray();
        void cambiarTextura(int posVector, int nuevoNumTile);


    private:
        vector<sf::Sprite *> vectorSprites;
        sf::Texture textureTile;
        int width;
        int height;
        sf::Vector2u tileSizeX;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
