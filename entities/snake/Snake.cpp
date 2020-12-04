#include <iostream>
#include <deque>

#include <entities/Entity.h>
#include <entities/snake/Snake.h>

const QString Snake::image_lookup[4][4] {
	{
		":/assets/sprite/snake-head-up.png",
		":/assets/sprite/snake-head-down.png",
		":/assets/sprite/snake-head-left.png",
		":/assets/sprite/snake-head-right.png",
	},
	{
		":/assets/sprite/snake-body-vertical.png",
		":/assets/sprite/snake-body-horizontal.png",
	},
	{
		":/assets/sprite/snake-corner-up-left.png",
		":/assets/sprite/snake-corner-up-right.png",
		":/assets/sprite/snake-corner-down-left.png",
		":/assets/sprite/snake-corner-down-right.png",
	},
	{
		":/assets/sprite/snake-tail-up.png",
		":/assets/sprite/snake-tail-down.png",
		":/assets/sprite/snake-tail-left.png",
		":/assets/sprite/snake-tail-right.png",
	}
};

Snake::Snake(int row, int col, int given_init_speed, Direction headingDirection, int max_health, int length) :
		SnakeBody(row, col, given_init_speed, headingDirection), GIVEN_INIT_SPEED(given_init_speed),
		max_health(max_health), health(max_health), num_fruits_eaten(0),
		pu_activate(nullptr)
{
	if (length < 0)
		this->length = INIT_LENGTH;
	else if (length > MAX_LENGTH)
		this->length = MAX_LENGTH;
	else
		this->length = length;

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
	// Delete the whole snake
    SnakeBody* currentSnakeBody = this->next;
    SnakeBody* nextSnakeBody = nullptr;
    while (currentSnakeBody != nullptr) {
        nextSnakeBody = currentSnakeBody->next;
        delete currentSnakeBody;
        currentSnakeBody = nextSnakeBody;
    }
	// Empty pu_inventpry
	for (auto it = pu_inventory.begin(); it != pu_inventory.end(); it++) {
		delete (*it);
	}
	pu_inventory.clear();
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

int Snake::get_num_fruits_eaten() const {
	return num_fruits_eaten;
}

std::deque<PowerUp*> Snake::get_pu_inventory() const {
    return pu_inventory;
}

const PowerUp* Snake::get_pu_activate() const {
	return pu_activate;
}

bool Snake::is_ghost_immunity() const {
	return ghost_immunity;
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

void Snake::set_speed(int speed) {
	if (speed < 0)
		speed = 0;
	else if (speed > MAX_SPEED)
		speed = MAX_SPEED;

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
	newSpeed = num_fruits_eaten / 5 + GIVEN_INIT_SPEED;

	// New speed should not exceed the maximum allowed speed
	if (newSpeed > MAX_SPEED)
		newSpeed = MAX_SPEED;

    return newSpeed;
}

void Snake::increase_length(int len) {
	if (len <= 0) {
		return;
	}

	if ((length + len) > MAX_LENGTH) {
		return;
	}

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

void Snake::increase_num_fruits_eaten(int num) {
	num_fruits_eaten += num;
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


// TODO
void Snake::usePU() {
    // If no power up to use or already activated a power up , ignored
    if (pu_inventory.empty() || pu_activate != nullptr)
        return;
    
    PowerUp* pu = pu_inventory.front();
    pu_inventory.pop_front();
	pu->activate(this);
	qDebug() << "Snake activated: " << static_cast<int>(pu->get_type());
}
