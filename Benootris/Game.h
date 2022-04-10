#pragma once
#include "Input.h"
#include "Update.h"

using namespace std;

class Game {
public:
	Game(SDL_Window*& gameWindow,
		SDL_Renderer*& renderer);
	~Game();
	void runGame();

private:
	SDL_Window*& mGameWindow;
	SDL_Renderer*& mRenderer;
	Input* mInput;
	Update* mUpdate;

	// Loop variables
	bool mQuit;
	SDL_Event mEvent;

	// Graphic variables
	SDL_Texture* mGameBackground;
	SDL_Rect mGameBackgroundRect;
	SDL_Texture* mGameBoard;
	SDL_Rect mGameBoardRect;
	SDL_Texture* mBlueTile;
	SDL_Texture* mTealTile;
	SDL_Texture* mGreenTile;
	SDL_Texture* mGoldTile;
	SDL_Texture* mOrangeTile;
	SDL_Texture* mRedTile;



	// Game state variables
	KeyPress mKeyPress;
	vector<int> mGameBoardMatrix;
	Block* mCurrentBlock;
	Uint32 mBlockTicks;

	void renderGame();
	void destroyResources();
};

void createNewBlock(Block*& mCurrentBlock);