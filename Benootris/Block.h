#pragma once
#include <vector>

using namespace std;

struct pattern {
	int tile[16];
};

enum BlockState {
	ACTIVE,
	INACTIVE
};

class Block {
public:
	Block();
	~Block();
	void moveLeft();
	bool checkLeftWall(pattern pattern, bool rotate);
	void moveRight();
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual void flip();
	void moveDown();
	void setBlockStateActive();
	void setBlockStateInactive();
	BlockState getBlockState();

	virtual pattern getPattern();
	virtual pattern getPattern(int index);



	vector<pattern> mPattern;
	int mPatternIndex;
	int mX, mY;

private:
	BlockState mBlockState;
};

class Line : public Block {
public:
	Line(int c, int index, int x, int y);
	~Line();
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual pattern getPattern();
	virtual pattern getPattern(int index);
};

class Square : public Block {
public:
	Square(int c, int index, int x, int y);
	~Square();
	virtual pattern getPattern();
	virtual pattern getPattern(int index);
};

class Lshape : public Block {
public:
	Lshape(int c, int index, int x, int y);
	~Lshape();
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual void flip();
	virtual pattern getPattern();
	virtual pattern getPattern(int index);
};

class Zshape : public Block {
public:
	Zshape(int c, int index, int x, int y);
	~Zshape();
	virtual void rotateLeft();
	virtual void rotateRight();
	virtual void flip();
	virtual pattern getPattern();
	virtual pattern getPattern(int index);
};

void createNewBlock(Block*& mCurrentBlock);