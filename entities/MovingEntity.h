#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include <QGraphicsItem>

#include "Entity.h"

class MovingEntity : public Entity {

public:
	/**
	* Plublic const
	* @param MAX_GAMETICK_SPEED		Maximum speed allowed for Entity (with power up activated)
	* @param MAX_SPEED				Maximum speed allowed for Entity (no power up activated)
	*/
	static const int MAX_GAMETICK_SPEED = 20;
	static const int MAX_SPEED = 10;
	enum class Direction {NORTH, EAST, SOUTH, WEST};

	/**
	 * Constructor for Entity.
	 */
	MovingEntity();
	/**
	 * Constructor for Entity.
	 * @param	row					Initial row location.
	 * @param	col					Initial column location.
	 * @param	speed				Initial speed.
	 * @param	headingDirection	Initial heading direction.
	 */
	MovingEntity(int row, int col, int speed, Direction headingDirection = Direction::NORTH);

	/**
	 * Destructor for MovingEntity.
	 */
	virtual ~MovingEntity();


	/**
	 * Obtains this MovingEntity's current speed.
	 * @return	speed	Current speed.
	 */
	int get_speed() const;
	/**
	 * Obtains this MovingEntity's current heading direction.
	 * @return	speed	Current heading direction.
	 */
	Direction get_headingDirection() const;

	/**
	 * Sets this MovingEntity's current speed.
	 * @param	speed	New speed.
	 */
	virtual void set_speed(int speed);
	/**
	 * Sets this MovingEntity's current heading direction.
	 * @param	headingDirection	New heading direction.
	 */
	virtual void set_headingDirection(MovingEntity::Direction headingDirection);

	/**
	 * Obtains this MovingEntity's rotated heading direction. Note: this does NOT change headingDirection.
	 * @return rotated_headingDirection		Rotated heading direction.
	 */
	MovingEntity::Direction get_rotated_headingDirection();

protected:

	/**
	 * Randomizes this MovingEntity's current heading direction.
	 */
	virtual void set_random_headingDirection();
	/**
	 * Moves this MovingEntity by 1 unit, direction specified by `headingDirection`.
	 */
	virtual void move_forward();
	
	int speed;
	Direction headingDirection;

};

#endif /* MOVINGENTITY_H_ */
