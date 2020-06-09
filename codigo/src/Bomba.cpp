#include "Bomba.h"
#include "Enemigo.h"
#include "Motor2D.h"
#include "Utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;



Bomba::Bomba(float posX, float posY, int tipo) : ObjetoMapa(posX, posY, tipo)
{
    //ctor
    string archivo = "resources/bomba.png";
    Texture *textura = Motor2D::getTextureFromFile(archivo);
    if(textura != nullptr)
        sprite->setTexture(*textura);
    danyo = 40;
    rango = 60;
    tiempo = 2;
    tiempoBomba = sf::Time::Zero;
    enemigos = nullptr;
    explotado=false;
    bombaSoltada=false;
    explosionAnimacion.restart();


}

Bomba::~Bomba()
{
    //dtor
}
void Bomba::update(){
    //cout<<"Update bomba"<<endl;

    animacionBomba();
}
void Bomba::explosion(vector<Enemigo *> *enemi, vector<Caja *> *caj){
    tiempoBomba = objetoClock.getElapsedTime();
    enemigos = enemi;
    cajas = caj;
}
void Bomba::animacionBomba(){
    if(enemigos!=nullptr){
        if((objetoClock.getElapsedTime() - tiempoBomba).asSeconds() > tiempo && !bombaSoltada){
            int distancia = 0;
            for(int i = 0; i < enemigos->size(); i++){
                distancia=pow((pow((enemigos->at(i)->getSprite()->getPosition().x-sprite->getPosition().x),2)+pow(enemigos->at(i)->getSprite()->getPosition().y-sprite->getPosition().y,2)),0.5);
                //cout<<"asd: "<<distancia<<endl;
                if(distancia <= rango){
                    cout<<"Le ha dado la explosion al enemigo a una distancia de: "<<distancia <<endl;
                    enemigos->at(i)->bajarVida(danyo);
                }
            }
            for(int i = 0; i < cajas->size(); i++){
                distancia=pow((pow((cajas->at(i)->getSprite()->getPosition().x-sprite->getPosition().x),2)+pow(cajas->at(i)->getSprite()->getPosition().y-sprite->getPosition().y,2)),0.5);
                //cout<<"asd: "<<distancia<<endl;
                if(distancia <= rango){
                    cout<<"Le ha dado la explosion a la caja a una distancia de: "<<distancia <<endl;
                    //enemigos->at(i)->bajarVida(danyo);
                    cajas->at(i)->setCogible(false);
                    cajas->at(i)->setPintable(false);
                }
            }

            cogible = false;
            bombaSoltada = true;
            explosionAnimacion.restart();
            sf::Texture *texExplosion = new Texture();
            if (!texExplosion->loadFromFile("resources/Explosion_enemigo1.png"))
            {
                std::cerr << "Error cargando la imagen Explosion_enemigo1.png";
                exit(0);
            }
            sprite->setTexture(*texExplosion);
            sprite->setScale(0.4, 0.4);
            sprite->setOrigin(240/2,224/2);
            sprite->setPosition(sprite->getPosition().x+16,sprite->getPosition().y+16);
            //spriteExplosion->setPosition(sprite->getPosition());
            //break;
        }



    }
    if(bombaSoltada==true){
        if(explosionAnimacion.getElapsedTime().asSeconds()<0.05)
            sprite->setTextureRect(sf::IntRect(2*240, 1*224, 240, 224));
        else if(explosionAnimacion.getElapsedTime().asSeconds()<0.1)
            sprite->setTextureRect(sf::IntRect(1*240, 1*224, 240, 224));
        else if(explosionAnimacion.getElapsedTime().asSeconds()<0.15)
            sprite->setTextureRect(sf::IntRect(0*240, 1*224, 240, 224));
        else if(explosionAnimacion.getElapsedTime().asSeconds()<0.2)
            sprite->setTextureRect(sf::IntRect(2*240, 0*224, 240, 224));
        else if(explosionAnimacion.getElapsedTime().asSeconds()<0.25)
            sprite->setTextureRect(sf::IntRect(1*240, 0*224, 240, 224));
        else if(explosionAnimacion.getElapsedTime().asSeconds()<0.3)
            sprite->setTextureRect(sf::IntRect(0*240, 0*224, 240, 224));
        else if(explosionAnimacion.getElapsedTime().asSeconds()<0.4){
            explotado=true;
            pintable = false;
        }

    }
}
