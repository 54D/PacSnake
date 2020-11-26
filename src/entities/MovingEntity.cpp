#include "MovingEntity.h"

MovingEntity::~MovingEntity() {}

double MovingEntity::get_speed() const {
	return speed;
}

MovingEntity::Direction MovingEntity::get_headingDirection() const {
	return headingDirection;
}

void MovingEntity::set_speed(double speed) {
	if (speed < 0.0)
		return;
		
	this->speed = speed;
}

void MovingEntity::set_headingDirection(MovingEntity::Direction headingDirection) {
	this->headingDirection = headingDirection;
}

MovingEntity::MovingEntity() {}

MovingEntity::MovingEntity(double row, double col, double speed, Direction headingDirection) :
	Entity(row, col), speed(speed), headingDirection(headingDirection) {}