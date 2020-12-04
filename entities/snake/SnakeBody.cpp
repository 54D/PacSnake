#include "SnakeBody.h"
#include "game_view.h"

/* PUBLIC */

SnakeBody* SnakeBody::get_prev() const {
    return prev;
}

SnakeBody* SnakeBody::get_next() const {
    return next;
}

void SnakeBody::refresh_pixmap(){
    int pic_ref = -1;
    if (this->get_prev() == nullptr) pic_ref = 0;
    if (this->get_next() == nullptr) pic_ref = 3;
    if (this->get_prev() != nullptr && this->get_next() != nullptr){
        if (this->get_next()->get_headingDirection()!= this->get_headingDirection()) pic_ref = 2;
    }
    if (pic_ref == -1) pic_ref = 1;
    int curr_dir = -1;
    if (this->get_headingDirection() == Direction::NORTH) curr_dir = 0;
    if (this->get_headingDirection() == Direction::SOUTH) curr_dir = 1;
    if (this->get_headingDirection() == Direction::WEST) curr_dir = 2;
    if (this->get_headingDirection() == Direction::EAST) curr_dir = 3;

    if (pic_ref == 1){
        if (curr_dir == 0 || curr_dir == 1){
            QPixmap pic(game_view::image_lookup[1][0]);
            this->get_pixmap()->setPixmap(pic);
        }else{
            QPixmap pic(game_view::image_lookup[1][1]);
            this->get_pixmap()->setPixmap(pic);
        }
    }else if (pic_ref == 2){
        int dir = -1;
        if (this->get_headingDirection() == Direction::EAST && this->get_next()->get_headingDirection() == Direction::NORTH) dir = 3;
        if (this->get_headingDirection() == Direction::EAST && this->get_next()->get_headingDirection() == Direction::SOUTH) dir = 1;
        if (this->get_headingDirection() == Direction::WEST && this->get_next()->get_headingDirection() == Direction::NORTH) dir = 2;
        if (this->get_headingDirection() == Direction::WEST && this->get_next()->get_headingDirection() == Direction::SOUTH) dir = 0;
        if (this->get_headingDirection() == Direction::NORTH && this->get_next()->get_headingDirection() == Direction::EAST) dir = 0;
        if (this->get_headingDirection() == Direction::NORTH && this->get_next()->get_headingDirection() == Direction::WEST) dir = 1;
        if (this->get_headingDirection() == Direction::SOUTH && this->get_next()->get_headingDirection() == Direction::EAST) dir = 2;
        if (this->get_headingDirection() == Direction::SOUTH && this->get_next()->get_headingDirection() == Direction::WEST) dir = 3;
        QPixmap pic(game_view::image_lookup[pic_ref][dir]);
        this->get_pixmap()->setPixmap(pic);
    }else{
        QPixmap pic(game_view::image_lookup[pic_ref][curr_dir]);
        this->get_pixmap()->setPixmap(pic);
    }
    return;
}

/* PROTECTED */

SnakeBody::SnakeBody(int row, int col, int speed, Direction headingDirection, SnakeBody* prev, SnakeBody* next)
	: MovingEntity(row, col, speed, headingDirection) , prev(prev), next(next) {
}

SnakeBody::~SnakeBody() {}

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
