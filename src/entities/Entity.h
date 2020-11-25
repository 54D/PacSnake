#ifndef ENTITY_H_
#define ENTITY_H_

class Entity {	
public:
	virtual ~Entity();

	double get_row() const;
	double get_col() const;

	void set_row(double row);
	void set_col(double col);
	void set_coordinate(double row, double col);
	
protected:
	Entity();
	Entity(double row, double col);

	double row, col;
};


#endif /* ENTITY_H_ */
