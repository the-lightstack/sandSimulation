#include <iostream>
#include <string>
#include "SDL/SDL.h"


class SandGrain{
	public:
		int x;
		int y;
};

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
		screenSurface = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
			return true;			

		}

		void onLoop();		// Calculating game logic
		void onRender();	// Displaying new state
		
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
				//onRender();
			}
		 	return 0;
				
		}
};


void initSDLConfigs(void){
		
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Falling Sand","Falling Sand");
	
}


int main(void){
	SandGrain sg;
	sg.x = 10;
	sg.y = 12;
	AnimationApp sandApp;	

	initSDLConfigs();
	sandApp.runWindow();
	

	return 0;
}
