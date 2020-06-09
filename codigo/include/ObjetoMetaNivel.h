#ifndef OBJETOMETANIVEL_H
#define OBJETOMETANIVEL_H

#include <ObjetoMapa.h>

class ObjetoMetaNivel : public ObjetoMapa
{
    public:
        ObjetoMetaNivel(float posX, float posY, int tipo);
        virtual ~ObjetoMetaNivel();

    protected:

    private:
};

#endif // OBJETOMETANIVEL_H
