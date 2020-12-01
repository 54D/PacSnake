#ifndef BIGGHOST_H
#define BIGGHOST_H

#include "GhostBody.h"

/*	Next pointer direction of BigGhost
 *	1 -> 2
 *	^	 v
 *	4 <- 3
 * */
class BigGhost final : public GhostBody {
public:
	BigGhost(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	virtual ~BigGhost();

	virtual void move_forward() override;
	virtual void set_headingDirection(MovingEntity::Direction headingDirection) override;
};

#endif // BIGGHOST_H
