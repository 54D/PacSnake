#include "SnakeBody.h"

SnakeBody::~SnakeBody() {}

const SnakeBody* SnakeBody::get_prev() const {
    return prev;
}

const SnakeBody* SnakeBody::get_next() const {
    return next;
}

SnakeBody::SnakeBody(int row, int col, int speed, Direction headingDirection, SnakeBody* prev, SnakeBody* next) :
MovingEntity(row, col, speed, headingDirection) , prev(prev), next(next) {
    //this->pixmap = QPixmap(":/assets/image");
}

void SnakeBody::move_forward() {
	switch(headingDirection) {
		case Direction::NORTH:	set_relative_coordinate(-1, 0);	break;
		case Direction::EAST:	set_relative_coordinate(0, 1);	break;
		case Direction::SOUTH:	set_relative_coordinate(1, 0);	break;
		case Direction::WEST:	set_relative_coordinate(0, -1);	break;
	}
}

void SnakeBody::remove_tail() {
    if (next->next != nullptr)
        next->remove_tail();
    delete next;
    next = nullptr;
}

QPixmap SnakeBody::get_pixmap() {
    if(prev==nullptr)return QPixmap(":/assets/snake-head.png");
    if(next==nullptr)return QPixmap(":/assets/snake-tail.png");
    if(prev->headingDirection!=next->headingDirection)return QPixmap(":/assets/snake-corner.png");
    return QPixmap(":/assets/snake-straight.png");
}
