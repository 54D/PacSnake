#include "PowerUp.h"

PowerUp::~PowerUp () {}

PowerUp::PowerUpType PowerUp::get_type() const {
	return type;
}

PowerUp::PowerUp(int row, int col, PowerUp::PowerUpType type) :
	Entity(row, col), type(type) {}
