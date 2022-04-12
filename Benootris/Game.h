#pragma once
#include "Input.h"
#include "Update.h"
#include "Block.h"
#include "LineState.h"

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
	SDL_Texture* mNextTileBackground;
	SDL_Texture* mScoreBackground;
	SDL_Rect mGameBackgroundRect;
	SDL_Texture* mGameBoard;
	SDL_Rect mGameBoardRect;
	SDL_Rect mNextTileRect;
	SDL_Rect mScoreRect;
	SDL_Texture* mBlueTile;
	SDL_Texture* mTealTile;
	SDL_Texture* mGreenTile;
	SDL_Texture* mGoldTile;
	SDL_Texture* mOrangeTile;
	SDL_Texture* mRedTile;
	SDL_Texture* mCompletedTile;

	// Game state variables
	KeyPress mKeyPress;
	vector<int> mGameBoardMatrix;
	Block* mCurrentBlock;
	Uint32 mBlockTicks;
	vector<int> mCompletedLines;
	LineState mLineState;
	bool mIsGameActive;
	Uint32 mScore;

	void renderGame();
	void destroyResources();
};