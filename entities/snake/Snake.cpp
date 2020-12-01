#include <iostream>
#include <deque>

#include <entities/Entity.h>
#include <entities/snake/Snake.h>

Snake::Snake(int row, int col, int speed, Direction headingDirection, int max_health, int length) :
        SnakeBody(row, col, speed, headingDirection),
        max_health(max_health), health(max_health), length(length), fruits_eaten(0),
		pu_activate(nullptr)
{
    // Initialise SnakeBody by creating a linked list
    int temp_row = row;
    int temp_col = col;
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

std::deque<PowerUp*> Snake::get_pu_inventory() const {
    return pu_inventory;
}

const PowerUp* Snake::get_pu_activate() const {
	return pu_activate;
}

void Snake::set_headingDirection(Direction headingDirection) {
    // Avoid setting the headingDirection the opposite of the current headingDirection
	if ((this->headingDirection == Direction::NORTH && headingDirection == Direction::SOUTH)	||
		(this->headingDirection == Direction::EAST && headingDirection == Direction::WEST)		||
		(this->headingDirection == Direction::SOUTH && headingDirection == Direction::NORTH)	||
		(this->headingDirection == Direction::WEST && headingDirection == Direction::EAST))
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

void Snake::set_pu_activate(PowerUp* powerUp) {
	pu_activate = powerUp;
}

void Snake::set_ghost_immunity(bool state) {
	ghost_immunity = state;
}

void Snake::move_forward() {
	for (int i = 0; i < speed; i++){
		move_forward_one_unit();
	}
}

void Snake::set_speed(int speed) {
    if (speed < 0)
        return;

    SnakeBody* currentSnakeBody = this;
    while (currentSnakeBody != nullptr) {
        currentSnakeBody->speed = speed;

        // Move to next SnakeBody
        currentSnakeBody = currentSnakeBody->next;
    }
}

int Snake::calculate_level_speed() const {
    // In case some power up affect the speed calculation, return the current value
    if (pu_activate != nullptr)
        return speed;

    int newSpeed;
    // TODO: Change an appropriate value (/ 10?)
    newSpeed = fruits_eaten / 10 + INIT_SPEED;
    return newSpeed;
}

void Snake::increase_length(int len) {
    if (len <= 0)
        return;

    // Search for end of  SnakeBody (index = length - 1)
    SnakeBody* endSnakeBody = this;
    while (endSnakeBody->next != nullptr) {
        endSnakeBody = endSnakeBody->next;
    }

    int temp_row = endSnakeBody->row;
    int temp_col = endSnakeBody->col;
    SnakeBody* prevSnakeBody = endSnakeBody;
    for (int i = 0; i < len; i++) {
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
    this->length += len;
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

void Snake::addPUToInventory(PowerUp* powerUp) {
    // Push the power up as the last element of the queue
    pu_inventory.push_back(powerUp);
    // If the inventory, remove the first element in queue
    if (pu_inventory.size() > MAX_PU) {
        pu_inventory.pop_front();
    }
}

QPixmap Snake::get_pixmap() {
    return QPixmap(":/assets/snake-head.png");
}

// TODO
void Snake::usePU() {
    // If no power up to use or already activated a power up , ignored
    if (pu_inventory.empty() || pu_activate != nullptr)
        return;
    
    PowerUp* pu = pu_inventory.front();
    pu_inventory.pop_front();
	pu->activate(this);
	// emit signal to wait for deactivate (time out)
}

void Snake::move_forward_one_unit() {
	SnakeBody* currentSnakeBody = this;
	Direction currentHeadingDirection, prevHeadingDirection;
	while (currentSnakeBody != nullptr) {
		// As the speed of the snake might change, so each SnakeBody moves according to its current speed instead of last SnakeBody's coordinate
		switch(currentSnakeBody->headingDirection) {
			case Direction::NORTH:	currentSnakeBody->set_relative_coordinate(-1, 0);	break;
			case Direction::EAST:	currentSnakeBody->set_relative_coordinate(0, 1);	break;
			case Direction::SOUTH:	currentSnakeBody->set_relative_coordinate(1, 0);	break;
			case Direction::WEST:	currentSnakeBody->set_relative_coordinate(0, -1);	break;
		}
		
		currentHeadingDirection = currentSnakeBody->headingDirection;
		// Change headingDirection according to the last snakeBody
		if (currentSnakeBody->prev != nullptr) {
			currentSnakeBody->headingDirection = prevHeadingDirection;
		}
		prevHeadingDirection = currentHeadingDirection;
		
		// Move to next SnakeBody
		currentSnakeBody = currentSnakeBody->next;
	}
}
