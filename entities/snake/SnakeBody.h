#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_

#include <entities/MovingEntity.h>

class SnakeBody : public MovingEntity {
public:

	friend class Snake;

	/**
	 * Obtains the previous linked SnakeBody.
	 * @return	prev	Previous linked SnakeBody. `nullptr` if head.
	 */
	SnakeBody* get_prev() const;
	/**
	 * Obtains the next linked SnakeBody.
	 * @return	next	Next linked SnakeBody. `nullptr` if tail.
	 */
    SnakeBody* get_next() const;
	/**
	 * Refreshes the pixmap representation of SnakeBody.
	 * Called to update the orientation and corner positioning upon snake movement.
	 */
    void refresh_pixmap();

protected:

	/**
	 * Constructor for SnakeBody.
	 * @param	row					Initial row location.
	 * @param	col					Initial column location.
	 * @param	speed				Initial speed.
	 * @param	headingDirection	Initial heading direction.
	 * @param	prev				Previous SnakeBody.
	 * @param	next				Next SnakeBody.
	 */
	SnakeBody(int row, int col, int speed, Direction headingDirection = Direction::NORTH, SnakeBody* prev = nullptr, SnakeBody* next = nullptr);

	/**
	 * Destructor for SnakeBody.
	 */
	virtual ~SnakeBody();

	/**
	 * Moves this MovingEntity by 1 unit, direction specified by `headingDirection`.
	 */
	virtual void move_forward() override;
	/**
	 * Recursively removes all SnakeBody following this one.
	 * This does not update the Snake length, which must be processed from a Snake object.
	 */
	void remove_tail();
    
    SnakeBody* prev {nullptr};
    SnakeBody* next {nullptr};

};

#endif /* SNAKEBODY_H_ */
