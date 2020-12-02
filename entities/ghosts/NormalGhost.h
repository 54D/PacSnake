#ifndef NORMALGHOST_H
#define NORMALGHOST_H

#include "GhostBody.h"

class NormalGhost final : public GhostBody {
public:
	NormalGhost(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	virtual ~NormalGhost();
	
	virtual void move_forward() override;
	
private:
	// Generate a number [min, max] that the NormalGhost will change direction if stepCount reaches that number
	void set_random_stepUntilDirctionChange(int lower = 1, int upper = 15);

	int stepUntilDirctionChange;
	int stepCount {0};
};


#endif // NORMALGHOST_H
