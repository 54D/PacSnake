#ifndef FRUIT_H_
#define FRUIT_H_

#include "src/entities/Entity.h"

class Fruit : public Entity {
public:
	// Display image on GUI, no speical use
	enum class FruitType {APPLE, ORANGE, BANBNA};

	Fruit();
	virtual ~Fruit();
};

#endif /* FRUIT_H_ */