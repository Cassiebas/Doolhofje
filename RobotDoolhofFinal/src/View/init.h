#ifndef INIT
#define INIT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720
#define TXTR_ROBOT (char *)"View/Textures/robot.png"

namespace view {
	class init
	{
		public:
			void sdl(SDL_Window **window, SDL_Renderer **renderer);
			void properShutdown(SDL_Window **window, SDL_Renderer **renderer);
	};
}

#endif
