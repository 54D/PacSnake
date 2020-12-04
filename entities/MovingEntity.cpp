#include <cstdlib>
#include <ctime>
#include "MovingEntity.h"

/* PUBLIC */

MovingEntity::MovingEntity() {}

MovingEntity::MovingEntity(int row, int col, int speed, Direction headingDirection) :
        Entity(row, col), speed(speed), headingDirection(headingDirection) {}


MovingEntity::~MovingEntity() {}

int MovingEntity::get_speed() const {
    return speed;
}

MovingEntity::Direction MovingEntity::get_headingDirection() const {
    return headingDirection;
}

void MovingEntity::set_speed(int speed) {
	if (speed < 0)
		speed = 0;
	else if (speed > MAX_SPEED)
		speed = MAX_SPEED;

    this->speed = speed;
}

void MovingEntity::set_headingDirection(MovingEntity::Direction headingDirection) {
    this->headingDirection = headingDirection;
}

MovingEntity::Direction MovingEntity::get_rotated_headingDirection() {
	switch (headingDirection) {
		case MovingEntity::Direction::NORTH:	return MovingEntity::Direction::EAST;	break;
		case MovingEntity::Direction::EAST:		return MovingEntity::Direction::SOUTH;	break;
		case MovingEntity::Direction::SOUTH:	return MovingEntity::Direction::WEST;	break;
		case MovingEntity::Direction::WEST:		return MovingEntity::Direction::NORTH;	break;
	}
}

/* PROTECTED */

void MovingEntity::set_random_headingDirection() {
    switch (rand() % 4) {
	case 0: headingDirection = Direction::NORTH;	break;
	case 1: headingDirection = Direction::EAST;		break;
	case 2: headingDirection = Direction::SOUTH;	break;
	case 3: headingDirection = Direction::WEST;		break;
    }
}

void MovingEntity::move_forward() {
	switch(headingDirection) {
	case Direction::NORTH:	set_relative_coordinate(-1, 0);	break;
	case Direction::EAST:	set_relative_coordinate(0, 1);	break;
	case Direction::SOUTH:	set_relative_coordinate(1, 0);	break;
	case Direction::WEST:	set_relative_coordinate(0, -1);	break;
	}
}
