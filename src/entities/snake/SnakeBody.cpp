#include "SnakeBody.h"


SnakeBody::SnakeBody(double row, double col, double speed, Direction headingDirection, SnakeBody* prev, SnakeBody* next) :
    MovingEntity(row, col, speed, headingDirection) , prev(prev), next(next){
    this->setRect(col,row,10,10);
}


SnakeBody::~SnakeBody() {}

SnakeBody* SnakeBody::get_prev() const {
	return prev;
}

SnakeBody* SnakeBody::get_next() const {
	return next;
}

void SnakeBody::remove_tail() {
	if (next->next != nullptr)
		next->remove_tail();
	delete next;
	next = nullptr;
}
