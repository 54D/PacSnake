#ifndef POWERUP_H_
#define POWERUP_H_

#include "Fruit.h"

class PowerUp {
public:
	enum class PowerUpType {NONE, DASH, SHIELD, INVISIBLE};
	PowerUp();
	~PowerUp();
	virtual void use() = 0;

private:

};

#endif /* POWERUP_H_ */