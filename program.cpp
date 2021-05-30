#include <iostream>
#include <stdio.h>
#include <string>
#include "SDL2/SDL.h"



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
	
		SDL_Color sandColor;
		SDL_Color emptyColor;
		SDL_Color rockColor;
	
	
		void printGameBoard(){
			for (int i = 0;i<gameVerticalRows;i++){
				for (int j = 0;j<gameHorizontalRows;j++){
					printf("%d ",gameBoard[i][j]);
				}
				printf("\n");
			}
			
		}

		/*
		AnimationApp(int gameWidth, int gameHeight, int** gameBoard_p,int gameVertRows,int gameHorzRows){
			width = gameWidth;
			height = gameHeight;
			gameBoard = gameBoard_p;
			gameVerticalRows = gameVertRows;
			gameHorizontalRows = gameHorzRows;	

			testShit(gameBoard);
			printGameBoard();
		}
		*/
		bool onInit(void){
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
				return false;
			}
			programWindow = SDL_CreateWindow("Falling Sand",100,100,width,height,0);
			programRenderer = SDL_CreateRenderer(programWindow,-1,0);			
		
			return true;			

		}


		
		void initialize(int gameWidth, int gameHeight, int** gameBoard_p,int gameVertRows,int gameHorzRows,SDL_Color gameSandColor, SDL_Color gameEmptyColor,SDL_Color gameRockColor){
			width = gameWidth;
			height = gameHeight;
			gameBoard = gameBoard_p;
			gameVerticalRows = gameVertRows;
			gameHorizontalRows = gameHorzRows;	
	
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
					printf("Clicked at (%d|%d)\n",event.button.x,event.button.y);
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
		

		void onRender(void){
			
			drawRect(0,0,100,sandColor);
			drawRect(100,0,100,emptyColor);
			drawRect(200,0,100,rockColor);
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
		enum {EMPTY,SAND,ROCK};

		int **gameBoard;			
		
		void updateGameStates(){};
		AnimationApp sandApp;

		SDL_Color sandColor;
		SDL_Color emptyColor;
		SDL_Color rockColor;


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
		
			printf("Game board 1: %d\n",gameBoard[0][2]);
			// Making bottom row ROCK 
			for (int i = 0;i<horizontalRowsSize;i++){
				gameBoard[verticalRowSize-1][i] = ROCK;
			}

			// Printing for Debugging :)
			printf("Gameboard height: %d, width: %d\n",verticalRowSize,horizontalRowsSize);
			
			// sandApp = AnimationApp(windowWidth,windowHeight,gameBoard,verticalRowSize,horizontalRowsSize);
			
			sandApp.initialize(windowWidth,windowHeight,gameBoard,verticalRowSize,horizontalRowsSize,sandColor,emptyColor,rockColor);
	
		}

		void runGame(){
			while (true){
				// Changing positions of sand
				updateGameStates();
				sandApp.loopTurn();
		
			}
		}
	};




int main(void){

	Game game = Game(640,480,5);
	game.runGame();
	
	

	return 0;
}
