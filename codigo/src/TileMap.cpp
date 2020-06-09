#include "TileMap.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

TileMap::TileMap() {

}

TileMap::~TileMap() {
    vectorSprites.clear();
    vectorSprites.shrink_to_fit();
}

TileMap::TileMap(const string& tileset, sf::Vector2u nuevoTileSize, const int* tiles, unsigned int nuevoWidth, unsigned int nuevoHeight) {
    load(tileset, nuevoTileSize, tiles, nuevoWidth, nuevoHeight);
}

bool TileMap::load(const string& tileset, sf::Vector2u nuevoTileSize, const int* tiles, unsigned int nuevoWidth, unsigned int nuevoHeight)
{
        vectorSprites.clear();
        // ancho en tiles del mapa completo
        width = nuevoWidth;
        // alto en tiles del mapa completo
        height = nuevoHeight;

        // tamaño de cada uno de los tiles
        tileSizeX = nuevoTileSize;

        // cargamos la textura desde el disco
        if (!textureTile.loadFromFile(tileset))
            return false;


        // populate the vertex array, with one quad per tile
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                // get the current tile number
                int num_tile = tiles[i + j * width] - 1;

                // find its position in the tileset texture
                int tu = num_tile % (textureTile.getSize().x / tileSizeX.x);
                int tv = num_tile / (textureTile.getSize().x / tileSizeX.x);

                sf::Sprite* quad;
                if(num_tile > 0) {
                    quad = new sf::Sprite(textureTile, sf::IntRect(tu * tileSizeX.x, tv * tileSizeX.y, tileSizeX.x, tileSizeX.y));
                } else {
                    quad = new sf::Sprite();
                    quad->setTexture(textureTile);
                    quad->setTextureRect(sf::IntRect(0, 0, 0,0));
                }


                sf::Vector2f position(i * tileSizeX.x, j * tileSizeX.y);
                quad->setPosition(position);
                vectorSprites.push_back(quad);
            }
        }

        return true;
}



void TileMap::cambiarTextura(int posVector, int nuevoNumTile) {
    sf::Sprite* quad = vectorSprites[posVector];

    if(nuevoNumTile == 0) {
        quad->setTextureRect(sf::IntRect(0, 0, 0,0));
    } else {
        // find its position in the tileset texture
        int tu = nuevoNumTile % (textureTile.getSize().x / tileSizeX.x);
        int tv = nuevoNumTile / (textureTile.getSize().x / tileSizeX.x);
        quad->setTextureRect(sf::IntRect(tu * tileSizeX.x, tv * tileSizeX.y, tileSizeX.x, tileSizeX.y));
    }
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    int numTiles = vectorSprites.size();
    for(int i = 0; i < numTiles; i++)
        target.draw(*vectorSprites[i]);
}


int TileMap::getTilePositionFromCoords(int x, int y) {
    int xCalc = x/tileSizeX.x;
    int yCalc = y/tileSizeX.y;
    return yCalc * width + xCalc;
}


std::vector<sf::Sprite *> TileMap::GetVertexArray() {
    return vectorSprites;
}
