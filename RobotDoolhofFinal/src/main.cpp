#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include "Model/maze.h"
#include "Model/input.h"
#include "View/init.h"
#include "Controller/robot.h"
#include "Controller/path.h"


using namespace model;
using namespace view;
using namespace controller;


int main(void) {

	SDL_Window *window;
	SDL_Renderer *renderer;
	srand(time(NULL));

	maze maze;
	robot robot;
	input input;
	init init;
	
	SDL_bool quit;
	SDL_Point counter = {0, 0};
	SDL_Point startMaze = {0, 0}, endMaze = {SCREEN_WIDTH/ROOM_SIZE-1, SCREEN_HEIGHT/ROOM_SIZE-1};
	bool endGenerating = 0;
	init.sdl(&window, &renderer);
		
	maze.initRooms();
	maze.setStartEnd(startMaze, endMaze);
	robot.init(renderer, &maze);
	
	while (!quit) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		quit = input.update();
		if (!endGenerating) { 	
			maze.generate(&counter, &endGenerating);
		}
		else {
			robot.update();
		}
		maze.stupidlyCorrectBorders(renderer);
		robot.draw(renderer);
		maze.draw(renderer);	
		SDL_RenderPresent(renderer);
	}
	init.properShutdown(&window, &renderer);

	return 0;	
}