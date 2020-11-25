#include <iostream>
#include "../Entity.h"
#include "Snake.h"

double Snake::INIT_SPEED = 1.0;

Snake::Snake(double row, double col, double speed, Direction headingDirection) :
	SnakeBody(row, col, speed, headingDirection), 
	max_health(INIT_HEALTH), health(INIT_HEALTH), length(INIT_LENGTH), 
	pu_inventory(MAX_PU, PowerUp::PowerUpType::NONE), pu_active(PowerUp::PowerUpType::NONE)
	{
	// Initialise SnakeBody by creating a linked list
	double temp_row = row;
	double temp_col = col;
	SnakeBody* lastSnakeBody = this;
	for (int i = 0; i < length; i++) {
		switch (headingDirection) {
			case Direction::NORTH: 	temp_row += 1.0;	break;
			case Direction::EAST:	temp_col += 1.0;	break;
			case Direction::SOUTH:	temp_row -= 1.0;	break;
			case Direction::WEST:	temp_col -= 1.0;	break;
		}
		SnakeBody* currentSnakeBody = new SnakeBody {temp_row, temp_col, speed, headingDirection};
		lastSnakeBody->next = currentSnakeBody;
		currentSnakeBody->prev = lastSnakeBody;
		lastSnakeBody = currentSnakeBody;
	}
}

Snake::~Snake() {
	SnakeBody* currentSnakeBody = this->next;
	SnakeBody* nextSnakeBody = nullptr;
	while (currentSnakeBody != nullptr) {
		nextSnakeBody = currentSnakeBody->next;
		delete currentSnakeBody;
		currentSnakeBody = nextSnakeBody;
	}
}

int Snake::get_max_health() const {
	return max_health;
}

int Snake::get_health() const {
	return health;
}

int Snake::get_length() const {
	return length;
}

void Snake::set_headingDirection(Direction headingDirection) {
	// Avoid headingDirection is the opposite of the current headingDirection
	if (this->headingDirection == Direction::NORTH && headingDirection == Direction::SOUTH ||
		this->headingDirection == Direction::EAST && headingDirection == Direction::WEST ||
		this->headingDirection == Direction::SOUTH && headingDirection == Direction::NORTH ||
		this->headingDirection == Direction::WEST && headingDirection == Direction::EAST)
		return;
	else
		this->headingDirection = headingDirection;
}

void Snake::move_forward() {
	SnakeBody* currentSnakeBody = this;
	Direction currentHeadingDirection, lastHeadingDirection;
	while (currentSnakeBody != nullptr) {
		// As the speed of the snake might change, so each SnakeBody moves according to its current speed instead of last SnakeBody's coordinate 
		switch(currentSnakeBody->headingDirection) {
			case Direction::NORTH:	currentSnakeBody->set_relative_coordinate(-1 * currentSnakeBody->speed, 0.0);	break;
			case Direction::EAST:	currentSnakeBody->set_relative_coordinate(0.0, currentSnakeBody->speed);		break;
			case Direction::SOUTH:	currentSnakeBody->set_relative_coordinate(currentSnakeBody->speed, 0.0);		break;
			case Direction::WEST:	currentSnakeBody->set_relative_coordinate(0.0, -1 * currentSnakeBody->speed);	break;
		}

		currentHeadingDirection = currentSnakeBody->headingDirection;
		// Change headingDiection according to the last snakeBody
		if (currentSnakeBody->prev != nullptr) {
			currentSnakeBody->headingDirection = lastHeadingDirection;
		}
		lastHeadingDirection = currentHeadingDirection;
		
		
		// Move to next SnakeBody
		currentSnakeBody = currentSnakeBody->next;
	}
}

void Snake::set_speed(double speed) {
	SnakeBody* currentSnakeBody = this;
	while (currentSnakeBody != nullptr) {
		currentSnakeBody->speed = speed;

		// Move to next SnakeBody
		currentSnakeBody = currentSnakeBody->next;
	}
}