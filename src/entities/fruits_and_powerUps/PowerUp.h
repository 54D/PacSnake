#ifndef POWERUP_H_
#define POWERUP_H_

#include "src/entities/Entity.h"
#include "src/entities/snake/Snake.h"

class PowerUp : public Entity {
public:
	enum class PowerUpType {NONE, DASH, SHIELD, INVISIBLE};
	virtual ~PowerUp();
	virtual void activate(Snake& snake) = 0;
	virtual void deactivate(Snake& snake) = 0;

protected:
	PowerUp(double row, double col);
};

#endif /* POWERUP_H_ */