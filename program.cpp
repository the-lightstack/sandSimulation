#include <iostream>
#include <string>
#include "SDL2/SDL.h"

//const static width = 640;
//const static height = 480;

class SandGrain{
	public:
		int x;
		int y;
};
/*
void drawRect(SDL_Surface* screen){
	// Creating surface to draw to 
	SDL_Surface *s;	
	s = SDL_CreateRGBSurface(0,640,480,32,0,0,0,0);
	
	// Creating rect that will be drawn	
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.w = 200;
	rect.h = 100;
	
	// Drawing Rect to new surface s
	SDL_FillRect(s,&rect,SDL_MapRGB(s->format, 0, 0, 100));
	
	// Blitting new surface to surf passed as parameter

	SDL_BlitSurface(s,NULL,screen,NULL);
}
*/

class AnimationApp{
	private:	
		bool _running = true;

	public:	
		SDL_Surface* screenSurface;
		SDL_Window* programWindow;
		SDL_Renderer* programRenderer;


		int width = 640;
		int height = 480;

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
			/*
			SDL_Rect rectangle;
			
			rectangle.x = 10;
			rectangle.y = 10;
			rectangle.w = 200;
			rectangle.h = 100;
			*/
			
			SDL_SetRenderDrawColor(programRenderer,0xff,0xff,0xff,0xff);
			SDL_RenderClear(programRenderer);
			SDL_RenderPresent( programRenderer );

			//SDL_RenderFillRect(programRenderer,&rectangle);

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




int main(void){
	SandGrain sg;
	sg.x = 10;
	sg.y = 12;

	AnimationApp sandApp;	

	sandApp.runWindow();
	

	return 0;
}
