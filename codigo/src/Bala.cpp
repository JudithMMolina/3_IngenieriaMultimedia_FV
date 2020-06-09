#include "Bala.h"
#include "Arma.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Jugador;
class Enemigo;

Bala::Bala(Arma* a, vector<Enemigo *> *nuevosEnemigos, int d)
{
    sf::Texture *tx = new Texture();
    if(tx->loadFromFile("./resources/flechas.png"))
        sprite = new sf::Sprite(*tx);

    getSprite()->setScale(sf::Vector2f(0.5,0.5));
    getSprite()->setPosition(sf::Vector2f (a->getJugador()->getSprite()->getPosition().x + 20.0,a->getJugador()->getSprite()->getPosition().y +26.0));
    arma = a;
    enemigos = nuevosEnemigos;
    danyo = d;
    colision = false;

    paredes = arma->getJugador()->getMapa()->getRectangulosParedes();

    sf::Vector2f dir = sf::Vector2f(*arma->getJugador()->getDireccionBala());

    direccion = dir;

    cambiaSprite(dir);
}

Bala::~Bala()
{
    if(sprite != nullptr){
        delete sprite;
    }
    arma = nullptr;
    enemigos = nullptr;
    paredes = nullptr;
}



void Bala::cambiaSprite(sf::Vector2f dir){

    if(dir == sf::Vector2f(0,-1))
        sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));

    if(dir == sf::Vector2f(1,0))
        sprite->setTextureRect(sf::IntRect(32, 0, 32, 32));

    if(dir == sf::Vector2f(0,1))
        sprite->setTextureRect(sf::IntRect(64, 0, 32, 32));

    if(dir == sf::Vector2f(-1,0))
        sprite->setTextureRect(sf::IntRect(96, 0, 32, 32));

    if(dir == sf::Vector2f(1,-1))
        sprite->setTextureRect(sf::IntRect(0, 32, 32, 32));

    if(dir == sf::Vector2f(1,1))
        sprite->setTextureRect(sf::IntRect(32, 32, 32, 32));

    if(dir == sf::Vector2f(-1,1))
        sprite->setTextureRect(sf::IntRect(64, 32, 32, 32));

    if(dir == sf::Vector2f(-1,-1))
        sprite->setTextureRect(sf::IntRect(96, 32, 32, 32));

}


void Bala::update(){
    mover();
    colisionaEnemigo();
    colisionaParedes();
}

void Bala::mover(){
    sprite->setPosition(sprite->getPosition().x + direccion.x * v_bala, sprite->getPosition().y + direccion.y * v_bala);
}

 void Bala::colisionaEnemigo()
 {

    for(int i=0; i<enemigos->size();i++)
    {
        if((*enemigos)[i]->getSprite()->getGlobalBounds().intersects(sprite->getGlobalBounds())){
            (*enemigos)[i]->bajarVida(danyo);
            colision = true;
        }
    }
 }

 void Bala::colisionaParedes()
 {
    for(int i=0; i<paredes->size();i++)
    {
        RectangleShape *pared = (*paredes)[i];
        if(pared->getGlobalBounds().intersects(sprite->getGlobalBounds()))
        {
            colision = true;
        }
    }
 }


void Bala::render() {
    Juego::getInstance()->getWindow()->draw(*sprite);
}

