
#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include<list>
#include "Sho.h"
#include "EnemigoAzul.h"
#include "EnemigoVerde.h"
#include "EnemigoRojo.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background;
SDL_Rect rect_background;
SDL_Texture *victoria;
SDL_Rect rectv;
SDL_Texture *derrota;

int muer=0;

int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1024/*WIDTH*/, 768/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    victoria = IMG_LoadTexture(renderer, "Victory.png");
    derrota = IMG_LoadTexture(renderer, "Loose.png");
    SDL_QueryTexture(victoria, NULL, NULL, &rectv.w, &rectv.h);
    SDL_QueryTexture(derrota, NULL, NULL, &rectv.w, &rectv.h);
    rectv.x=250;
    rectv.y=200;

    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;


    list<Personaje*> personajes;
    personajes.push_back(new Sho(renderer,&personajes));
//    personajes.push_back(new EnemigoAzul(renderer,&personajes));
    personajes.push_back(new EnemigoVerde(renderer,&personajes));
    personajes.push_back(new EnemigoRojo(renderer,&personajes));

    //Main Loop
    int frame=0;
    int animacion_sho = 0;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
        }

//        if(frame%1000==0)
//        {
//            personajes.push_back(new EnemigoAzul(renderer,&personajes));
//        }

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->act();

        SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);

        // Clear the entire screen to our selected color.
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            (*p)->draw(renderer);

        for(list<Personaje*>::iterator p=personajes.begin();
                p!=personajes.end();
                p++)
            if((*p)->muerto)
            {
                muer++;
                personajes.erase(p);
                break;
            }
            if (muer == 2)
                SDL_RenderCopy(renderer, victoria, NULL, &rectv);
//            else
//                SDL_RenderCopy(renderer, derrota, NULL, &rectv);


        SDL_RenderPresent(renderer);

        frame++;
    }

	return 0;
}




