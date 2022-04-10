#include <iostream>
#include "Game.h"
#include "Update.h"

using namespace std;

Update::Update(KeyPress& keyPress, Block*& currentBlock, Uint32& blockTicks, vector<int>& gameBoardMatrix)
	: mKeyPress(keyPress),
	mCurrentBlock(currentBlock),
	mBlockTicks(blockTicks),
	mGameBoardMatrix(gameBoardMatrix) { 

	mLineScored = false;
}

Update::~Update() {}

void Update::updateGame() {
	updateBlockPosition();
	checkBlockPosition();

	if (mCurrentBlock->getBlockState() == INACTIVE) {
		updateGameBoard();
		checkForCompleteLine();
		prepareNewBlock();
	}
	
	
}

void Update::updateBlockPosition() {
	updatePlayerMovement();
	updateAutoMovement();
}

void Update::updatePlayerMovement() {
	if (mKeyPress == LEFT) {
		mCurrentBlock->moveLeft();
	}
	else if (mKeyPress == RIGHT) {
		mCurrentBlock->moveRight();
	}
	else if (mKeyPress == ROTATE_LEFT) {
		mCurrentBlock->rotateLeft();
	}
	else if (mKeyPress == ROTATE_RIGHT) {
		mCurrentBlock->rotateRight();
	}
	else if (mKeyPress == UP) {
		mCurrentBlock->flip();
	}
	else if (mKeyPress == DOWN) {
		dropBlock();
	}
}

void Update::dropBlock() {
	while (mCurrentBlock->getBlockState() == ACTIVE) {
		mCurrentBlock->mY++;
		checkBlockPosition();
	}
}

void Update::updateAutoMovement() {
	if (SDL_GetTicks() - mBlockTicks > 250) {
		mCurrentBlock->moveDown();
		mBlockTicks = SDL_GetTicks();
	}
}

void Update::checkBlockPosition() {
	if (isLandedonBlock() || isLandedOnBottom()) {
		mCurrentBlock->setBlockStateInactive();
	}
}

bool Update::isLandedOnBottom() {
	if (mCurrentBlock->mY >= 30) {
		for (int i = 15; i > 0; i--) {
			if (mCurrentBlock->mPattern[mCurrentBlock->mPatternIndex].tile[i] != 0) {
				if (mCurrentBlock->mY + (i / 4) >= 33) {
					return true;
				}
				return false;
			}
		}
		return false;
	}
	return false;
}

bool Update::isLandedonBlock() {
	int count = 0;

	for (int i = 15; i > 0; i--) {
		if (mCurrentBlock->mPattern[mCurrentBlock->mPatternIndex].tile[i] != 0) {
			int position = (mCurrentBlock->mY * 20) + ((i / 4) * 20) + (mCurrentBlock->mX + (i % 4)) + 20;
			if (position < mGameBoardMatrix.size() && mGameBoardMatrix[position] != 0) {
				return true;
			}
			count++;
		}
		else if (count == 4) { // There are only four tiles in a block, so potentially save 12 cycles
			break;
		}
	}
	return false;
}

void Update::updateGameBoard() {
	// Tidy up literals
	for (int i = 0; i < 16; i++) {
		if (mCurrentBlock->getPattern().tile[i] != 0) {
			int position = (mCurrentBlock->mY * 20) + ((i / 4) * 20) + (mCurrentBlock->mX + (i % 4)); // Find position of block tile on board
			mGameBoardMatrix[position] = mCurrentBlock->getPattern().tile[i]; // Add colour of block to board
		}
	}
}

void Update::checkForCompleteLine() {
	int tileCount = 0;
	int filledCount = 0;
	int emptyCount = 0;

	for (int i = mGameBoardMatrix.size() - 1; i >= 0; i--) { // Cycle backwards through board
		if (mGameBoardMatrix[i] != 0) {
			filledCount++;
			emptyCount = 0;
		}
		else {
			emptyCount++;
		}

		if (filledCount == 20) {
			cout << "Filled complete line" << endl;
			prepareCompletedLine(i);
			filledCount = 0;
		}
		if (emptyCount == 20) { // No tiles left in game board row	
			break;
		}

		tileCount++;

		// clear new row
		if (tileCount == 20) {
			tileCount = 0;
			filledCount = 0;
			emptyCount = 0;
		}
	}
	cout << "No line scored" << endl;

	mLineScored = false;
}

void Update::prepareCompletedLine(int rowStart) {
	int endOfRow = rowStart + 20;

	cout << "Deleting row " << rowStart << "-" << endOfRow << endl;
	// animate - but this is a big piece, for now just delete and move

	for (int i = endOfRow; i >= 0; i--) { // Cycle backwards through board
		if (mGameBoardMatrix[i - 20] >= 0) {
			mGameBoardMatrix[i] = mGameBoardMatrix[i - 20];
		}
		else {
			mGameBoardMatrix[i] = 0;
		}
	}

	mLineScored = true;
}

void Update::prepareNewBlock() {
	if (!mLineScored) {
		delete mCurrentBlock;
		createNewBlock(mCurrentBlock);
	}
}
