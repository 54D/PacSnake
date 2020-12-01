#ifndef SNAKE_H_
#define SNAKE_H_

#include <deque>

#include "SnakeBody.h"
#include <entities/fruits_and_powerUps/PowerUp.h>

// The "head / brain" of the snake, consider as a moving entity of snake as well
class Snake : public SnakeBody {
public:
    static const int INIT_HEALTH = 3;
    static const int INIT_LENGTH = 3;
    static double INIT_SPEED;
    static const int MAX_PU = 3;

    Snake(double row, double col, double speed = INIT_SPEED, Direction headingDirection = Direction::NORTH, int max_health = INIT_HEALTH, int length = INIT_LENGTH);
    virtual ~Snake();

    int get_max_health() const;
    int get_health() const;
    int get_length() const;
    std::deque<PowerUp*> get_pu_inventory() const;
    const PowerUp* get_pu_activate() const;

    virtual void set_headingDirection(Direction headingDirection) override;
    void set_health(int health);
    void set_relative_health(int delta_health);
    void set_pu_activate(PowerUp* powerUp);

    // The WHOLE snake will move forward base on its speed and each parts' headingDirection
    void move_forward();
    virtual void set_speed(double speed) override;
    // Calculate the speed of the snake according to the number of fruits eaten
    // Should be executed whenever a fruit is eaten
    double calculate_level_speed() const;

    // Increase / Decrease the length of the Snake
    // Increase the length of Snake by length at the end of Snake
    void increase_length(int length);

    // Remove the tail of Snake after the index
    // index = 0 is Snake ("head / brain" of the snake)
    // index = 1 is the first snakeBody after Snake
    // index = length - 1 is the last SankeBody
    void remove_tail(int index);
    void remove_tail(SnakeBody* snakeBody);

    void addPUToInventory(PowerUp* powerUp);
    void usePU();

private:
    int max_health {INIT_HEALTH};
    int health {INIT_HEALTH};
    int length {INIT_LENGTH};
    int fruits_eaten {0};

    // Power Up (PU)
    std::deque<PowerUp*> pu_inventory;
    PowerUp* pu_activate {nullptr};
};

#endif /* SNAKE_H_ */