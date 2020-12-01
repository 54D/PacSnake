#include <iostream>
#include "PowerUp.h"
#include "PU_Dash.h"

PU_Dash::PU_Dash(double row, double col) :
	PowerUp(row, col, PowerUp::PowerUpType::DASH) {}
	
PU_Dash::~PU_Dash() {}

void PU_Dash::activate(Snake* snake) {
    // Only one power up can be activated at the same time 
    if (snake->get_pu_activate() != nullptr)
        return;

    // TODO
    double newSpeed= snake->get_speed() * 2.0;
    snake->set_speed(newSpeed);
    snake->set_pu_activate(this);
}

void PU_Dash::deactivate(Snake* snake) {
    if (snake->get_pu_activate() == nullptr)
        return;
    // Reset speed
    snake->set_pu_activate(nullptr);
    double newSpeed = snake->calculate_level_speed();
    snake->set_speed(newSpeed);
}

PowerUp::PowerUpType PU_Dash::get_type() const {
	return type;
}