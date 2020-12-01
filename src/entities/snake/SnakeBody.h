#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_
#include <QGraphicsRectItem>
#include "../MovingEntity.h"

class SnakeBody : public MovingEntity, public QGraphicsRectItem {
public:
	friend class Snake;
	SnakeBody(double row, double col, double speed, Direction headingDirection = Direction::NORTH, SnakeBody* prev = nullptr, SnakeBody* next = nullptr);
	virtual ~SnakeBody();

    SnakeBody* get_prev() const;
    SnakeBody* get_next() const;

protected:
	// Remove all the SnakeBody after this SnakeBody
	void remove_tail();

private:
	SnakeBody* prev {nullptr};
	SnakeBody* next {nullptr};
};

#endif /* SNAKEBODY_H_ */
