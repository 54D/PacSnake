#ifndef FRUIT_H_
#define FRUIT_H_

#include <QString>
#include <entities/Entity.h>

class Fruit : public Entity {
public:
    /**
     * Constructor for Fruit.
     */
	Fruit(int row, int col);

    /**
     * Destructor for Fruit.
     */
    virtual ~Fruit();

    /**
     * Look up different image for different fruits
     */
	static const QString image_lookup[5];
};

#endif /* FRUIT_H_ */
