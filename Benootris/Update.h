#pragma once
#include <SDL.h>
#include "Input.h"
#include "Block.h"
#include "LineState.h"

class Update {
public:
	Update(KeyPress& keyPress, 
		Block*& currentBlock, 
		Uint32& blockTicks, 
		vector<int>& gameBoardMatrix, 
		vector<int>& completedLines,
		LineState& lineState,
		bool& isGameActive,
		Uint32& score);
	~Update();
	void updateGame();

private:
	KeyPress& mKeyPress;
	Block*& mCurrentBlock;
	Uint32& mBlockTicks;
	vector<int>& mGameBoardMatrix;
	vector<int>& mCompletedLines;
	LineState& mLineState;
	Uint32 mLineTicks;
	bool& mIsGameActive;
	Uint32& mScore;

	void updateBlockPosition();
	void updatePlayerMovement();
	void dropBlock();
	void updateAutoMovement();
	void checkBlockPosition();
	bool isLandedOnBottom();
	bool isLandedonBlock();
	bool checkIfFull();
	void updateLineState();
	void updateGameBoard();
	bool checkForCompleteLine();
	void markCompletedLine(size_t startTile);
	void prepareCompletedLine();
	void resetLineState();
	void prepareNewBlock();
};