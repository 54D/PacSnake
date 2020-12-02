#ifndef BIGGHOST_H
#define BIGGHOST_H

#include "GhostBody.h"

/*	Next pointer direction of BigGhost
 *	1 (this) -> 2
 *	^	        v
 *	4 <-------- 3
 * */
class BigGhost final : public GhostBody {
public:
	BigGhost(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	virtual ~BigGhost();

	virtual void set_speed(int speed) override;
	virtual void set_headingDirection(MovingEntity::Direction headingDirection) override;

	virtual void move_forward() override;

private:
	// Generate a number [min, max] that the NormalGhost will change direction if stepCount reaches that number
	void set_random_stepUntilDirctionChange(int lower = 1, int upper = 10);
	virtual void set_random_headingDirection() override;

	int stepUntilDirctionChange;
	int stepCount {0};
};

#endif // BIGGHOST_H
