#include <iostream>
#include "RenderText.h"

using namespace std;

void RenderText::renderText(SDL_Renderer*& renderer, int score, int x, int y) {
	TTF_Font* font = TTF_OpenFont("resources/arialbd.ttf", 32);
	SDL_Color colour = { 255, 255, 255 };
	renderText(renderer, font, colour, score, x, y);
}

void RenderText::renderText(SDL_Renderer*& renderer, SDL_Color colour, int score, int x, int y) {
	TTF_Font* font = TTF_OpenFont("resources/arialbd.ttf", 32);
	renderText(renderer, font, colour, score, x, y);
}

void RenderText::renderText(SDL_Renderer*& renderer, TTF_Font* font, SDL_Color colour, int score, int x, int y) {
	string scoreText = to_string(score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), colour);

	if (textSurface == NULL) {
		cout << "ERROR - Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else {
		SDL_Rect rect = { x, y, textSurface->w, textSurface->h };
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);

		if (texture == NULL) {
			cout << "ERROR - Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
		}

		SDL_RenderCopy(renderer, texture, NULL, &rect);
		SDL_DestroyTexture(texture);
	}
}
