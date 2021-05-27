#include <iostream>
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
		long *gameBoard;

		AnimationApp(int gameWidth, int gameHeight, long* gameBoard_p){
			width = gameWidth;
			height = gameHeight;
			gameBoard = gameBoard_p;
			printf("gameboard: %d \n",&gameBoard);
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

		void onLoop();		// Calculating game logic
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
				//onLoop();
				onRender();
			}
		 	return 0;
				
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

			
		// Defining constructor
		Game(int width,int height,int sandGrainSize){
			windowWidth = width;
			windowHeight = height;	
			sandboxSize = sandGrainSize;
			SDL_Color sandColor = {0xE6,0xBD,0x05,0xff};

			// Creating game-board array
			horizontalRowsSize = (int)windowWidth/sandboxSize;
			verticalRowSize = (int)windowHeight/sandboxSize;
			
			//uint8_t gameBoard [verticalRowSize] [horizontalRowsSize];
			int gameBoard [verticalRowSize] [horizontalRowsSize] = {}; // Zeroeing it 
			
			// Making bottom row ROCK 
			for (int i = 0;i<horizontalRowsSize;i++){
				gameBoard[verticalRowSize-1][i] = ROCK;
			}

			// Printing for Debugging :)
			printf("Gameboard height:%d, width: %d\n",verticalRowSize,horizontalRowsSize);
			for (int i = 0; i<horizontalRowsSize;i++){
				printf("%d | ",gameBoard[verticalRowSize-1][i]);
			}
			long* gameBoardPointer;			
			gameBoardPointer = &gameBoard[0];
			AnimationApp sandApp = AnimationApp(windowWidth,windowHeight,gameBoardPointer);
		

		}
		
	};




int main(void){

	Game game = Game(640,480,5);

	// AnimationApp sandApp;	
	// sandApp.runWindow();
	

	return 0;
}
