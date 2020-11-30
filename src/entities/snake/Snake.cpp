#include <iostream>
#include <deque>
#include "src/entities/Entity.h"
#include "Snake.h"

double Snake::INIT_SPEED = 1.0;

Snake::Snake(double row, double col, double speed, Direction headingDirection, int max_health, int length) :
	SnakeBody(row, col, speed, headingDirection), 
	max_health(max_health), health(max_health), length(length), 
	pu_active(PowerUp::PowerUpType::NONE)
	{
	// Inialise pu_inventory
	for (int i = 0; i < MAX_PU; i++)
		pu_inventory.push_back(PowerUp::PowerUpType::NONE);

	// Initialise SnakeBody by creating a linked list
	double temp_row = row;
	double temp_col = col;
	SnakeBody* prevSnakeBody = this;
	for (int i = 0; i < length; i++) {
		switch (headingDirection) {
			case Direction::NORTH: 	temp_row += 1.0;	break;
			case Direction::EAST:	temp_col -= 1.0;	break;
			case Direction::SOUTH:	temp_row -= 1.0;	break;
			case Direction::WEST:	temp_col += 1.0;	break;
		}
		SnakeBody* currentSnakeBody = new SnakeBody {temp_row, temp_col, speed, headingDirection};
		prevSnakeBody->next = currentSnakeBody;
		currentSnakeBody->prev = prevSnakeBody;
		prevSnakeBody = currentSnakeBody;
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

std::deque<PowerUp::PowerUpType> Snake::get_pu_inventory() const {
	return pu_inventory;
}

PowerUp::PowerUpType Snake::get_pu_active() const {
	return pu_active;
}

void Snake::set_headingDirection(Direction headingDirection) {
	// Avoid setting the headingDirection the opposite of the current headingDirection
	if (this->headingDirection == Direction::NORTH && headingDirection == Direction::SOUTH ||
		this->headingDirection == Direction::EAST && headingDirection == Direction::WEST ||
		this->headingDirection == Direction::SOUTH && headingDirection == Direction::NORTH ||
		this->headingDirection == Direction::WEST && headingDirection == Direction::EAST)
		return;
	else
		this->headingDirection = headingDirection;
}

void Snake::set_health(int health) {
	// If the input is out-of-bound, make it to 0 or max_health
	if (health < 0) {
		this->health = 0;
		return;
	}
	else if (health > max_health) {
		this->health = max_health;
	}
	else
		this->health = health;
}

void Snake::set_relative_health(int delta_health) {
	// If the input is out-of-bound, make it to 0 or max_health
	if ((health + delta_health) < 0) {
		health = 0;
		return;
	}
	else if ((health + delta_health) > max_health) {
		health = max_health;
	}
	else
		health = health + delta_health;
}

void Snake::set_pu_active(PowerUp::PowerUpType powerUp) {
	pu_active = powerUp;
}

void Snake::move_forward() {
	SnakeBody* currentSnakeBody = this;
	Direction currentHeadingDirection, prevHeadingDirection;
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
			currentSnakeBody->headingDirection = prevHeadingDirection;
		}
		prevHeadingDirection = currentHeadingDirection;
		
		// Move to next SnakeBody
		currentSnakeBody = currentSnakeBody->next;
	}
}

void Snake::set_speed(double speed) {
	if (speed < 0.0)
		return;

	SnakeBody* currentSnakeBody = this;
	while (currentSnakeBody != nullptr) {
		currentSnakeBody->speed = speed;

		// Move to next SnakeBody
		currentSnakeBody = currentSnakeBody->next;
	}
}

double Snake::calculate_level_speed() const {
	// In case some power up affect the speed calculation, return the current value
	if (pu_active != PowerUp::PowerUpType::NONE)
		return speed;

	double newSpeed;
	// TODO: Change an appropraite value 
	newSpeed = speed * static_cast<double>(fruits_eaten) / 10;
	return newSpeed;
}

void Snake::increase_length(int length) {
	if (length <= 0)
		return;
	
	// Search for end of  SnakeBody (index = length - 1)
	SnakeBody* endSnakeBody = this;
	while (endSnakeBody->next != nullptr) {
		endSnakeBody = endSnakeBody->next;
	}
	
	double temp_row = endSnakeBody->row;
	double temp_col = endSnakeBody->col;
	SnakeBody* prevSnakeBody = endSnakeBody;
	for (int i = 0; i < length; i++) {
		switch (prevSnakeBody->headingDirection) {
			case Direction::NORTH: 	temp_row += 1.0;	break;
			case Direction::EAST:	temp_col -= 1.0;	break;
			case Direction::SOUTH:	temp_row -= 1.0;	break;
			case Direction::WEST:	temp_col += 1.0;	break;
		}
		SnakeBody* currentSnakeBody = new SnakeBody {temp_row, temp_col, speed, prevSnakeBody->headingDirection};
		prevSnakeBody->next = currentSnakeBody;
		currentSnakeBody->prev = prevSnakeBody;
		prevSnakeBody = currentSnakeBody;
	}

	// Increase length to Snake
	this->length += length;
}

void Snake::remove_tail(int index) {
	if (index < 0 || index >= length)
		return;

	SnakeBody* currentSnakeBody = this;
	for (int i = 0; i < index; i++) {
		currentSnakeBody = currentSnakeBody->next;
	}
	currentSnakeBody->remove_tail();
	
	// Update length
	currentSnakeBody = this;
	int count = 0;
	do {
		count++;
		currentSnakeBody = currentSnakeBody->next;
	} while (currentSnakeBody != nullptr);
	length = count;
}

void Snake::remove_tail(SnakeBody* snakeBody) {
	snakeBody->remove_tail();
	
	// Update length
	SnakeBody* currentSnakeBody = this;
	int count = 0;
	do {
		count++;
		currentSnakeBody = currentSnakeBody->next;
	} while (currentSnakeBody != nullptr);
	length = count;
}

void Snake::addPUToInventory(PowerUp::PowerUpType& powerUp) {
	// Push the power up as the last element of the queue
	pu_inventory.push_back(powerUp);
	// If the inventory, remove the first element in queue
	if (pu_inventory.size() > MAX_PU) {
		pu_inventory.pop_front();
	}
}

// TODO
void Snake::usePU() {
	// If no power up to use, ignore
	if (pu_inventory.size() == 0)
		return;
	
	// Get the type of power up
	PowerUp::PowerUpType puType = pu_inventory.front();
	pu_inventory.pop_front();

	// Case switch or use function poiter to call the coreesponding powerup use function
	switch (puType) {

	}
}