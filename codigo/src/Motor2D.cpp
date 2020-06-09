#include "Motor2D.h"

#include <SFML/Graphics.hpp>
#include <Juego.h>
#include <Constantes.h>
#include <iostream>

using namespace sf;
using namespace std;

Text* Motor2D::getDefaultText()
{
    sf::Text *text = new sf::Text();
    text->setPosition(sf::Vector2f(1.0, 1.0));
    sf::Font *font = new sf::Font();
    if(!font->loadFromFile("resources/SuperMario256.ttf")) {
        std::cout << "No se puede cargar la fuente" << std::endl;
    }
    text->setCharacterSize(/*24*/32);
    text->setColor(sf::Color::White);
    text->setFont(*font);
    text->setStyle(sf::Text::Bold /*| sf::Text::Underlined*/);

    return text;
}


Texture* Motor2D::getTextureFromFile(string nombreArchivo) {
    Texture *textura = new Texture();
    if(!textura->loadFromFile(nombreArchivo)){
        delete [] textura;
        textura = nullptr;
        return nullptr;
    }
    return textura;
}


Texture *Motor2D::capturarPantalla()
{
    Texture *texture = new Texture();
    RenderWindow *window = Juego::getInstance()->getWindow();
    texture->create(window->getSize().x, window->getSize().y);
    texture->update(*window);
    return texture;
}


void Motor2D::centrarView()
{
    Juego::getInstance()->getView()->setCenter(Constantes::TAMANYO_VENTANA_X / 2, Constantes::TAMANYO_VENTANA_Y /2);
}


FloatRect Motor2D::getViewRect()
{
    sf::Vector2i viewCenter(Juego::getInstance()->getView()->getCenter()); // this returns the center of the view IN THE WORLD!
    sf::Vector2i viewSize(Juego::getInstance()->getView()->getSize());

    sf::FloatRect currentViewRect
            (viewCenter.x - viewSize.x / 2, // left
            viewCenter.y - viewSize.y / 2, // top
            viewSize.x,
            viewSize.y);
    return currentViewRect;
}
