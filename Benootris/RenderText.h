#pragma once
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

class RenderText {
public:
	static void renderText(SDL_Renderer*& renderer, int score, int x, int y);
	static void renderText(SDL_Renderer*& renderer, SDL_Color colour, int score, int x, int y);
	static void renderText(SDL_Renderer*& renderer, TTF_Font* font, SDL_Color colour, int score, int x, int y);
};