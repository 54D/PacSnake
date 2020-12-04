#include "SnakeBody.h"
#include "game_view.h"

/* PUBLIC */
const QString SnakeBody::image_lookup[4][4][4] {
	{	// No power up
		{
			":/assets/sprite/snake-head-up.png",
			":/assets/sprite/snake-head-down.png",
			":/assets/sprite/snake-head-left.png",
			":/assets/sprite/snake-head-right.png",
		},
		{
			":/assets/sprite/snake-body-vertical.png",
			":/assets/sprite/snake-body-horizontal.png",
		},
		{
			":/assets/sprite/snake-corner-up-left.png",
			":/assets/sprite/snake-corner-up-right.png",
			":/assets/sprite/snake-corner-down-left.png",
			":/assets/sprite/snake-corner-down-right.png",
		},
		{
			":/assets/sprite/snake-tail-up.png",
			":/assets/sprite/snake-tail-down.png",
			":/assets/sprite/snake-tail-left.png",
			":/assets/sprite/snake-tail-right.png",
		}
	},
	{	// Dash power Up
		{
			":/assets/sprite/snake-head-up-dashing.png",
			":/assets/sprite/snake-head-down-dashing.png",
			":/assets/sprite/snake-head-left-dashing.png",
			":/assets/sprite/snake-head-right-dashing.png",
		},
		{
			":/assets/sprite/snake-body-vertical-dashing.png",
			":/assets/sprite/snake-body-horizontal-dashing.png",
		},
		{
			":/assets/sprite/snake-corner-up-left-dashing.png",
			":/assets/sprite/snake-corner-up-right-dashing.png",
			":/assets/sprite/snake-corner-down-left-dashing.png",
			":/assets/sprite/snake-corner-down-right-dashing.png",
		},
		{
			":/assets/sprite/snake-tail-up-dashing.png",
			":/assets/sprite/snake-tail-down-dashing.png",
			":/assets/sprite/snake-tail-left-dashing.png",
			":/assets/sprite/snake-tail-right-dashing.png",
		}
	},
	{	// Heal power Up
		{
			":/assets/sprite/snake-head-up-healing.png",
			":/assets/sprite/snake-head-down-healing.png",
			":/assets/sprite/snake-head-left-healing.png",
			":/assets/sprite/snake-head-right-healing.png",
		},
		{
			":/assets/sprite/snake-body-vertical-healing.png",
			":/assets/sprite/snake-body-horizontal-healing.png",
		},
		{
			":/assets/sprite/snake-corner-up-left-healing.png",
			":/assets/sprite/snake-corner-up-right-healing.png",
			":/assets/sprite/snake-corner-down-left-healing.png",
			":/assets/sprite/snake-corner-down-right-healing.png",
		},
		{
			":/assets/sprite/snake-tail-up-healing.png",
			":/assets/sprite/snake-tail-down-healing.png",
			":/assets/sprite/snake-tail-left-healing.png",
			":/assets/sprite/snake-tail-right-healing.png",
		}
	},
	{	// Shield power Up
		{
			":/assets/sprite/snake-head-up-shielding.png",
			":/assets/sprite/snake-head-down-shielding.png",
			":/assets/sprite/snake-head-left-shielding.png",
			":/assets/sprite/snake-head-right-shielding.png",
		},
		{
			":/assets/sprite/snake-body-vertical-shielding.png",
			":/assets/sprite/snake-body-horizontal-shielding.png",
		},
		{
			":/assets/sprite/snake-corner-up-left-shielding.png",
			":/assets/sprite/snake-corner-up-right-shielding.png",
			":/assets/sprite/snake-corner-down-left-shielding.png",
			":/assets/sprite/snake-corner-down-right-shielding.png",
		},
		{
			":/assets/sprite/snake-tail-up-shielding.png",
			":/assets/sprite/snake-tail-down-shielding.png",
			":/assets/sprite/snake-tail-left-shielding.png",
			":/assets/sprite/snake-tail-right-shielding.png",
		}
	}
};


SnakeBody* SnakeBody::get_prev() const {
	return prev;
}

SnakeBody* SnakeBody::get_next() const {
	return next;
}

void SnakeBody::refresh_pixmap(){
	int currentPUState = static_cast<int>(current_powerUpState);
	int pic_ref = -1;
	if (this->get_next() == nullptr) pic_ref = 3;
	if (this->get_prev() == nullptr) pic_ref = 0;
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
			QPixmap pic(SnakeBody::image_lookup[currentPUState][1][0]);
			this->get_pixmap()->setPixmap(pic);
		}else{
			QPixmap pic(SnakeBody::image_lookup[currentPUState][1][1]);
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
		QPixmap pic(SnakeBody::image_lookup[currentPUState][pic_ref][dir]);
		this->get_pixmap()->setPixmap(pic);
	}else{
		QPixmap pic(SnakeBody::image_lookup[currentPUState][pic_ref][curr_dir]);
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
