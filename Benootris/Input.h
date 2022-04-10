#pragma once
#include <SDL.h>

enum KeyPress {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ROTATE_LEFT,
	ROTATE_RIGHT
};

class Input {
public:
	Input(SDL_Event& event, bool& quit, KeyPress& keyPress);
	~Input();
	void handleInput();
	void handleKeyDown();

private:
	SDL_Event& mEvent;
	bool& mQuit;
	KeyPress& mKeyPress;


};
