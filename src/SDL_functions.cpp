#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "SDL_functions.h"

/**
*	Pause the program, until escape key is pressed, or window closed manually
*/

void pause() {
	int resume = true;
	SDL_Event event;
	while (resume) {
		SDL_WaitEvent(&event);
		switch (event.type) {
			case SDL_QUIT:
				resume = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						resume = false;
						break;
				}
		}
	}
}



/**
*	Log an SDL error with some error message
*	@param msg The error message to write
*/
void logSDL(const std::string &msg) {
	std::string logmessage = msg+":"+SDL_GetError()+"\n";
	SDL_Log(logmessage.c_str());
}



/**
*	Loads a BMP image into a texture on the rendering device
*	@param file The BMP image file to load
*	@param renderer The renderer to load the texture onto
*	@return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer) {
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr) {
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr) {
			logSDL("Create Texture From Surface");
		}
	} else {
		logSDL("Load BMP");
	}
	return texture;
}



/**
*	Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
*	the texture's width and height
*	@param texture The source texture we want to draw
*	@param renderer The renderer we want to draw to
*	@param x The x coordinate to draw to
*	@param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}