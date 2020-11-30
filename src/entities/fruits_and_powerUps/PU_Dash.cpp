#include "PowerUp.h"
#include "PU_Dash.h"

PU_Dash::PU_Dash(double row, double col) : PowerUp(row, col) {}
PU_Dash::~PU_Dash() {}

void PU_Dash::activate(Snake& snake) {
    // Only one power up can be activated at the same time 
    if (snake.get_pu_active() != PowerUp::PowerUpType::NONE)
        return;

    // TODO
    double newSpeed= snake.get_speed() * 2.0;
    snake.set_speed(newSpeed);
    snake.set_pu_active(PowerUp::PowerUpType::DASH);
}

void PU_Dash::deactivate(Snake& snake) {
    if (snake.get_pu_active() != PowerUp::PowerUpType::DASH)
        return;

    // Reset speed
    snake.set_pu_active(PowerUp::PowerUpType::NONE);
    double newSpeed = snake.calculate_level_speed();
    snake.set_speed(newSpeed);
}