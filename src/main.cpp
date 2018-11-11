#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "main.h"
#include "SDL_functions.h"


const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;


//using namespace std;




int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		logSDL("SDL_Init");
		return EXIT_FAILURE;
	}

	
	SDL_Window *window = SDL_CreateWindow("SDL Window",
							SDL_WINDOWPOS_UNDEFINED, 
							SDL_WINDOWPOS_UNDEFINED, 
							WIN_WIDTH,
							WIN_HEIGHT,
							SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDL("Create Window");
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window,
											   -1,
											   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDL("Create Renderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture *backgroundNorm = loadTexture("../resources/backgroundNormal.bmp", renderer);
	SDL_Texture *backgroundInv = loadTexture("../resources/backgroundInverse.bmp", renderer);
	SDL_Texture *toreLeft = loadTexture("../resources/toreLeft.bmp", renderer);
	SDL_Texture *toreRight = loadTexture("../resources/toreRight.bmp", renderer);
	if (backgroundNorm == nullptr ||backgroundInv == nullptr || toreLeft == nullptr|| toreRight == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}


	SDL_RenderClear(renderer);

	int backW, backH;
	SDL_QueryTexture(backgroundNorm, NULL, NULL, &backW, &backH);
	SDL_QueryTexture(backgroundInv, NULL, NULL, &backW, &backH);
	renderTexture(backgroundInv, renderer, 0, 0);



	int toreW, toreH;
	SDL_QueryTexture(toreLeft, NULL, NULL, &toreW, &toreH);
	SDL_QueryTexture(toreRight, NULL, NULL, &toreW, &toreH);
	for (int i {0}; i<=7; i++){
		for (int j {0}; j<=7; j++) {
			int x = 70+j*70 - toreW / 2;
			int y = 70+i*70 - toreH / 2;
			if ((i+j)%2 == 0){
				renderTexture(toreLeft, renderer, x, y);
			}else{
				renderTexture(toreRight, renderer, x, y);
			}
			
		}
	}
	
	SDL_RenderPresent(renderer);

	pause();



	SDL_DestroyTexture(toreLeft);
	SDL_DestroyTexture(toreRight);
	SDL_DestroyTexture(backgroundNorm);
	SDL_DestroyTexture(backgroundInv);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}


