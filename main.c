#include "c8.h"
#define SDL_MAIN_HANDLED 1
#include "SDL2/include/SDL.h"

//this is an application, it should be a thing on its own! (an exe referencing dengine.dll)


//FEATURES TODO
//-Fibers
//-String Streams!
//-Profiling
//-Engine logging
//-Basic Sound (+ Audio compression/decompression)
//-Window Abstraction
//-Graphics (when I get the new PC..)


void init(void)
{
    SDL_Window *window = NULL;
    SDL_Surface *screen_surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize!!\n");
    }
    else
    {
        //Create the window
        window = SDL_CreateWindow( "CHIP-8 EMU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN );
        if (window == NULL)
            printf("Window could not be created!!\n");
        else
        {
            //printf("Created Window!\n");
            screen_surface = SDL_GetWindowSurface( window );
            SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xAF, 0x2F, 0x3F ) );
            SDL_UpdateWindowSurface( window );
            SDL_Delay(20);
        }
    }
}

b32 update(void)
{
    //call_context_func();

    return 0;
}


int main(void)
{
    
    
    init();
	
	parse_rom("Fishie.ch8");
    while(update());
    
    return 0;
}
