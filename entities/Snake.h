#ifndef SNAKE_H_
#define SNAKE_H_

#include "../entities/SnakeBody.h"
#include "../fruits_and_powerUps/PowerUp.h"

class Snake {
public:
	enum class Direction {NORTH, EAST, SOUTH, WEST};
	static const int INIT_HEALTH = 3;
	static const int INIT_LENGTH = 3;
	static double INIT_SPEED;
	
	static const int MAX_PU = 3;

	Snake();
	~Snake();
	
	int get_max_health() const;
	int get_health() const;
	int get_length() const;
	double get_speed() const;

	SnakeBody* get_head() const;
	Direction get_headingDirection() const;

	PowerUp::PowerUpType get_pu_inventory(int) const;
	PowerUp::PowerUpType get_pu_active() const;

private:
	int max_health {INIT_HEALTH};
	int health {INIT_HEALTH};
	int length {INIT_LENGTH};
	double speed {INIT_SPEED};

	SnakeBody* head;
	Direction headingDirection {Direction::NORTH};

	// Power Up (PU)
	PowerUp::PowerUpType pu_inventory[MAX_PU] {PowerUp::PowerUpType::NONE};
	PowerUp::PowerUpType pu_active {PowerUp::PowerUpType::NONE};
};

double Snake::INIT_SPEED = 1.0;

#endif /* SNAKE_H_ */