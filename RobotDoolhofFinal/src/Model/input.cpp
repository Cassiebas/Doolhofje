#include "input.h"

SDL_bool model::input::update() {
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
				case SDL_QUIT: 
                        		return SDL_TRUE;
					break;
				default:
					break;
		    }
                }
		return SDL_FALSE;
}
