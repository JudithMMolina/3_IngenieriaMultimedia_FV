#ifndef CAJA_H
#define CAJA_H

#include <ObjetoMapa.h>

using namespace sf;
using namespace std;

class Caja : public ObjetoMapa
{
    public:
        Caja(float posX, float posY, int tipo);
        virtual ~Caja();

    protected:

    private:
};

#endif // CAJA_H
