#ifndef SNAKE_H_
#define SNAKE_H_

#include <queue>
#include "SnakeBody.h"
#include "src/entities/fruits_and_powerUps/PowerUp.h"

// The "head / brain" of the snake, consider as a moving entity of snake as well
class Snake : public SnakeBody {	
public:
	static const int INIT_HEALTH = 3;
	static const int INIT_LENGTH = 3;
	static double INIT_SPEED;
	static const int MAX_PU = 3;

	Snake(double row, double col, double speed = INIT_SPEED, Direction headingDirection = Direction::NORTH, int max_health = INIT_HEALTH, int length = INIT_LENGTH);
	virtual ~Snake();

	int get_max_health() const;
	int get_health() const;
	int get_length() const;

	//std::queue<PowerUp::PowerUpType>::const_iterator get_pu_inventory_begin() const;
	//std::queue<int>::iterator x;

	virtual void set_headingDirection(Direction headingDirection); 
	void set_health(int health);
	void set_relative_health(int delta_health);

	// The WHOLE snake will move forward base on its speed and each parts' headingDirection 
	void move_forward();
	virtual void set_speed(double speed);

	// Increase / Decrease the length of the Snake
	// Increase the length of Snake by length at the end of Snake
	void increase_length(int length);

	// Remove the tail of Snake after the index
	// index = 0 is Snake ("head / brain" of the snake)
	// index = 1 is the first snakeBody after Snake
	// index = length - 1 is the last SankeBody
	void remove_tail(int index);
	void remove_tail(SnakeBody* snakeBody);

	void addPUToInventory(PowerUp::PowerUpType& powerUp);
	void usePU();

private:
	int max_health {INIT_HEALTH};
	int health {INIT_HEALTH};
	int length {INIT_LENGTH};

	// Power Up (PU)
	std::queue<PowerUp::PowerUpType> pu_inventory;
	PowerUp::PowerUpType pu_active {PowerUp::PowerUpType::NONE};
};

#endif /* SNAKE_H_ */