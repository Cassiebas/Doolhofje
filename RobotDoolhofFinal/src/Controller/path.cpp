#include "path.h"

void controller::path::init(maze *yourMaze) {
	SDL_Point counter = {0, 0};
	room *tmp;
	theMaze = yourMaze;	
	for (int j = 0; j < SCREEN_HEIGHT/ROOM_SIZE; j++) {
		for (int i = 0; i < SCREEN_WIDTH/ROOM_SIZE; i++) {
			counter.x = i * ROOM_SIZE;
			counter.y = j * ROOM_SIZE;
			tmp = theMaze->getRoomByCoords(counter);
			nodes[i][j].setCurrentRoom(tmp);
			nodes[i][j].setMissingWalls(); 
			nodes[i][j].setWeightWalls();

		}
	}
}

void controller::path::getNextRoom(SDL_Point *counter, int *weight_counter) {
	int weight[4], min_weight = INT_MAX;//, second_min_weight;
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, top); 
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, left);
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, right);
	nodes[counter->x][counter->y].setWeightOpening(weight_counter, bottom); 

	weight[top] = nodes[counter->x][counter->y].getWeight(top);
	weight[bottom] = nodes[counter->x][counter->y].getWeight(bottom);
	weight[right] = nodes[counter->x][counter->y].getWeight(right);
	weight[left] = nodes[counter->x][counter->y].getWeight(left);

	for (int i = 0; i < 4; i++) {
		if (weight[i] <= INT_MAX/2&& weight[i]  < min_weight) {
			min_weight = weight[i];

		}
	}
	if (weight[top] != INT_MAX && weight[top] == min_weight && 
	    counter->y > 0) {
		counter->y--;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x][counter->y+1]);
		//printf("top is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, bottom);	
		*weight_counter -= 1;

	}
	else if (weight[right] != INT_MAX && weight[right] == min_weight && 
    		counter->x < SCREEN_WIDTH/ROOM_SIZE) {
		counter->x++;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x-1][counter->y]);
		//printf("right is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, left);	
		*weight_counter -= 1;
	
	}
	else if (weight[left] != INT_MAX && weight[left] == min_weight && 
	    counter->x > 0) {
		counter->x--;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x+1][counter->y]);
		//printf("left is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, right);	
		*weight_counter -= 1;
	}
	else if (weight[bottom] != INT_MAX && weight[bottom] == min_weight && 
	    counter->y < SCREEN_WIDTH/ROOM_SIZE) {
		counter->y++;
		nodes[counter->x][counter->y].setPrevNode(&nodes[counter->x][counter->y-1]);
		//printf("bottom is the best choice: %d, %d\n", counter->x, counter->y);
		*weight_counter += 2;
		nodes[counter->x][counter->y].setWeightOpening(weight_counter, top);	
		*weight_counter -= 1;
	}
}

void controller::path::setWeightFinish(SDL_Point finish) {
	int tmp = INT_MAX/2;	
	nodes[finish.x][finish.y].setWeightOpening(&tmp, top); 
	nodes[finish.x][finish.y].setWeightOpening(&tmp, left);
	nodes[finish.x][finish.y].setWeightOpening(&tmp, right);
	tmp = 0;
	nodes[finish.x][finish.y].setWeightOpening(&tmp, bottom); 
}

bool controller::path::isFinished(SDL_Point counter) {
	if (counter.x == SCREEN_WIDTH/ROOM_SIZE-1 && counter.y == SCREEN_HEIGHT/ROOM_SIZE-1) {
		return true;
	}
	return false;
}

void controller::path::setWeightStart(void) {
	int tmp = INT_MAX/2;
	nodes[0][0].setWeightOpening(&tmp, top);
}