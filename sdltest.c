#include<stdio.h>
#include<stdlib.h>
#include "src\include\SDL2\SDL.h"
int main(int argc,char *argv[])
{
    const int WIDTH = 800, HEIGHT=600;
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *window = SDL_CreateWindow("Hello SDL WORLD",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);
        if(NULL ==window){
            printf("Could not create window.\n");
            return 1;
        }
        SDL_Event windowEvent;
        while(1){
            if(SDL_PollEvent(&windowEvent)){
                if(SDL_QUIT==windowEvent.type){
                    break;
                }
            }
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
        
return 0;
}