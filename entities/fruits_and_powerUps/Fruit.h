#ifndef FRUIT_H_
#define FRUIT_H_

#include <QString>
#include <entities/Entity.h>

class Fruit : public Entity {
public:
	Fruit(int row, int col);

    virtual ~Fruit();

	static const QString image_lookup[5];
};

#endif /* FRUIT_H_ */
