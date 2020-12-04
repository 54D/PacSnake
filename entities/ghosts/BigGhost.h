#ifndef BIGGHOST_H
#define BIGGHOST_H

#include "GhostBody.h"

/**	
 * Next pointer direction of BigGhost
 *	1 (this) -> 2
 *	^	        v
 *	4 <-------- 3
 */
class BigGhost final : public GhostBody {
public:
	/**
	 * Public const
	 */
	static const QString image_lookup[4];

	/**
	 * Constructor fpr BigGhost.
	 * @param	row					Initial row location.
	 * @param	col					Initial col location.
	 * @param 	speed				Initial speed.
	 * @param	headingDirection	Initial heading direction.
	*/
	BigGhost(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	
	/**
	 * Destructor for BigGhost
	*/
	virtual ~BigGhost();

	/**
	 * Sets the current speed of this BigGhost.
	 * @param	speed	New speed.
	*/
	virtual void set_speed(int speed) override;
	/**
	 * Sets the current heading direction of this BigGhost.
	 * @param	headingDirection	New heading direction.
	*/
	virtual void set_headingDirection(MovingEntity::Direction headingDirection) override;

	/**
	 * Move this BigGhost by 1 unit, direction sepecified by `headingDirection`
	*/
	virtual void move_forward() override;

private:
	/**
	 * Sets this BigGhost's `stepUntilDirctionChange` to a random value bounded by [lower, upper].
	 * Heading direction of this BigGhost will changes if value of `stepCount` equals to `stepUntilDirctionChange`.
	 * @param	lower	The lower bound for generating the random value of `stepUntilDirctionChange`.
	 * @param	upper	The upper bound for generating the random value of `stepUntilDirctionChange`.
	*/
	void set_random_stepUntilDirctionChange(int lower = 1, int upper = 10);
	/**
	 * Randomizes this BigGhost's current heading direction.
	*/
	virtual void set_random_headingDirection() override;

	int stepUntilDirctionChange;
	int stepCount {0};
};

#endif // BIGGHOST_H
