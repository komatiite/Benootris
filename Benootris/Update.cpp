#include <iostream>
#include "Update.h"

using namespace std;

Update::Update(KeyPress& keyPress, 
				Block*& currentBlock, 
				Uint32& blockTicks, 
				vector<int>& gameBoardMatrix, 
				vector<int>& completedLines,
				LineState& lineState,
				bool& isGameActive,
				Uint32& score) :
	mKeyPress(keyPress),
	mCurrentBlock(currentBlock),
	mBlockTicks(blockTicks),
	mGameBoardMatrix(gameBoardMatrix),
	mCompletedLines(completedLines),
	mLineState(lineState),
	mIsGameActive(isGameActive),
	mScore(score) { }

Update::~Update() {}

void Update::updateGame() {

	if (mCurrentBlock->getBlockState() == ACTIVE) {
		updateBlockPosition();
		checkBlockPosition();
	}
	else if (mCurrentBlock->getBlockState() == INACTIVE) {
		if (mLineState == INPLAY) {
			if (!checkIfFull()) {
				updateGameBoard();

				if (!checkForCompleteLine()) {
					//cout << "prep new block INPLAY" << endl;
					prepareNewBlock();
				}
			}	
		}
		else if (mLineState == COMPLETED) {
			updateLineState();
		}
		else if (mLineState == DELETED) {
			prepareCompletedLine();
			resetLineState();
			//cout << "prep new block DELETED" << endl;
			prepareNewBlock();
		}
		
	}
}

void Update::updateBlockPosition() {
	//cout << "updateBlockPosition()" << endl;
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
	if (SDL_GetTicks() - mBlockTicks > 500) {
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

bool Update::checkIfFull() {
	if (mCurrentBlock->mY < 0) {
		mIsGameActive = false;
		return !mIsGameActive;
	}

	return false;
}

void Update::updateLineState() {
	//cout << "updateLineState() " << "- line ticks: " << mLineTicks << " - diff: " << (SDL_GetTicks() - mLineTicks) << endl;

	if (mLineTicks != 0 && SDL_GetTicks() - mLineTicks > 125) {
		cout << "Set line state to DELETED" << endl;
		mLineState = DELETED;
		mLineTicks = 0;
	}
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

bool Update::checkForCompleteLine() {
	cout << "checkForCompletedLine()" << endl;
	int filledCount = 0;
	int emptyCount = 0;
	bool lineScored = false;

	for (size_t i = mGameBoardMatrix.size() - 1; i >= 0; i--) { // Cycle backwards through board	

		//cout << "Check row: " << (i / 20) + 1 << endl;

		if (mGameBoardMatrix[i] != 0) {
			filledCount++;
			emptyCount = 0;
		}
		else {
			emptyCount++;
			filledCount = 0;
		}

		//cout << "Check row: " << (i / 20) + 1 << " - filled: " << filledCount << endl;

		if (filledCount == 20) {
			//cout << "Filled complete line" << endl;
			mCompletedLines.push_back(((int)i / 20) + 1);
			mLineState = COMPLETED;
			mLineTicks = SDL_GetTicks();
			lineScored = true;

			markCompletedLine(i);
			filledCount = 0;
			mScore += 100;
		}
		if (emptyCount == 20) { // No tiles left in game board row
			cout << "Breaking check for complete line on row: " << (i / 20) << endl;
			break;
		}
	}	

	return lineScored;
}


void Update::markCompletedLine(size_t startTile) {
	cout << "markCompletedLine()" << endl;
	// Update game board matrix to signify completed lies

	//cout << "Update game board for completed line render" << endl;
	cout << "Size of completed line vector: " << mCompletedLines.size() << endl;


	for (size_t i = startTile; i < startTile + 20; i++) {
		cout << "Completed line row - current colour: " << mGameBoardMatrix[i] << endl;
		mGameBoardMatrix[i] = 1;
	}
}

void Update::prepareCompletedLine() {
	// for each line in the completed lines run through and shift shit down

	cout << "prepareCompletedLine()" << endl;

	for (size_t i = 0; i < mCompletedLines.size(); i++) {
		int endPosition = (mCompletedLines[i] * 20) - 1;


		cout << "Deleting row " << mCompletedLines[i] << " - end position: " << endPosition << endl;

		for (size_t i = endPosition; i > 0; i--) {
			//cout << "shift: " << i << endl;
			if (i > 19) {
				mGameBoardMatrix[i] = mGameBoardMatrix[i - 20];
			}
			else {
				mGameBoardMatrix[i] = 0;
			}

		}

		if (mCompletedLines.size() > 1) {
			cout << "shift next completed line" << endl;
			for (size_t j = i; j < mCompletedLines.size(); j++) {
				mCompletedLines[j]++;
			}
		}
		
	}

	cout << "END prepareCompletedLine()" << endl;
}

void Update::resetLineState() {
	cout << "resetLineState()" << endl;
	mLineState = INPLAY;
	mCompletedLines.clear();
}

void Update::prepareNewBlock() {
	cout << "prepareNewBlock()" << endl;
	delete mCurrentBlock;
	createNewBlock(mCurrentBlock);
}
