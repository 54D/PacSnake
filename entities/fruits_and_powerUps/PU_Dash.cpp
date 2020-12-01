#include <iostream>
#include "PowerUp.h"
#include "PU_Dash.h"

PU_Dash::PU_Dash(int row, int col) :
	PowerUp(row, col, PowerUp::PowerUpType::DASH) {}
	
PU_Dash::~PU_Dash() {}

PowerUp::PowerUpType PU_Dash::get_type() const {
	return type;
}

void PU_Dash::activate(Snake* snake) {
    // Only one power up can be activated at the same time 
    if (snake->get_pu_activate() != nullptr)
        return;

    // TODO
    int newSpeed= snake->get_speed() * 2;
    snake->set_speed(newSpeed);
    snake->set_pu_activate(this);
}

void PU_Dash::deactivate(Snake* snake) {
    if (snake->get_pu_activate() == nullptr)
        return;
    // Reset speed
    snake->set_pu_activate(nullptr);
    int newSpeed = snake->calculate_level_speed();
    snake->set_speed(newSpeed);
}