#ifndef FRUIT_H_
#define FRUIT_H_

// TODO
// Include header

class Fruit {
public:
	// Display image on GUI, no speical use
	enum class FruitType {APPLE, ORANGE, BANBNA, POWERUP};

	Fruit();
	virtual ~Fruit();
	
	int get_row() const;
	int get_col() const;

protected:
	int row, col;
};

#endif /* FRUIT_H_ */