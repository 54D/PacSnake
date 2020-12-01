#ifndef SNAKE_H_
#define SNAKE_H_

#include <deque>

#include "SnakeBody.h"
#include <entities/fruits_and_powerUps/PowerUp.h>

// The "head / brain" of the snake, consider as a moving entity of snake as well
class Snake final : public SnakeBody {
public:
    static const int INIT_HEALTH = 3;
    static const int INIT_LENGTH = 3;
    static const int INIT_SPEED = 1;
    static const int MAX_PU = 3;

    Snake(int row, int col, int speed = INIT_SPEED, Direction headingDirection = Direction::NORTH, int max_health = INIT_HEALTH, int length = INIT_LENGTH);
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
	void set_ghost_immunity(bool state);

    // The WHOLE snake will move forward base on its speed and each parts' headingDirection
    virtual void move_forward() override;
    virtual void set_speed(int speed) override;
    // Calculate the speed of the snake according to the number of fruits eaten
    // Should be executed whenever a fruit is eaten
    int calculate_level_speed() const;

    // Increase / Decrease the length of the Snake
    // Increase the length of Snake by length at the end of Snake
    void increase_length(int len);

    // Remove the tail of Snake after the index
    // index = 0 is Snake ("head / brain" of the snake)
    // index = 1 is the first snakeBody after Snake
    // index = length - 1 is the last SnakeBody
	void remove_tail(int index);
    void remove_tail(SnakeBody* snakeBody);

    void addPUToInventory(PowerUp* powerUp);
    void usePU();

protected:
    virtual QPixmap get_pixmap() override;

private:
	void move_forward_one_unit();
	
    int max_health {INIT_HEALTH};
    int health {INIT_HEALTH};
    int length {INIT_LENGTH};
    int fruits_eaten {0};

	bool ghost_immunity {false};

    // Power Up (PU)
    std::deque<PowerUp*> pu_inventory;
    PowerUp* pu_activate {nullptr};
};

#endif /* SNAKE_H_ */
