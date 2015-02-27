#ifndef ENEMIGOROJO_H
#define ENEMIGOROJO_H

#include "Enemigo.h"

class EnemigoRojo : public Enemigo
{
    public:
        EnemigoRojo(SDL_Renderer* renderer,list<Personaje*> *personajes);
        virtual ~EnemigoRojo();
        bool arraba;
        void act();
    protected:
    private:
};

#endif // ENEMIGOROJO_H
