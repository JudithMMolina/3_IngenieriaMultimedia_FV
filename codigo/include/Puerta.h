#ifndef PUERTA_H
#define PUERTA_H

#include <ObjetoMapa.h>


class Puerta : public ObjetoMapa
{
    public:
        Puerta(float posX, float posY, int tipo);
        virtual ~Puerta();

        bool getAbrible(){
            return abrible;
        }
        void setAbrible(bool var){
            abrible = var;
        }
        bool getAbierta(){
            return abierta;
        }
        void setAbierta(bool var){
            abierta = var;
        }
        int getTipo(){
            return tipoLocal;
        }
        void abrir();
    protected:
        bool abrible;
        int tipoLocal;
        bool abierta;
    private:
};

#endif // PUERTA_H
