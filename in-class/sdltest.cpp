/**
 * Draw a white square in a 640x480 window.
 * Windows users: You already went through the pain of setting this all up.
 * g++ sdltest.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -w -Wl,-subsystem,windows -o sdltest.exe
 * Mac users: First, install SDL from here: https://www.libsdl.org/release/SDL2-2.0.3.dmg
 * g++ sdltest.cpp -lSDL2main -lSDL2 -o sdltest
 */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    
    // Init SDL
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        cout << "Couldn't initialize SDL: " << SDL_GetError() << endl;
        return 1;
    }
    
    // Init window
    window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Couldn't create window: " << SDL_GetError() << endl;
        return 1;
    }

    // Get the screen
    screenSurface = SDL_GetWindowSurface(window);
    
    //Initialize PNG loading
    if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        return 1;
    }

    // Load image
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load( "image.png" );
    if( loadedSurface == NULL ) { 
        cout << "Unable to load image. " << IMG_GetError() << endl;
        return 1;
    }
    // Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, NULL );
    if( optimizedSurface == NULL ) { 
        cout << "Unable to optimize image. " << SDL_GetError() << endl;
        return 1;
    }
    // Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
    
    // Draw to screen surface
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,
        0x00, 0x00, 0x00));
    SDL_BlitSurface( optimizedSurface, NULL, screenSurface, NULL );
    
    // Show surface on screen window
    // This is when the drawing happens
    SDL_UpdateWindowSurface(window);
    
    // Wait around
    SDL_Delay(2000);
    
    // kthxbye
    SDL_DestroyWindow(window);
    SDL_FreeSurface( optimizedSurface );
    IMG_Quit();
    SDL_Quit();
    return 0;
}