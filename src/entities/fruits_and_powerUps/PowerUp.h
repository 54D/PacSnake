#ifndef POWERUP_H_
#define POWERUP_H_

#include "Fruit.h"

class PowerUp : public Fruit {
public:
	enum class PowerUpType {NONE, DASH, SHIELD, INVISIBLE};
	PowerUp();
	~PowerUp();

private:

};

#endif /* POWERUP_H_ */