#include "node.h"

void view::node::setVisited(void) { 
	visited = true;
}
void view::node::setWeightBegin(void) { 
	weight[top] = INT_MAX; 
}
void view::node::setCurrentRoom(room *currRoom) {
	current_room = currRoom;
}
void view::node::setPrevRoom(room *prevRoom) { 
	prev_room = prevRoom;
}
void view::node::setPrevNode(node *prevNode) { 
	prev_node = prevNode;
}
void view::node::setWeightWalls() { 
	if (missing_wall[top] == 0)
		weight[top] = INT_MAX;
	if (missing_wall[bottom] == 0)
		weight[bottom] = INT_MAX;
	if (missing_wall[right] == 0)
		weight[right] = INT_MAX;
	if (missing_wall[left] == 0)
		weight[left] = INT_MAX;
}
void view::node::setWeightOpening(int *weight_counter, sides Side) { 
	if (missing_wall[Side] == true) {
		weight[Side] += *weight_counter;
	}
}
void view::node::setWeightBacktracking(sides currentRoomWeight) {
	switch (currentRoomWeight) {
		case top:
			weight[top] = INT_MAX;
			//setWeightBacktrackingPrevNode(bottom);
		case bottom:
			weight[bottom] = INT_MAX;
			//setWeightBacktrackingPrevNode(top);
		case left:
			weight[left] = INT_MAX;
			//setWeightBacktrackingPrevNode(right);
		case right:
			weight[right] = INT_MAX;
			//setWeightBacktrackingPrevNode(left);
		default:
			break;
	}	
}
void view::node::setWeightBacktrackingPrevNode(sides currentRoomWeight) { 
	switch (currentRoomWeight) {
		case top:
			weight[top] = INT_MAX;
		case bottom:
			weight[bottom] = INT_MAX;
		case left:
			weight[left] = INT_MAX;
		case right:
			weight[right] = INT_MAX;
		default:
			break;
	}
}

int view::node::getWeight(sides theSide) {
	switch (theSide) {
		case top:
			return weight[top];
		case bottom:
			return weight[bottom];
		case left:
			return weight[left];
		case right:
			return weight[right];
		default:
			break;
	}
	return INT_MAX;
}

void view::node::setMissingWalls() {
	//printf("locating segfault\n");
	missing_wall[top] = current_room->isWallMissing(top);
	missing_wall[bottom] = current_room->isWallMissing(bottom);
	missing_wall[right] = current_room->isWallMissing(right);
	missing_wall[left] = current_room->isWallMissing(left);
	//printf("Missing walls: \t top: %d \t bottom: %d \t right: %d \t left: %d \n", missing_wall[top], missing_wall[bottom], missing_wall[right], missing_wall[left]);
}

view::node *view::node::getPrevNode(void) {
	return prev_node;
}
