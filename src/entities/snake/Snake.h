#ifndef SNAKE_H_
#define SNAKE_H_

#include <list>
#include "SnakeBody.h"
#include "../fruits_and_powerUps/PowerUp.h"

// The "brain" of the snake, consider as a moving entity of snake as well
class Snake : public SnakeBody {	
public:
	static const int INIT_HEALTH = 3;
	static const int INIT_LENGTH = 3;
	static double INIT_SPEED;
	static const int MAX_PU = 3;

	Snake(double row, double col, double speed = INIT_SPEED, Direction headingDirection = Direction::NORTH);
	virtual ~Snake();

	int get_max_health() const;
	int get_health() const;
	int get_length() const;

	virtual void set_headingDirection(Direction headingDirection);

	// The WHOLE snake will move forward base on its speed and each parts' headingDirection 
	void move_forward();
	virtual void set_speed(double speed);

	// TODO
	void remove_tail(int index);
	void remove_tail(SnakeBody* index);

private:
	int max_health {INIT_HEALTH};
	int health {INIT_HEALTH};
	int length {INIT_LENGTH};

	// Power Up (PU)
	std::list<PowerUp::PowerUpType> pu_inventory {MAX_PU, PowerUp::PowerUpType::NONE};
	PowerUp::PowerUpType pu_active {PowerUp::PowerUpType::NONE};
};

#endif /* SNAKE_H_ */