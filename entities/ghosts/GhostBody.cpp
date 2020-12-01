#include "GhostBody.h"

GhostBody::~GhostBody() {}

GhostBody::GhostBody(int row, int col, int speed, Direction headingDirection, GhostBody* next) :
	MovingEntity(row, col, speed, headingDirection), next(next) {}

void GhostBody::move_forward() {
	switch(headingDirection) {
		case Direction::NORTH:	set_relative_coordinate(-1, 0);	break;
		case Direction::EAST:	set_relative_coordinate(0, 1);		break;
		case Direction::SOUTH:	set_relative_coordinate(1, 0);		break;
		case Direction::WEST:	set_relative_coordinate(0, -1);	break;
	}
}
