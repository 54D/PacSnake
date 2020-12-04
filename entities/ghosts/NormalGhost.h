#ifndef NORMALGHOST_H
#define NORMALGHOST_H

#include "GhostBody.h"

class NormalGhost final : public GhostBody {
public:
	/**
	 * Public const
	 * @param	image_lookup	Store directory of NormalGhost's images 
	*/
	static const QString image_lookup[5];

	/**
	 * Constructor for NormalGhost.
	 * @param	row					Initial row location.
	 * @param	col					Initial column location.
	 * @param	speed				Initial speed.
	 * @param	headingDirection	Initial heading direction.
	*/
	NormalGhost(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	
	/**
	 * Destructor for NormalGhost.
	*/
	virtual ~NormalGhost();
	
	/**
	 * Moves this NormalGhost by 1 unit, direction specified by `headingDirection`.
	*/
	virtual void move_forward() override;

private:
	/**
	 * Sets this NormalGhost's `stepUntilDirctionChange` to a random value bounded by [lower, upper].
	 * Heading direction of this NormalGhosts will changes if value of `stepCount` equals to `stepUntilDirctionChange`.
	 * @param	lower	The lower bound for generating the random value of `stepUntilDirctionChange`.
	 * @param	upper	The upper bound for generating the random value of `stepUntilDirctionChange`.
	*/
	void set_random_stepUntilDirctionChange(int lower = 1, int upper = 10);

	int stepUntilDirctionChange;
	int stepCount {0};
};


#endif // NORMALGHOST_H
