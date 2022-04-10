#pragma once
#include <SDL.h>
#include "Input.h"
#include "Block.h"

class Update {
public:
	Update(KeyPress& keyPress, Block*& currentBlock, Uint32& blockTicks, vector<int>& gameBoardMatrix);
	~Update();
	void updateGame();

private:
	KeyPress& mKeyPress;
	Block*& mCurrentBlock;
	Uint32& mBlockTicks;
	vector<int>& mGameBoardMatrix;
	bool mLineScored;

	void updateBlockPosition();
	void updatePlayerMovement();
	void dropBlock();
	void updateAutoMovement();
	void checkBlockPosition();
	bool isLandedOnBottom();
	bool isLandedonBlock();
	void updateGameBoard();
	void checkForCompleteLine();
	void prepareCompletedLine(int rowStart);
	void prepareNewBlock();
};