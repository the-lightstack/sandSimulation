#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "SDL2/SDL.h"
#include <functional>


class FieldTypes{
	public:
		const static int EMPTY = 0;	
		const static int SAND = 1;	
		const static int ROCK = 2;	
		
};

struct Vector{
	int x;
	int y;
};

class AnimationApp{
	private:	
		bool _running = true;

	public:	
		
		SDL_Surface* screenSurface;
		SDL_Window* programWindow;
		SDL_Renderer* programRenderer;
			

		int width;
		int height;
		int** gameBoard;
		int gameVerticalRows;
		int gameHorizontalRows;
		int sandBoxScale;
		
		Vector generator {(int)width/2,(int)height/5};
		bool generatorOn = false;

		// Defining placeholder for callback
		std::function<void (int,int)> placeSandPiecePH;
		std::function<void (int,int)> placeRockPiecePH;	 // PH = PlaceHolder
	
		SDL_Color sandColor;
		SDL_Color emptyColor;
		SDL_Color rockColor;
	
		bool leftMouseButtonDown = false;
		bool rightMouseButtonDown = false;
		bool spaceIsPressed = false;

	
		void printGameBoard(){
			for (int i = 0;i<gameVerticalRows;i++){
				for (int j = 0;j<gameHorizontalRows;j++){
					printf("%d ",gameBoard[i][j]);
				}
				printf("\n");
			}
			
		}
		
		void setPlaceSandCallback(std::function<void(int,int)> callbackFunc){
			placeSandPiecePH = callbackFunc;
		}
		void setPlaceRockCallback(std::function<void(int,int)>callbackFunc){	
			placeRockPiecePH = callbackFunc;	
		}

		bool onInit(void){
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
				return false;
			}
			programWindow = SDL_CreateWindow("Falling Sand",100,100,width,height,0);
			programRenderer = SDL_CreateRenderer(programWindow,-1,0);			
		
			return true;			

		}


		
		void initialize(int gameWidth, int gameHeight, int** gameBoard_p,int gameVertRows,int gameHorzRows,SDL_Color gameSandColor, SDL_Color gameEmptyColor,SDL_Color gameRockColor,int sandBoxSize){
			width = gameWidth;
			height = gameHeight;
			gameBoard = gameBoard_p;
			gameVerticalRows = gameVertRows;
			gameHorizontalRows = gameHorzRows;	
			
			sandBoxScale = sandBoxSize;
	
			sandColor = gameSandColor;	
			emptyColor = gameEmptyColor;
			rockColor = gameRockColor;
			
			onInit();

		}


		void onEvent(SDL_Event event){
			switch (event.type){
				case SDL_QUIT:   
					// Handling keydown events here
					_running = false;   
					SDL_Quit();
					break;  
			case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT){
						leftMouseButtonDown = true;
					}else if(event.button.button = SDL_BUTTON_RIGHT){
						if (spaceIsPressed){
							generatorOn = true;
							generator.x = event.button.x;	
							generator.y = event.button.y;
						}
						else{	
							rightMouseButtonDown = true;
						}


					}
					/*
					if (event.button.button == SDL_BUTTON_LEFT){
						placeSandPiecePH(event.button.x,event.button.y);
					}else if(event.button.button = SDL_BUTTON_RIGHT){
						placeRockPiecePH(event.button.x,event.button.y);
					}
					*/
					break;
	
			case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT){
						leftMouseButtonDown = false;
					}else if(event.button.button = SDL_BUTTON_RIGHT){
						rightMouseButtonDown = false;
					}
				break;			
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_SPACE ){
					spaceIsPressed = true;	
				}
				break;

			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_SPACE ){
					spaceIsPressed = false;	
				}
				break;
			}   
		}
		
		void drawRect(int xPos,int yPos,int scale,SDL_Color color){
			SDL_Rect rectangle;
			
			rectangle.x = xPos;
			rectangle.y = yPos;
			rectangle.w = scale;
			rectangle.h = scale;
			
			// 	Setting background color	
			//	SDL_SetRenderDrawColor(programRenderer,0xdf,0xdf,0x00,0xff);
			//	SDL_RenderClear(programRenderer);
			
			SDL_SetRenderDrawColor(programRenderer,color.r,color.g,color.b,color.a);
			SDL_RenderFillRect(programRenderer,&rectangle);

		}
		
		void showRender(){
			SDL_RenderPresent( programRenderer );
		}
		
		void callDrawFunctions(){
			if (leftMouseButtonDown){
				int x,y;
				SDL_GetMouseState(&x,&y);
				placeSandPiecePH(x,y);
				
			}else if(rightMouseButtonDown){
				int x,y;
				SDL_GetMouseState(&x,&y);
				placeRockPiecePH(x,y);
			}
			
		}
		int genMutatedColor(int org){
			int mutationStrength = 10;
			return (unsigned char)(org+(rand()%mutationStrength)-((int)mutationStrength/2)); 
		}

		void onRender(void){
			// Looping through entire game-map-array			
			SDL_Color tempCol;
		
			for (int row = 0; row<gameVerticalRows;row++){
				for (int col = 0;col<gameHorizontalRows;col++){
					int xCoord = col*sandBoxScale;
					int yCoord = row*sandBoxScale;
					
					switch (gameBoard[row][col]){
						case FieldTypes::SAND:
							// changing color a bit
							srand(row*col);
							// Define lambda
							// auto generateColorMutation = [&](int org) { return org+(rand()%mutationStrength)-((int)mutationStrength/2); };

							tempCol = {genMutatedColor(sandColor.r),genMutatedColor(sandColor.g),genMutatedColor(sandColor.b),0xff};

							drawRect(xCoord,yCoord,sandBoxScale,tempCol);
							break;
						case FieldTypes::EMPTY:
							drawRect(xCoord,yCoord,sandBoxScale,emptyColor);
							break;
						case FieldTypes::ROCK:
							drawRect(xCoord,yCoord,sandBoxScale,rockColor);
							break;
									
					}	
				
					
				}
			}
			callDrawFunctions();
			
			if (generatorOn){
				placeSandPiecePH(generator.x,generator.y);
			}
			
			// placeSandPiecePH(200,4);
			/*	
			drawRect(0,0,100,sandColor);
			drawRect(100,0,100,emptyColor);
			drawRect(200,0,100,rockColor);
			*/
			showRender();
		}
		
		bool runWindow(void){
	
			if (onInit() == false){
				return -1;
			}
			while (_running){
				// Sending all events to handler
				SDL_Event dummyEvent;
				while (SDL_PollEvent(&dummyEvent)){
					onEvent(dummyEvent);
				}
				onRender();
			}
		 	return 0;
				
		}
		
		void cleanSDL(){};

		void loopTurn(){
		// Does all the things if running is true else quits?			
			if (_running){	
				// Handling all events
				SDL_Event dummyEvent;
				while (SDL_PollEvent(&dummyEvent)){
					onEvent(dummyEvent);
				}
				// Rendering entire screen 
				onRender(); 
		
			}else{
				cleanSDL();
				exit(0);
			}
			
		}


};

class Game{
	private:
		int horizontalRowsSize;
		int verticalRowSize;
		
	public:
		int windowWidth;
		int windowHeight;
		//AnimationApp sandApp;
		int sandboxSize;

		int **gameBoard;			
		int **secondaryGameBoard;
	
		void copyBoard(int** src,int** dest){
			for (int row = 0;row<verticalRowSize;row++){
				for (int col = 0;col<horizontalRowsSize;col++){
				dest[row][col] = src[row][col];
				}
			}
		}

		void updateGameStates(){
			bool madeMove;
			for (int row = 0;row<verticalRowSize;row++){
				for (int col = 0;col<horizontalRowsSize;col++){
					// looking into secondary gameBoard and then changing main gameBoard -> later copying mainGameBoard back into secondary Game board			
					if (secondaryGameBoard[row][col] == FieldTypes::SAND){
						madeMove = false;
						// Checking if 1 down is out of bounds
						if (row+1<verticalRowSize){
							if (secondaryGameBoard[row+1][col] == FieldTypes::EMPTY){
								gameBoard[row+1][col] = FieldTypes::SAND;
								// Maybe make current pos empty
								gameBoard[row][col] = FieldTypes::EMPTY;
								madeMove = true;
							}
						}
						// Chained if for error prevention
						// check for not out of map and not moved yet
						// Moving one down + one left
						if (row+1<verticalRowSize && col-1>=0 && !madeMove){
							if (secondaryGameBoard[row+1][col-1] == FieldTypes::EMPTY && secondaryGameBoard[row][col-1] == FieldTypes::EMPTY){
								gameBoard[row+1][col-1] = FieldTypes::SAND;
								gameBoard[row][col] = FieldTypes::EMPTY;
								madeMove = true;

							}
						}

						if (row+1<verticalRowSize && col+1>=0 && !madeMove){
							if (secondaryGameBoard[row+1][col+1] == FieldTypes::EMPTY && secondaryGameBoard[row][col+1] == FieldTypes::EMPTY){
								gameBoard[row+1][col+1] = FieldTypes::SAND;
								gameBoard[row][col] = FieldTypes::EMPTY;
								madeMove = true;

							}
						}
					}				
				}
			}
			// Copying new array back into old one
			copyBoard(gameBoard,secondaryGameBoard);
		}

		AnimationApp sandApp;

		SDL_Color sandColor;
		SDL_Color emptyColor;
		SDL_Color rockColor;
		
		// in milli seconds	
		int updateSandPositionDelay = 4;

		void placeSandPiece(int x,int y){
			int gridX = (int)x/sandboxSize;
			int gridY = (int)y/sandboxSize;
				
			gameBoard[gridY][gridX] = FieldTypes::SAND;
		}
		
		void placeRockPiece(int x, int y){
			int gridX = (int)x/sandboxSize;
			int gridY = (int)y/sandboxSize;
				
			gameBoard[gridY][gridX] = FieldTypes::ROCK;
		}
		
	
		// Defining constructor
		Game(int width,int height,int sandGrainSize){
			windowWidth = width;
			windowHeight = height;	
			sandboxSize = sandGrainSize;
	
			sandColor = {0xE6,0xBD,0x05,0xff};
			emptyColor = {0x44,0x24,0xdb,0xff};
			rockColor = {0x54,0xab,0x99,0xff};

			// Creating game-board array
			horizontalRowsSize = (int)windowWidth/sandboxSize;
			verticalRowSize = (int)windowHeight/sandboxSize;
			

			// Creating 2D Game Board Array			
			gameBoard = new int* [verticalRowSize];
			for (int i = 0;i<verticalRowSize;i++){
				gameBoard[i] = new int[horizontalRowsSize];
			}
	
			// Initializing secondary game Board
			secondaryGameBoard = new int* [verticalRowSize];
			for (int i = 0;i<verticalRowSize;i++){
				secondaryGameBoard[i] = new int[horizontalRowsSize];
			}
		
			printf("Game board 1: %d\n",gameBoard[0][2]);
			// Making bottom row ROCK 
			for (int i = 0;i<horizontalRowsSize;i++){
				gameBoard[verticalRowSize-2][i] = FieldTypes::ROCK;
			}
			// gameBoard[64][40] = FieldTypes::SAND;
			// gameBoard[62][40] = FieldTypes::SAND;
			
			// gameBoard[70][20] = FieldTypes::ROCK;
		
			copyBoard(gameBoard,secondaryGameBoard);
			// Printing for Debugging :)
			printf("Gameboard height: %d, width: %d\n",verticalRowSize,horizontalRowsSize);
			
			// sandApp = AnimationApp(windowWidth,windowHeight,gameBoard,verticalRowSize,horizontalRowsSize);
			
			sandApp.initialize(windowWidth,windowHeight,gameBoard,verticalRowSize,horizontalRowsSize,sandColor,emptyColor,rockColor,sandboxSize);
			sandApp.setPlaceSandCallback([&](int x,int y){ placeSandPiece(x,y);});
			sandApp.setPlaceRockCallback([&](int x,int y){ placeRockPiece(x,y);});
		
		}

		void runGame(){
			updateGameStates();
			while (true){
				// Changing positions of sand
				updateGameStates();
				sandApp.loopTurn();
				SDL_Delay(updateSandPositionDelay);
		
			}
		}
	};

int main(void){

	Game game = Game(640,480,5);
	game.runGame();
	
	return 0;
}
