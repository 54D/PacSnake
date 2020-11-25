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
			case Direction::NORTH: 	temp_row -= 1.0;	break;
			case Direction::EAST:	temp_col -= 1.0;	break;
			case Direction::SOUTH:	temp_row += 1.0;	break;
			case Direction::WEST:	temp_col += 1.0;	break;
			default:
				std::cerr << "An unexpected error has occur at Snake construdtor (switch case)" << std::endl;
				exit(-1);
				break;
		}
		SnakeBody* currentSnakeBody = new SnakeBody {temp_row, temp_col, speed, headingDirection};
		lastSnakeBody->next = currentSnakeBody;
		currentSnakeBody->prev = lastSnakeBody;
		lastSnakeBody = currentSnakeBody;
	}
}

Snake::~Snake() {
	// TODO
	// Handle memory problem
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
