#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include "Entity.h"

class MovingEntity : public Entity {
public:
	enum class Direction {NORTH, EAST, SOUTH, WEST};

	virtual ~MovingEntity();

	double get_speed() const;
	Direction get_headingDirection() const;

	void set_speed(double speed);
	void set_headingDirection(MovingEntity::Direction headingDirection);
	
protected:
	MovingEntity();
	MovingEntity(double row, double col, double speed, Direction headingDirection = Direction::NORTH);

	double speed;
	Direction headingDirection;
};

#endif /* MOVINGENTITY_H_ */