#include <iostream>
#include <cstdlib>
#include <vector>
#include <SDL.h>

#include "main.h"
#include "SDL_functions.h"


const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 768;


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
	SDL_Texture *toreLeftBlue = loadTexture("../resources/toreLeftBlue.bmp", renderer);
	SDL_Texture *toreLeftRed = loadTexture("../resources/toreLeftRed.bmp", renderer);
	SDL_Texture *toreRightBlue = loadTexture("../resources/toreRightBlue.bmp", renderer);
	SDL_Texture *toreRightRed = loadTexture("../resources/toreRightRed.bmp", renderer);
	if (backgroundNorm == nullptr ||backgroundInv == nullptr
		|| toreLeftBlue == nullptr|| toreLeftRed == nullptr
		|| toreRightBlue == nullptr|| toreRightRed == nullptr) {
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


	std::vector<std::vector<bool>> gridBits (8, std::vector<bool>(8));

	for (int i{0}; i<=7; i++){
		for (int j{0}; j<=7; j++){
			gridBits[i][j]=false;
		}
	}

	drawTores(gridBits, toreLeftBlue, toreLeftRed, toreRightBlue, toreRightRed, renderer);

	
	SDL_RenderPresent(renderer);

	pause();



	SDL_DestroyTexture(toreLeftBlue);
	SDL_DestroyTexture(toreLeftRed);
	SDL_DestroyTexture(toreRightBlue);
	SDL_DestroyTexture(toreRightRed);
	SDL_DestroyTexture(backgroundNorm);
	SDL_DestroyTexture(backgroundInv);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}



void drawTores(std::vector<std::vector<bool>> const& gridBits, SDL_Texture *toreLeftBlue,
			   SDL_Texture *toreLeftRed,
			   SDL_Texture *toreRightBlue,
			   SDL_Texture *toreRightRed,
			   SDL_Renderer *renderer){
	int toreW, toreH;
	SDL_QueryTexture(toreLeftBlue, NULL, NULL, &toreW, &toreH);
	SDL_QueryTexture(toreLeftRed, NULL, NULL, &toreW, &toreH);
	SDL_QueryTexture(toreRightBlue, NULL, NULL, &toreW, &toreH);
	SDL_QueryTexture(toreRightRed, NULL, NULL, &toreW, &toreH);
	for (int i {0}; i<=7; i++) {
		for (int j {0}; j<=7; j++) {
			int x = 70+j*70 - toreW / 2;
			int y = 70+i*70 - toreH / 2;
			if ((i+j)%2 == 0){
				if (gridBits[i][j]) {renderTexture(toreLeftBlue, renderer, x, y);}
				else{ renderTexture(toreLeftRed, renderer, x, y); }
			} else {
				if (gridBits[i][j]) { renderTexture(toreRightBlue, renderer, x, y); }
				else { renderTexture(toreRightRed, renderer, x, y); }
			}

		}
	}
}