#include "MovingEntity.h"

MovingEntity::~MovingEntity() {}

int MovingEntity::get_speed() const {
    return speed;
}

MovingEntity::Direction MovingEntity::get_headingDirection() const {
    return headingDirection;
}

void MovingEntity::set_speed(int speed) {
    if (speed < 0)
        return;

    this->speed = speed;
}

void MovingEntity::set_headingDirection(MovingEntity::Direction headingDirection) {
    this->headingDirection = headingDirection;
}

MovingEntity::MovingEntity() {}

MovingEntity::MovingEntity(int row, int col, int speed, Direction headingDirection) :
        Entity(row, col), speed(speed), headingDirection(headingDirection) {}