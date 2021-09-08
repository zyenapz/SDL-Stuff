#include <string>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argv, char** args) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	
	SDL_Window* gWindow = SDL_CreateWindow("Archimedean spiral demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Surface* gWinSurf = SDL_GetWindowSurface(gWindow);
	SDL_Surface* tempSurface = IMG_Load("img.jpg");
	
	// Necessary: convert surface
	// Seems like I need to use a 32-bit pixel format like RGBA32...
	// ...in order for the display to be correct.
	SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	SDL_Surface* mySurface = SDL_ConvertSurface(tempSurface, format, 0);
	SDL_FreeSurface(tempSurface);
		
	if(mySurface == NULL) {
		printf("Surface is nullz. %s\n", IMG_GetError());
	}
	else {
		printf("Surface is not null.\n");
	}
	
	SDL_Event e;
	bool running = true;
	
	// indx data
	int x = 0;
	int y = 0;
	int w = mySurface->w;
	double r = 0;
	double a = 1;
	double b = 5;
	double t = 0;
	const double STEP = 0.01;
	const double LOOPS = 50;
	Uint32 color = 0xFFAA88FF;
	
	// Convert pixels to 32 bit
	Uint32* pixels = (Uint32 *)mySurface->pixels;
	
	while(running) {
		
		// calc r
		if (t < LOOPS) {
			t = t + STEP;
		}
		
		r = a + b * t;
		
		// polar to cartesian
		x = round(r * cos(t)) + 500;
		y = round(r * sin(t)) + 300;
		int indx = (y * w) + x;
		//printf("Index: %d\n", indx);
		
		// replace pixel with the specified color
		pixels[ (y * w) + x ] = color;	
		
		SDL_BlitSurface(mySurface, NULL, gWinSurf, NULL);
		SDL_UpdateWindowSurface( gWindow );
	}
	printf("SDL Error: %s\n", SDL_GetError());
	printf("IMG Error: %s\n", IMG_GetError());
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(mySurface);
	SDL_FreeFormat(format);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
