#include <iostream>
#include <SDL.h>
using namespace std;
/*
int main(int argc, char * argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	} else {
		cout << "SDL initialization succeeded!";
	}

	cin.get();
	return 0;
}
*/


int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	SDL_Quit();
	return EXIT_SUCCESS;
}