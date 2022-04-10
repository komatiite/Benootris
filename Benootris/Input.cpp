#include <iostream>
#include "Input.h"

using namespace std;

Input::Input(SDL_Event& event, bool& quit, KeyPress& keyPress) : mEvent(event), mQuit(quit), mKeyPress(keyPress) {}
Input::~Input() {}

void Input::handleInput() {
	while (SDL_PollEvent(&mEvent) != 0) {
		if (mEvent.type == SDL_QUIT) {
			mQuit = true;
		}
		else if (mEvent.type == SDL_KEYDOWN) {
			handleKeyDown();
		}
	}
}

void Input::handleKeyDown() {
	if (mEvent.key.keysym.sym == SDLK_ESCAPE) {
		mQuit = true;
	}
	else if (mEvent.key.keysym.sym == SDLK_LEFT) {
		mKeyPress = LEFT;
	}
	else if (mEvent.key.keysym.sym == SDLK_RIGHT) {
		mKeyPress = RIGHT;
	}
	else if (mEvent.key.keysym.sym == SDLK_UP) {
		mKeyPress = UP;
	}
	else if (mEvent.key.keysym.sym == SDLK_DOWN) {
		mKeyPress = DOWN;
	}
	else if (mEvent.key.keysym.sym == SDLK_a) {
		mKeyPress = ROTATE_LEFT;
	}
	else if (mEvent.key.keysym.sym == SDLK_s) {
		mKeyPress = ROTATE_RIGHT;
	}

}