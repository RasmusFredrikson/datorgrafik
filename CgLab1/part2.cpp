#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"
#include <ctime>
using namespace std;
using glm::vec3;
// ---------------------------------------------------------
// GLOBAL VARIABLES
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
int t;
SDL_Surface* screen;
vector<vec3> stars(10000);
// ---------------------------------------------------------
// FUNCTION DECLARATIONS
void Draw();
void Update();
// ---------------------------------------------------------
// FUNCTION DEFINITIONS
int main( int argc, char* argv[] ) {
    t = SDL_GetTicks();
    srand ( time(NULL) );
    screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
    for (int i = 0; i < stars.size(); ++i) {
        float r = -1 + float(rand()) / float(RAND_MAX)+float(rand()) / float(RAND_MAX);
        stars[i].x = r;
        r = -1 + float(rand()) / float(RAND_MAX)+float(rand()) / float(RAND_MAX);
        stars[i].y = r;
        stars[i].z = float(rand()) / float(RAND_MAX);
    }
    while( NoQuitMessageSDL() ) {
        Update();
        Draw();
    }
    SDL_SaveBMP( screen, "screenshot.bmp" );
    return 0;
}
void Draw() {
    SDL_FillRect( screen, 0, 0 );
    if( SDL_MUSTLOCK(screen) )
        SDL_LockSurface(screen);
    for( size_t s=0; s<stars.size(); ++s ) {
        float u = (SCREEN_HEIGHT/2)*(stars[s].x/stars[s].z) + (SCREEN_WIDTH/2);
        float v = (SCREEN_HEIGHT/2)*(stars[s].y/stars[s].z) + (SCREEN_HEIGHT/2);
        vec3 color = 0.2f * vec3(1,1,1) / (stars[s].z*stars[s].z);
        PutPixelSDL(screen, u, v, color);
    }
    if( SDL_MUSTLOCK(screen) )
        SDL_UnlockSurface(screen);
    SDL_UpdateRect( screen, 0, 0, 0, 0 );
}
void Update() {
    int t2 = SDL_GetTicks();
    float dt = float(t2-t); //Time since last update
    t = t2;
    float v = dt*0.0005;
    
    for( int s=0; s<stars.size(); ++s ) {
        stars[s].z += v*(-1 + float(rand()) / float(RAND_MAX));

        if( stars[s].z <= 0 )
            stars[s].z = 1;
        else if( stars[s].z > 1 )
            stars[s].z = 0;
    }
}
