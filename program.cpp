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
	
		void testShit(int** gameB_p){
			printf("Pointer 1: %d\n",*(*gameB_p));
			gameB_p++;
			printf("Pointer 2: %d\n",gameB_p[94][4]);

		}
		
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
		
		void initialize(int gameWidth, int gameHeight, int** gameBoard_p,int gameVertRows,int gameHorzRows){
			width = gameWidth;
			height = gameHeight;
			gameBoard = gameBoard_p;
			gameVerticalRows = gameVertRows;
			gameHorizontalRows = gameHorzRows;	



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
		
		void drawRect(){
			SDL_Rect rectangle;
			
			rectangle.x = 10;
			rectangle.y = 10;
			rectangle.w = 200;
			rectangle.h = 100;
			
			// #1e118e	
			SDL_SetRenderDrawColor(programRenderer,0x1e,0x11,0x8e,0xff);
			SDL_RenderClear(programRenderer);
			
			SDL_SetRenderDrawColor(programRenderer,0xdf,0xdf,0x00,0xff);
			SDL_RenderFillRect(programRenderer,&rectangle);

			SDL_RenderPresent( programRenderer );
		}

		bool onInit(void){
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
				return false;
			}
			programWindow = SDL_CreateWindow("Falling Sand",100,100,width,height,0);
			programRenderer = SDL_CreateRenderer(programWindow,-1,0);			
		
			return true;			

		}

		void onRender(void){
			drawRect();
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
		

		// Defining constructor
		Game(int width,int height,int sandGrainSize){
			windowWidth = width;
			windowHeight = height;	
			sandboxSize = sandGrainSize;
			SDL_Color sandColor = {0xE6,0xBD,0x05,0xff};

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
			
			sandApp.initialize(windowWidth,windowHeight,gameBoard,verticalRowSize,horizontalRowsSize);
	
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
