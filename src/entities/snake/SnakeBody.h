#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_

#include "../MovingEntity.h"

class SnakeBody : public MovingEntity {	
public:
	friend class Snake;
	SnakeBody(double row, double col, double speed, Direction headingDirection = Direction::NORTH, SnakeBody* prev = nullptr, SnakeBody* next = nullptr);
	virtual ~SnakeBody();

	const SnakeBody* get_prev() const;
	const SnakeBody* get_next() const;

protected:
	// Remove all the SnakeBody after this SnakeBody
	void remove_tail();

private:
	SnakeBody* prev {nullptr};
	SnakeBody* next {nullptr};
};

#endif /* SNAKEBODY_H_ */