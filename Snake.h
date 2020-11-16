#ifndef SNAKE_H_
#define SNAKE_H_

#include "SnakeBody.h"

class Snake {
public:
	enum class PowerUpType {NONE, DASH, SHIELD, INVISIBLE};
	static const int INIT_HEALTH = 3;
	static const int INIT_LENGTH = 3;
	static double INIT_SPEED;

	Snake();
	~Snake();

private:
	int max_health {INIT_HEALTH};
	int health {INIT_HEALTH};
	int length {INIT_LENGTH};
	double speed {INIT_SPEED};

	int num_of_fruit {0};

	SnakeBody* head;

	PowerUpType pu_inventory {Snake::PowerUpType::NONE};
	PowerUpType pu_active {Snake::PowerUpType::NONE};
};

double Snake::INIT_SPEED = 1.0;

#endif /* SNAKE_H_ */