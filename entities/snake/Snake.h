#ifndef SNAKE_H_
#define SNAKE_H_

#include <deque>

#include "SnakeBody.h"
#include <entities/fruits_and_powerUps/PowerUp.h>

// The "head / brain" of the snake, consider as a moving entity of snake as well
class Snake final : public SnakeBody {
    Q_OBJECT

public:

    static const int INIT_HEALTH = 3;
    static const int INIT_LENGTH = 3;
	static const int INIT_SPEED = 2;
    static const int MAX_PU = 3;
	static const int MAX_LENGTH = 50;

	/**
	 * Constructor for Snake.
	 * @param	row					Initial row location.
	 * @param	col					Initial column location.
	 * @param	given_init_speed	Initial speed.
	 * @param	headingDirection	Initial heading direction.
	 * @param	max_health			Maximum health possible.
	 * @param	length				Initial length.
	 */
	Snake(int row, int col, int given_init_speed = INIT_SPEED, Direction headingDirection = Direction::NORTH, int max_health = INIT_HEALTH, int length = INIT_LENGTH);
	/**
	 * Destructor for Snake.
	 */
	virtual ~Snake();

	/**
	 * Obtains the maximum health possible of this Snake.
	 * @return	max_health	Maximum health possible.
	 */
    int get_max_health() const;
	/**
	 * Obtains the current health of this Snake.
	 * @return	health		Current health.
	 */
    int get_health() const;
	/**
	 * Obtains the current length of this Snake.
	 * @return	length		Current length.
	 */
    int get_length() const;
	/**
	 * Obtains the number of fruits consumed by this Snake.
	 * @return	num_fruits_eaten	Number of consumed fruits.
	 */
	int get_num_fruits_eaten() const;
	/**
	 * Obtains the powerup inventory of this Snake.
	 * @return	pu_inventory	A deque containing all stored powerups.
	 */
    std::deque<PowerUp*> get_pu_inventory() const;
	/**
	 * Obtains the current activated powerup for this Snake.
	 * @return	pu_activate		Current activated powerup.
	 */
    const PowerUp* get_pu_activate() const;
	/**
	 * Checks if this Snake is immune to ghosts.
	 * @return	ghost_immunity	Ghost immunity state.
	 */
	bool is_ghost_immunity() const;
	/**
	 * Obtains the maximum length possible of this Snake.
	 * @return	longest_length	Maximum length possible.
	 */
	int get_longest_length();

	/**
	 * Sets the new heading direction of this Snake.
	 * @param	headingDirection	New heading direction.
	 */
    virtual void set_headingDirection(Direction headingDirection) override;
	/**
	 * Sets the new health of this Snake.
	 * @param	health	New health.
	 */
    void set_health(int health);
	/**
	 * Changes the health of this Snake by a relative amount.
	 * @param	delta_health	New relative health amount.
	 */
    void set_relative_health(int delta_health);
	/**
	 * Sets the activated powerup of this Snake.
	 * @param	powerUp		Activated powerup.
	 */
	void set_pu_activate(PowerUp* powerUp);
	/**
	 * Sets if this Snake is immune to ghosts.
	 * @param	state		New ghost immunity state.
	 */
	void set_ghost_immunity(bool state);
	/**
	 * Sets the maximum length possible of this Snake.
	 * @param	length		Maximum length possible.
	 */
	void set_longest_length(int length);

	/**
	 * Moves the entire Snake forward based on its speed and each part's heading direction once.
	 */
	virtual void move_forward() override;
	/**
	 * Sets the speed of this Snake.
	 * @param	speed		New speed.
	 */
	virtual void set_speed(int speed) override;
	/**
	 * Calculates the supposed speed of this Snake according to the number of fruits consumed.
	 * This is called whenever a fruit is consumed.
	 */
    int calculate_level_speed() const;

	/**
	 * Increases the length of this Snake at the end.
	 * @param	len		Length increment.
	 */
    void increase_length(int len);
	/**
	 * Increases the number of fruits consumed by this Snake.
	 * @param	num		Number of fruits increment.
	 */
	void increase_num_fruits_eaten(int num);

	/**
	 * Removes the tail of this Snake following the specified index.
	 * To remove the head of this Snake, set `index` to `0`.
	 * To remove the last SnakeBody of this Snake, set `index` to `length - 1`.
	 * @param	index	Location to start removing the tail.
	 */
	void remove_tail(int index);
	/**
	 * Removes the tail of this Snake following the specified SnakeBody.
	 * @param	snakeBody	SnakeBody to start removing the tail.
	 */
    void remove_tail(SnakeBody* snakeBody);

	/**
	 * Adds a powerup to the inventory of this Snake.
	 * @param	powerUp		Powerup to add to the inventory.
	 */
	void addPUToInventory(PowerUp* powerUp);
	/**
	 * Uses the next available powerup of this Snake.
	 */
    void usePU();
	/**
	 * Updates the powerup state of this Snake.
	 */
	void updatePowerUpState();

signals:

	/**
	 * Signal fired when a powerup has been added to the inventory.
	 */
    void powerUp_added();

private:

	const int GIVEN_INIT_SPEED;
    int max_health {INIT_HEALTH};
    int health {INIT_HEALTH};
    int length {INIT_LENGTH};
	int num_fruits_eaten {0};
    int longest_length{INIT_LENGTH};

	bool ghost_immunity {false}; // Controls whether SnakeBody will be hit by ghosts.
    // Power Up (PU)
    std::deque<PowerUp*> pu_inventory;
    PowerUp* pu_activate {nullptr};
	QMediaPlayer* no_pu_SoundEffect;
};

#endif /* SNAKE_H_ */
