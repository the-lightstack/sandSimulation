#include <iostream>
#include <string>
#include "SDL/SDL.h"

//const static width = 640;
//const static height = 480;

class SandGrain{
	public:
		int x;
		int y;
};

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

class AnimationApp{
	private:	
		bool _running = true;
		SDL_Surface* screenSurface;
	
	public:	
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
		bool onInit(void){
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
				return false;
			}

			SDL_WM_SetCaption("Falling Sand","Falling Sand");
			screenSurface = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
			//SDL_Renderer* screenRenderer = SDL_CreateRenderer()			
	
		
			return true;			

		}

		void onLoop();		// Calculating game logic
		void onRender(void){
			//drawRect(screenSurface);
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
