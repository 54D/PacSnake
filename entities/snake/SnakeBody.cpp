#include "SnakeBody.h"

SnakeBody::SnakeBody(double row, double col, double speed, Direction headingDirection, SnakeBody* prev, SnakeBody* next) :
        MovingEntity(row, col, speed, headingDirection) , prev(prev), next(next) {}

SnakeBody::~SnakeBody() {}

const SnakeBody* SnakeBody::get_prev() const {
    return prev;
}

const SnakeBody* SnakeBody::get_next() const {
    return next;
}

void SnakeBody::remove_tail() {
    if (next->next != nullptr)
        next->remove_tail();
    delete next;
    next = nullptr;
}