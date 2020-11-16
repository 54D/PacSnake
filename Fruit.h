#ifndef FRUIT_H_
#define FRUIT_H_

class Fruit {
public:
	// Display image on GUI, no speical use
	enum class FruitType {APPLE, ORANGE, BANBNA, POWERUP};

	Fruit();
	virtual ~Fruit();

protected:
	int row, col;
};

#endif /* FRUIT_H_ */