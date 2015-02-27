#ifndef ENEMIGOVERDE_H
#define ENEMIGOVERDE_H

#include "Enemigo.h"

class EnemigoVerde : public Enemigo
{
    public:
        EnemigoVerde(SDL_Renderer* renderer,list<Personaje*> *personajes);
        virtual ~EnemigoVerde();

        bool inc;
        void act();
    protected:
    private:
};

#endif // ENEMIGOVERDE_H
