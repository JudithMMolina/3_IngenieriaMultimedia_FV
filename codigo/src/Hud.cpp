#include "Hud.h"
#include <Motor2D.h>
#include <Constantes.h>
#include <Juego.h>

using namespace sf;

Hud::Hud(int num, Jugador *j)
{
    tipoHud = num;
    jugador = j;

    textovida = Motor2D::getDefaultText();

    std::string archivo = "";
    std::string sel = "";

    if(tipoHud == 1){
        archivo = imgh1;
        sel = imgselec2;
    }
    else{
        archivo = imgh2;
        sel = imgselec2;
    }

    sf::Texture *img = Motor2D::getTextureFromFile(archivo);
    if(img != nullptr)
        fondo = new sf::Sprite(*img);

    sf::Texture *txseleccion = Motor2D::getTextureFromFile(sel);
    if(txseleccion != nullptr)
        seleccion = new sf::Sprite(*txseleccion);

    sf::Texture* txdaga = Motor2D::getTextureFromFile(cuchillo);
    if(txdaga != nullptr)
        daga = new sf::Sprite(*txdaga);


    if(jugador->tieneBomba())
    {
        Texture *textura = Motor2D::getTextureFromFile(imgbomba);
        if(textura != nullptr)
            bomba = new sf::Sprite(*textura);
    }
    else{
        Texture *textura = Motor2D::getTextureFromFile(imgbombaG);
        if(textura != nullptr)
            bomba = new sf::Sprite(*textura);
    }

    if(jugador->tieneLlave())
    {
        sf::Texture *txllave = Motor2D::getTextureFromFile(imgllave);
        if(txllave != nullptr)
            llave = new sf::Sprite(*txllave);
    }
    else{
        sf::Texture *txllave = Motor2D::getTextureFromFile(imgllaveG);
        if(txllave != nullptr)
            llave = new sf::Sprite(*txllave);
    }

    if(jugador->queArma() == 0){
        sf::Texture *txarco1 = Motor2D::getTextureFromFile(imgarma1G);
        sf::Texture *txarco2 = Motor2D::getTextureFromFile(imgarma2G);
        if(txarco1 != nullptr)
            arma1 = new sf::Sprite(*txarco1);
        if(txarco2 != nullptr)
            arma2 = new sf::Sprite(*txarco2);
    }
    else if(jugador->queArma() == 1){
        sf::Texture *txarco1 = Motor2D::getTextureFromFile(imgarma1);
        sf::Texture *txarco2 = Motor2D::getTextureFromFile(imgarma2G);
        if(txarco1 != nullptr)
            arma1 = new sf::Sprite(*txarco1);
        if(txarco2 != nullptr)
            arma2 = new sf::Sprite(*txarco2);

    }
    else if(jugador->queArma() == 2){
        sf::Texture *txarco2 = Motor2D::getTextureFromFile(imgarma2);
        sf::Texture *txarco1 = Motor2D::getTextureFromFile(imgarma1G);
        if(txarco2 != nullptr)
            arma2 = new sf::Sprite(*txarco2);
        if(txarco1 != nullptr)
            arma1 = new sf::Sprite(*txarco1);

    }
    else if(jugador->queArma() == 3){
        sf::Texture *txarco1 = Motor2D::getTextureFromFile(imgarma1);
        sf::Texture *txarco2 = Motor2D::getTextureFromFile(imgarma2);
        if(txarco1 != nullptr)
            arma1 = new sf::Sprite(*txarco1);
        if(txarco2 != nullptr)
            arma2 = new sf::Sprite(*txarco2);
    }

    textovida->setCharacterSize(27);

    moverHud();

}

Hud::~Hud()
{
    //dtor
}


void Hud::cargarTexturas()
{

    std::string archivo = "";
    std::string sel = "";


    if(jugador->tieneBomba())
    {
        Texture *textura = Motor2D::getTextureFromFile(imgbomba);
        if(textura != nullptr)
            bomba->setTexture(*textura);
    }
    else{
        Texture *textura = Motor2D::getTextureFromFile(imgbombaG);
        if(textura != nullptr)
            bomba->setTexture(*textura);
    }

    if(jugador->tieneLlave())
    {
        sf::Texture *txllave = Motor2D::getTextureFromFile(imgllave);
        if(txllave != nullptr)
            llave->setTexture(*txllave);
    }
    else{
        sf::Texture *txllave = Motor2D::getTextureFromFile(imgllaveG);
        if(txllave != nullptr)
            llave->setTexture(*txllave);
    }

    std::string txarco1 = "";
    std::string txarco2 = "";

    queArma(txarco1, txarco2);
    sf::Texture *txa1 = Motor2D::getTextureFromFile(txarco1);
    sf::Texture *txa2 = Motor2D::getTextureFromFile(txarco2);
    if(txa1 != nullptr)
        arma1->setTexture(*txa1);
    if(txa2 != nullptr)
        arma2->setTexture(*txa2);
}

void Hud::queArma(std::string &txa1, std::string &txa2){
    switch(jugador->queArma()){
        case 0: txa1 = imgarma1G;   txa2 = imgarma2G;   break;
        case 1: txa1 = imgarma1;    txa2 = imgarma2G;   break;
        case 2: txa1 = imgarma1G;   txa2 = imgarma2;    break;
        case 3: txa1 = imgarma1;    txa2 = imgarma2;    break;
    }
}


void Hud::moverHud(){


    if(tipoHud == 1){
        sf::Vector2f posEnMapa = Juego::getInstance()->getWindow()->mapPixelToCoords(Vector2i(Constantes::posXhud1, Constantes::posYhud1));
        fondo->setPosition(posEnMapa);

        int posfondoX = fondo->getPosition().x;
        int posfondoY = fondo->getPosition().y;

        daga->setPosition(posfondoX + Constantes::posXdata1, posfondoY + Constantes::posYdata1);
        textovida->setPosition(posfondoX + Constantes::posXvida1, posfondoY + Constantes::posYvida);
        bomba->setPosition(posfondoX + Constantes::posXbomb1, posfondoY + Constantes::posYbomb1);
        llave->setPosition(posfondoX + Constantes::posXllave1, posfondoY + Constantes::posYllave1);
        arma1->setPosition(posfondoX + Constantes::posXarma11, posfondoY + Constantes::posYarma);
        arma2->setPosition(posfondoX + Constantes::posXarma12, posfondoY + Constantes::posYarma);
    }
    else{
        sf::Vector2f posEnMapa = Juego::getInstance()->getWindow()->mapPixelToCoords(Vector2i(Constantes::posXhud2, Constantes::posYhud2));
        fondo->setPosition(posEnMapa);

        int posfondoX = fondo->getPosition().x;
        int posfondoY = fondo->getPosition().y;

        daga->setPosition(posfondoX + Constantes::posXdata2, posfondoY + Constantes::posYdata2);
        textovida->setPosition(posfondoX + Constantes::posXvida2, posfondoY + Constantes::posYvida);
        bomba->setPosition(posfondoX + Constantes::posXbomb2, posfondoY + Constantes::posYbomb2);
        llave->setPosition(posfondoX + Constantes::posXllave2, posfondoY + Constantes::posYllave2);
        arma1->setPosition(posfondoX + Constantes::posXarma21, posfondoY + Constantes::posYarma);
        arma2->setPosition(posfondoX + Constantes::posXarma22, posfondoY + Constantes::posYarma);
    }


    int vida = jugador->getVida();
    textovida->setString(std::to_string(vida) + "%");

    switch(jugador->queTieneSeleccionado()){
        case 0: seleccion->setPosition(daga->getPosition().x - 12, daga->getPosition().y -5);   break;
        case 1: seleccion->setPosition(arma1->getPosition().x - 6, arma1->getPosition().y -5);   break;
        case 2: seleccion->setPosition(arma2->getPosition().x - 6, arma2->getPosition().y -5);   break;
        case 3: seleccion->setPosition(bomba->getPosition().x - 6, bomba->getPosition().y -5);   break;
    }
}



void Hud::update()
{
    cargarTexturas();


}



void Hud::render()
{
    moverHud();

    Juego::getInstance()->getWindow()->draw(*fondo);
    Juego::getInstance()->getWindow()->draw(*seleccion);
    Juego::getInstance()->getWindow()->draw(*daga);
    Juego::getInstance()->getWindow()->draw(*textovida);
    //if(jugador->tieneBomba())
        Juego::getInstance()->getWindow()->draw(*bomba);
    if(jugador->tieneLlave())
        Juego::getInstance()->getWindow()->draw(*llave);
    if(arma1 != nullptr)
        Juego::getInstance()->getWindow()->draw(*arma1);
    if(arma2 !=nullptr)
        Juego::getInstance()->getWindow()->draw(*arma2);
}
