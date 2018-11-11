#pragma once


void drawTores(std::vector<std::vector<bool>> const& gridBits, SDL_Texture *toreLeftBlue,
			   SDL_Texture *toreLeftRed,
			   SDL_Texture *toreRightBlue,
			   SDL_Texture *toreRightRed,
			   SDL_Renderer *renderer);