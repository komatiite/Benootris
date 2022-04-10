#include <iostream>
#include "Block.h"

using namespace std;

Block::Block() {}

Block::~Block() {}

void Block::moveLeft() {
	mX--;
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
	return mPattern[mPatternIndex];
}

Line::Line(int c, int index, int x, int y) {
	mPattern.push_back({ 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0 });
	mPattern.push_back({ 0, 0, 0, 0, c, c, c, c, 0, 0, 0, 0, 0, 0, 0, 0 });
	mPattern.push_back({ 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0, 0, 0, c, 0 });
	mPattern.push_back({ 0, 0, 0, 0, 0, 0, 0, 0, c, c, c, c, 0, 0, 0, 0 });

	mPatternIndex = 0;
	mX = x;
	mY = y;
}

Line::~Line() {}

void Line::rotateLeft() {
	if (mPatternIndex > 0) {
		mPatternIndex--;
	}
	else {
		mPatternIndex = 3;
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
	return mPattern[mPatternIndex];
}


Square::Square(int c, int index, int x, int y) {
	mPattern.push_back({ 0, 0, 0, 0, 0, c, c, 0, 0, c, c, 0, 0, 0, 0, 0 });

	mPatternIndex = 0;
	mX = x;
	mY = y;
}

Square::~Square() {}

pattern Square::getPattern() {
	return mPattern[mPatternIndex];
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
		mPatternIndex--;
	}
	else if (mPatternIndex == 0) {
		mPatternIndex = 3;
	}
	else if (mPatternIndex > 4) {
		mPatternIndex--;
	}
	else if (mPatternIndex == 4) {
		mPatternIndex = 7;
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
	return mPattern[mPatternIndex];
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
		mPatternIndex--;
	}
	else if (mPatternIndex == 0) {
		mPatternIndex = 3;
	}
	else if (mPatternIndex > 4) {
		mPatternIndex--;
	}
	else if (mPatternIndex == 4) {
		mPatternIndex = 7;
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
		mPatternIndex -= 4;
	}
}

// Can this be cleaned up for base class? - all derived classes
pattern Zshape::getPattern() {
	return mPattern[mPatternIndex];
}

