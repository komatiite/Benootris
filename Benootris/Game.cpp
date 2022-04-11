#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Block.h"

using namespace std;

Game::Game(SDL_Window*& gameWindow,	SDL_Renderer*& renderer) : mGameWindow(gameWindow), mRenderer(renderer) {
	mQuit = false;
	
	// Load static graphic assets
	mGameBackground = IMG_LoadTexture(mRenderer, "resources/background_01.png");
	mGameBackgroundRect = { 0, 0, 1920, 1080 };
	mGameBoard = IMG_LoadTexture(mRenderer, "resources/game_area.png");
	mGameBoardRect = { 650, 20, 620, 1040 };
	mBlueTile = IMG_LoadTexture(mRenderer, "resources/02_blue.png");
	mTealTile = IMG_LoadTexture(mRenderer, "resources/03_teal.png");
	mGreenTile = IMG_LoadTexture(mRenderer, "resources/04_green.png");
	mGoldTile = IMG_LoadTexture(mRenderer, "resources/05_gold.png");
	mOrangeTile = IMG_LoadTexture(mRenderer, "resources/06_orange.png");
	mRedTile = IMG_LoadTexture(mRenderer, "resources/07_red.png");
	mCompletedTile = IMG_LoadTexture(mRenderer, "resources/01_completed.png");

}

Game::~Game() {
}

void Game::runGame() {
	mInput = new Input(mEvent, mQuit, mKeyPress);
	mUpdate = new Update(mKeyPress, mCurrentBlock, mBlockTicks, mGameBoardMatrix, mCompletedLines, mLineState, mIsGameActive);

	// Initialize game board matrix
	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 20; j++) {
			if (i < 32) {
				mGameBoardMatrix.push_back(0);
			}
			else {
				mGameBoardMatrix.push_back(2);
			}
			
		}
	}

	mGameBoardMatrix[670] = 0;
	mGameBoardMatrix[650] = 0;




	createNewBlock(mCurrentBlock);
	mBlockTicks = SDL_GetTicks();
	mLineState = INPLAY;
	mIsGameActive = true;

	while (!mQuit) {
		mKeyPress = NONE;

		mInput->handleInput();
		if (mIsGameActive) {
			mUpdate->updateGame();
		}
		renderGame();
	}

	destroyResources();
}



void Game::renderGame() {
	SDL_RenderClear(mRenderer);

	SDL_RenderCopy(mRenderer, mGameBackground, NULL, &mGameBackgroundRect);
	SDL_RenderCopy(mRenderer, mGameBoard, NULL, &mGameBoardRect);
	
	//render game board
	for (int i = 0; i < mGameBoardMatrix.size(); i++) {
		if (mGameBoardMatrix[i] != 0) {
			SDL_Texture* texture;

			switch (mGameBoardMatrix[i]) {
			case 1:
				texture = mCompletedTile;
				break;
			case 2:
				texture = mBlueTile;
				break;
			case 3:
				texture = mTealTile;
				break;
			case 4:
				texture = mGreenTile;
				break;
			case 5:
				texture = mGoldTile;
				break;
			case 6:
				texture = mOrangeTile;
				break;
			case 7:
				texture = mRedTile;
				break;
			default:
				texture = mRedTile;
				break;
			}

			int screenX = 660 + ((i % 20) * 30);
			int screenY = 30 + ((i / 20) * 30);

			SDL_Rect rect { screenX, screenY, 30, 30 };
			SDL_RenderCopy(mRenderer, texture, NULL, &rect);

			//SDL_DestroyTexture(texture);
			//texture = NULL;
		}	
	}

	/*for (int i = 0; i < mGameBoardMatrix.size(); i++) {
		if (mGameBoardMatrix[i] != 0) {
			cout << i << " - colour: " << mGameBoardMatrix[i] << endl;
		}
	}*/

	
	
	// Render current block
	if (mCurrentBlock->getBlockState() == ACTIVE) {
		for (int i = 0; i < 16; i++) {
			if (mCurrentBlock->getPattern().tile[i] != 0) {
				SDL_Texture* texture;

				switch (mCurrentBlock->getPattern().tile[i]) {
				case 1:
					texture = mCompletedTile;
					break;
				case 2:
					texture = mBlueTile;
					break;
				case 3:
					texture = mTealTile;
					break;
				case 4:
					texture = mGreenTile;
					break;
				case 5:
					texture = mGoldTile;
					break;
				case 6:
					texture = mOrangeTile;
					break;
				case 7:
					texture = mRedTile;
					break;
				default:
					texture = mRedTile;
					break;
				}

				int y = i / 4;
				int x = i - (4 * y);
				int startX = 660;
				int tileWidth = 30;
				//int screenX = startX - (mCurrentBlock->getPattern().leftX * tileWidth) + (x * 30) + (mCurrentBlock->mX * 30);
				//int screenY = 30 + (y * 30) + (mCurrentBlock->mY * 30) - (mCurrentBlock->getPattern().topY * 30);
				int screenX = startX + (x * 30) + (mCurrentBlock->mX * 30);
				int screenY = 30 + (y * 30) + (mCurrentBlock->mY * 30);

				SDL_Rect rect{ screenX, screenY, 30, 30 };
				SDL_RenderCopy(mRenderer, texture, NULL, &rect);
			}
		}
	}

	if (!mIsGameActive) {
		SDL_Texture* texture = mRedTile;
		SDL_Rect rect{ 10, 10, 30, 30 };
		SDL_RenderCopy(mRenderer, texture, NULL, &rect);
	}
	

	SDL_RenderPresent(mRenderer);

}

void Game::destroyResources() {

}