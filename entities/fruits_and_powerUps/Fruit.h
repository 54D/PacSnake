#ifndef FRUIT_H_
#define FRUIT_H_

#include <entities/Entity.h>

class Fruit : public Entity {
public:
    // Display image on GUI, no speical use
    enum class FruitType {APPLE, ORANGE, BANBNA};

	Fruit(int row, int col);
    virtual ~Fruit();
};

#endif /* FRUIT_H_ */
