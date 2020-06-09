#ifndef LLAVE_H
#define LLAVE_H

#include <ObjetoMapa.h>

class Llave : public ObjetoMapa
{
    public:
        Llave(float posX, float posY, int tipo);
        virtual ~Llave();

    protected:

    private:
};

#endif // LLAVE_H
