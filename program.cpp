#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include <eventHandler.h>


class SandGrain{
	public:
		int x;
		int y;
};

class AnimationApp{
	private:	
		bool _running = true;
	
	public:	
		bool onInit();
		void onEvent(SDL_Event* Event); // Handling e.g mouse
		void onLoop();		// Calculating game logic
		void onRender();	// Displaying new state
		
		void runWindow(void){
			while (_running){
				// Sending all events to handler
				SDL_Event dummyEvent;
				while (SDL_PollEvent(&dummyEvent)){
					onEvent(&dummyEvent);
				}
				onLoop();
				onRender();
			}
				
		}
};


void initSDLConfigs(void){
		
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Falling Sand","Falling Sand");
	SDL_Surface* screen = SDL_SetVideoMode(640,480,0,0);
	

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
