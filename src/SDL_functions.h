#pragma once

void pause();

void logSDL(const std::string &msg);

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y);