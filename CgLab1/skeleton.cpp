// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;


// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Interpolate(float, float, vector<float>&);
void Interpolate( vec3, vec3, vector<vec3>&);

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
//    vector<vec3> result( 4 );
//    vec3 a(1,4,9.2);
//    vec3 b(4,1,9.8);
//    Interpolate( a, b, result );
//    for( int i=0; i<result.size(); ++i ){
//        cout << "( "
//        << result[i].x << ", "
//        << result[i].y << ", "
//        << result[i].z << " ) ";
//    }
	while( NoQuitMessageSDL() )
	{
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Interpolate( vec3 a, vec3 b, vector<vec3>& result ){
    if (result.size()==1){
        cout << "vector has to be larger than 1";
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        result[i].x = a.x + (b.x-a.x)/(result.size()-1)*i;
        result[i].y = a.y + (b.y-a.y)/(result.size()-1)*i;
        result[i].z = a.z + (b.z-a.z)/(result.size()-1)*i;
    }
}

void Interpolate( float a, float b, vector<float>& result ){
    if (result.size()==1){
        cout << "vector has to be larger than 1";
        return;
    }
    for (int i = 0; i < result.size(); i++) {
        result[i] = a + (b-a)/(result.size()-1)*i;
    }
}

void Draw(){
    vec3 topLeft(1,0,0); // red
    vec3 topRight(0,0,1); // blue
    vec3 bottomLeft(1,1,0); // yellow
    vec3 bottomRight(0,1,0); // green
    
    vector<vec3> leftSide( SCREEN_HEIGHT );
    vector<vec3> rightSide( SCREEN_HEIGHT );
    vector<vec3> canvas(SCREEN_WIDTH);
    Interpolate( topLeft, bottomLeft, leftSide );
    Interpolate( topRight, bottomRight, rightSide );
    
	for( int y=0; y<SCREEN_HEIGHT; ++y ){
        Interpolate( leftSide[y], rightSide[y], canvas);
        for( int x=0; x<SCREEN_WIDTH; ++x ){
            PutPixelSDL(screen, x, y, canvas[x]);
        }
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}
