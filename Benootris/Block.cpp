#include <iostream>
#include <cmath>
#include "Block.h"

using namespace std;

Block::Block() {}

Block::~Block() {}

void Block::moveLeft() {
	if (checkLeftWall(getPattern(), false)) {
		mX--;
	}
}

bool Block::checkLeftWall(pattern pattern, bool rotate) {
	int newX = rotate ? mX : mX - 1;

	if (newX < 0) {
		int column = abs(newX) - 1;

		for (int i = column; i < 16; i += 4) {
			if (pattern.tile[i] != 0) {
				return false;
			}
		}
		return true;
	}
	return true;
}

void Block::moveRight() {
	mX++;
}

void Block::rotateLeft() {}
void Block::rotateRight() {}
void Block::flip() {}

void Block::moveDown() {
	if (mBlockState == ACTIVE) {
		mY++;
	}
}

void Block::setBlockStateActive() {
	mBlockState = ACTIVE;
}

void Block::setBlockStateInactive() {
	mBlockState = INACTIVE;
}

BlockState Block::getBlockState() {
	return mBlockState;
}

pattern Block::getPattern() {
	return getPattern(mPatternIndex);
}

pattern Block::getPattern(int index) {
	return mPattern[index];
}

Line::Line(int c, int index, int x, int y) {
	//mPattern.push_back({ 1, c, 1, 1, 1, c, 1, 1, 1, c, 1, 1, 1, c, 1, 1 });
	mPattern.push_back({ 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, c, c, c, c, 0, 0, 0, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, c, c, c, c, 0, 0, 0, 0 });
	//mPattern.push_back({ 1, 1, 1, 1, 1, 1, 1, 1, c, c, c, c, 1, 1, 1, 1 });

	mPatternIndex = 0;
	mX = x;
	mY = y;
}

Line::~Line() {}

void Line::rotateLeft() {
	if (mPatternIndex > 0) {
		if (checkLeftWall(mPattern[mPatternIndex - 1], true)) {
			mPatternIndex--;
		}	
	}
	else {
		if (checkLeftWall(mPattern[3], true)) {
			mPatternIndex = 3;
		}	
	}
}

void Line::rotateRight() {
	if (mPatternIndex < 3) {
		mPatternIndex++;
	}
	else {
		mPatternIndex = 0;
	}
}

pattern Line::getPattern() {
	return getPattern(mPatternIndex);
}

pattern Line::getPattern(int index) {
	return mPattern[index];
}


Square::Square(int c, int index, int x, int y) {
	mPattern.push_back({ 0, 0, 0, 0, 0, c, c, 0, 0, c, c, 0, 0, 0, 0, 0 });

	mPatternIndex = 0;
	mX = x;
	mY = y;
}

Square::~Square() {}

pattern Square::getPattern() {
	return getPattern(mPatternIndex);
}

pattern Square::getPattern(int index) {
	return mPattern[index];
}



Lshape::Lshape(int c, int index, int x, int y) {
	mPattern.push_back({ 0, c, c, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, c, c, c, c, 0, 0, 0, c, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, c, c, 0 });
	mPattern.push_back({ 0, 0, 0, 0, c, 0, 0, 0, c, c, c, c, 0, 0, 0, 0 });
	mPattern.push_back({ 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, c, 0 });
	mPattern.push_back({ 0, 0, 0, 0, c, c, c, c, c, 0, 0, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, c, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, 0, 0, c, c, c, c, c, 0, 0, 0, 0 });

	mPatternIndex = 0;
	mX = x;
	mY = y;
}

Lshape::~Lshape() {}

void Lshape::rotateLeft() {
	if (mPatternIndex > 0 && mPatternIndex < 4) {
		if (checkLeftWall(mPattern[mPatternIndex - 1], true)) {
			mPatternIndex--;
		}
	}
	else if (mPatternIndex == 0) {
		if (checkLeftWall(mPattern[3], true)) {
			mPatternIndex = 3;
		}
	}
	else if (mPatternIndex > 4) {
		if (checkLeftWall(mPattern[mPatternIndex - 1], true)) {
			mPatternIndex--;
		}
	}
	else if (mPatternIndex == 4) {
		if (checkLeftWall(mPattern[mPatternIndex - 1], true)) {
			mPatternIndex = 7;
		}
	}
}

void Lshape::rotateRight() {
	if (mPatternIndex < 3) {
		mPatternIndex++;
	}
	else if (mPatternIndex == 3) {
		mPatternIndex = 0;
	}
	else if (mPatternIndex < 7 && mPatternIndex > 3) {
		mPatternIndex++;
	}
	else if (mPatternIndex == 7) {
		mPatternIndex = 4;
	}
}

void Lshape::flip() {
	switch (mPatternIndex) {
	case 0:
		mPatternIndex = 4;
		break;
	case 1:
		mPatternIndex = 7;
		break;
	case 2:
		mPatternIndex = 6;
		break;
	case 3:
		mPatternIndex = 5;
		break;
	case 4:
		mPatternIndex = 0;
		break;
	case 5:
		mPatternIndex = 3;
		break;
	case 6:
		mPatternIndex = 2;
		break;
	case 7:
		mPatternIndex = 1;
		break;
	}
}

pattern Lshape::getPattern() {
	return getPattern(mPatternIndex);
}

pattern Lshape::getPattern(int index) {
	return mPattern[index];
}



Zshape::Zshape(int c, int index, int x, int y) {
	mPattern.push_back({ 0, 0, 0, 0, c, c, 0, 0, 0, c, c, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, c, 0, 0, c, c, 0, 0, c, 0, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, c, c, 0, 0, 0, c, c, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, 0, c, 0, 0, c, c, 0, 0, c, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, 0, c, c, 0, c, c, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, c, 0, 0, 0, c, c, 0, 0, 0, c, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, c, c, 0, c, c, 0, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, c, 0, 0, 0, c, c, 0, 0, 0, c, 0, 0, 0, 0, 0 });

	mPatternIndex = 0;
	mX = x;
	mY = y;
}

Zshape::~Zshape() {}

void Zshape::rotateLeft() {
	if (mPatternIndex > 0 && mPatternIndex < 4) {
		if (checkLeftWall(mPattern[mPatternIndex - 1], true)) {
			mPatternIndex--;
		}
	}
	else if (mPatternIndex == 0) {
		if (checkLeftWall(mPattern[3], true)) {
			mPatternIndex = 3;
		}
	}
	else if (mPatternIndex > 4) {
		if (checkLeftWall(mPattern[mPatternIndex - 1], true)) {
			mPatternIndex--;
		}
	}
	else if (mPatternIndex == 4) {
		if (checkLeftWall(mPattern[7], true)) {
			mPatternIndex = 7;
		}
	}
}

void Zshape::rotateRight() {
	if (mPatternIndex < 3) {
		mPatternIndex++;
	}
	else if (mPatternIndex == 3) {
		mPatternIndex = 0;
	}
	else if (mPatternIndex < 7 && mPatternIndex > 3) {
		mPatternIndex++;
	}
	else if (mPatternIndex == 7) {
		mPatternIndex = 4;
	}
}

void Zshape::flip() {
	if (mPatternIndex < 4) {
		mPatternIndex += 4;
	}
	else if (mPatternIndex > 3) {
		if (checkLeftWall(mPattern[mPatternIndex - 4], true)) {
			mPatternIndex -= 4;
		}
	}
}

// Can this be cleaned up for base class? - all derived classes
pattern Zshape::getPattern() {
	return getPattern(mPatternIndex);
}

pattern Zshape::getPattern(int index) {
	return mPattern[index];
}

void createNewBlock(Block*& mCurrentBlock) {
	int seedColour = 2 + rand() % 7;
	int seedShape = 1 + rand() % 4;

	switch (seedShape) {
	case 1:
		mCurrentBlock = new Line(seedColour, 0, 3, 0);
		break;
	case 2:
		mCurrentBlock = new Square(seedColour, 0, 12, 0);
		break;
	case 3:
		mCurrentBlock = new Lshape(seedColour, 0, 12, 0);
		break;
	case 4:
		mCurrentBlock = new Zshape(seedColour, 0, 12, 0);
		break;
	default:
		mCurrentBlock = new Line(seedColour, 0, 7, 0);
		break;
	}

	mCurrentBlock->setBlockStateActive();
}