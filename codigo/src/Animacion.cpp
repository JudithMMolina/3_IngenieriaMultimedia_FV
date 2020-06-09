#include "Animacion.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Animacion::Animacion(Sprite* sprite, sf::Time nuevoTiempoFrame, bool pausa)
{
    spritePadre = sprite;
    //spritePadre->setScale(0.75,0.75);
    tiempoFrame = nuevoTiempoFrame;
    frameActual = 0;
    estaPausado = pausa;
}

Animacion::~Animacion()
{
    //dtor
}

void Animacion::anyadirFrame(sf::IntRect sprite)
{
    frames.push_back(sprite);
    //cout << "Tenemos " << frames.size() << " frames" << endl;
}

void Animacion::anyadirFrames(int iniFrames, int finFrames, int fila, int rectMeasure) //Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight)
{
    while(iniFrames != finFrames+1) {
        frames.push_back(IntRect(iniFrames*rectMeasure, fila*rectMeasure, rectMeasure, rectMeasure));
        iniFrames++;
    }
}

int Animacion::getSize() const
{
    return frames.size();
}


void Animacion::update(sf::Time tiempo)
{
    //cout << "Esta pausado " << estaPausado << endl;
    //cout << "frames.empty() " << frames.empty() << endl;
    //cout << "Textura null " << (spritePadre->getTexture() == nullptr) << endl;
    // Si no esta pausado y tenemos una animacion valida
    if (!estaPausado && !frames.empty() && spritePadre->getTexture() != nullptr)
    {
        // Anyade tiempo delta
        tiempoActual += tiempo;

        // Si la hora actual es mayor, entonces el tiempo de frame avanza un frame
        if (tiempoActual >= tiempoFrame)
        {
            // Restablecer el tiempo, pero mantener el resto
            tiempoActual = sf::microseconds(tiempoActual.asMicroseconds() % tiempoFrame.asMicroseconds());

            // Obtener el siguiente indice de frame
            if (frameActual + 1 < getSize())
                frameActual++;
            else
            {
                // La animacion ha terminado
                frameActual = 0; // Reiniciar para iniciar
            }
            // Establece el frame actual, no restableciendo el tiempo
            setFrame(frameActual, false);
        }
    }
}

void Animacion::play()
{
    estaPausado = false;
}

void Animacion::pause()
{
    estaPausado = true;
}

void Animacion::stop()
{
    estaPausado = true;
    frameActual = 0;
    setFrame(frameActual);
}

void Animacion::setFrame(int nuevoFrame, bool restaurarTiempo)
{
    if (!frames.empty() && spritePadre->getTexture() != nullptr)
    {
        sf::IntRect rect = frames[nuevoFrame];
        spritePadre->setTextureRect(rect);
    }

    if (restaurarTiempo)
        tiempoActual = sf::Time::Zero;
}

void Animacion::setTiempoFrame(sf::Time tiempo)
{
    tiempoFrame = tiempo;
}


sf::Time Animacion::getTiempoFrame() const
{
    return tiempoFrame;
}
