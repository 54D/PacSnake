#include "PowerUp.h"

PowerUp::~PowerUp () {}

PowerUp::PowerUp(double row, double col, PowerUp::PowerUpType type) :
	Entity(row, col), type(type) {}