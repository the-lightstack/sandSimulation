#include <program.cpp>

void AnimationApp::onEvent(SDL_Event* event){
	printf("Caught event!\n");
	switch (event.type){
		case SDL_KEYDOWN:	
		// Handling keydown events here
			if (event.keysym.SDL_Scancode == SDL_SCANCODE_ESCAPE){
			_running = false;	
			}
		break;	

	}
}
