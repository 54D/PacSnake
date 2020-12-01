#include "SnakeBody.h"

SnakeBody::~SnakeBody() {}

const SnakeBody* SnakeBody::get_prev() const {
    return prev;
}

const SnakeBody* SnakeBody::get_next() const {
    return next;
}

SnakeBody::SnakeBody(int row, int col, int speed, Direction headingDirection, SnakeBody* prev, SnakeBody* next) :
MovingEntity(row, col, speed, headingDirection) , prev(prev), next(next) {}

void SnakeBody::remove_tail() {
    if (next->next != nullptr)
        next->remove_tail();
    delete next;
    next = nullptr;
}
