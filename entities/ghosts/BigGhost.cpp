#include <cstdlib>
#include <ctime>
#include "BigGhost.h"

BigGhost::BigGhost(int row, int col, int speed, Direction headingDirection) :
	GhostBody(row, col, speed, headingDirection) {

	GhostBody* currentGhostBody = this;
	// [2]
	currentGhostBody->next = new GhostBody(row, col + 1, speed, headingDirection);
	currentGhostBody = currentGhostBody->next;
	// [3]
	currentGhostBody->next = new GhostBody(row + 1, col + 1, speed, headingDirection);
	currentGhostBody = currentGhostBody->next;
	// [4]
	currentGhostBody->next = new GhostBody(row + 1, col, speed, headingDirection);
	currentGhostBody = currentGhostBody->next;

	set_random_stepUntilDirctionChange();
}

BigGhost::~BigGhost() {
	GhostBody* currentGhostBody = this->next;
	while (currentGhostBody != this) {
		GhostBody* nextGhostBody = currentGhostBody->next;
		delete currentGhostBody;
		currentGhostBody = nextGhostBody;
	}
}

void BigGhost::set_speed(int speed) {
	if (speed < 0 || speed > MAX_SPEED)
		return;

	GhostBody* currentGhostBody = this;
	do {
		currentGhostBody->speed = speed;
		currentGhostBody = currentGhostBody->next;
	} while(currentGhostBody != this);
}

void BigGhost::set_headingDirection(MovingEntity::Direction headingDirection) {
	GhostBody* currentGhostBody = this;
	do {
		currentGhostBody->headingDirection = headingDirection;
		currentGhostBody = currentGhostBody->next;
	} while(currentGhostBody != this);
}

void BigGhost::move_forward() {
	GhostBody* currentGhostBody = this;
	do {
		switch(currentGhostBody->headingDirection) {
			case Direction::NORTH:	currentGhostBody->set_relative_coordinate(-1, 0);	break;
			case Direction::EAST:	currentGhostBody->set_relative_coordinate(0, 1);	break;
			case Direction::SOUTH:	currentGhostBody->set_relative_coordinate(1, 0);	break;
			case Direction::WEST:	currentGhostBody->set_relative_coordinate(0, -1);	break;
		}
		currentGhostBody = currentGhostBody->next;
	} while (currentGhostBody != this);

	stepCount++;
	if (stepCount >= stepUntilDirctionChange){
		stepCount = 0;
		set_random_stepUntilDirctionChange();
		set_random_headingDirection();
	}
}

void BigGhost::set_random_stepUntilDirctionChange(int lower, int upper) {
	srand(time(NULL));
	stepUntilDirctionChange = (rand() % (upper - lower + 1)) + lower;
}

void BigGhost::set_random_headingDirection() {
	srand(time(NULL));
	switch (rand() % 4) {
	case 0: set_headingDirection(Direction::NORTH);	break;
	case 1: set_headingDirection(Direction::EAST);	break;
	case 2: set_headingDirection(Direction::SOUTH);	break;
	case 3: set_headingDirection(Direction::WEST);	break;
	}
}
