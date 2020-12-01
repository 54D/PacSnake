#include <cstdlib>
#include <ctime>

#include "NormalGhost.h"

NormalGhost::NormalGhost(int row, int col, int speed, Direction headingDirection) :
	GhostBody(row, col, speed, headingDirection) {
	set_random_stepUntilDirctionChange();
}
	
NormalGhost::~NormalGhost() {}

void NormalGhost::move_forward() {
	switch(headingDirection) {
		case Direction::NORTH:	set_relative_coordinate(-1, 0);	break;
		case Direction::EAST:	set_relative_coordinate(0, 1);		break;
		case Direction::SOUTH:	set_relative_coordinate(1, 0);		break;
		case Direction::WEST:	set_relative_coordinate(0, -1);	break;
	}
	stepCount++;
	if (stepCount >= stepUntilDirctionChange){
		stepCount = 0;
		set_random_stepUntilDirctionChange();
		set_random_headingDirection();
	}
}

void NormalGhost::set_random_stepUntilDirctionChange(int lower, int upper) {
	srand(time(NULL));
	stepUntilDirctionChange = (rand() % (upper - lower + 1)) + lower;
}