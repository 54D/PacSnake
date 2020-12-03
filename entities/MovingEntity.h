#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include <QGraphicsItem>

#include "Entity.h"

class MovingEntity : public Entity {
public:
	static const int MAX_SPEED = 10;
    enum class Direction {NORTH, EAST, SOUTH, WEST};

    virtual ~MovingEntity();

    int get_speed() const;
    Direction get_headingDirection() const;

    virtual void set_speed(int speed);
	virtual void set_headingDirection(MovingEntity::Direction headingDirection);

	// This function only return the rotated headingDirection, will not change the data member
	MovingEntity::Direction get_rotated_headingDirection();

protected:
    MovingEntity();
    MovingEntity(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	virtual void set_random_headingDirection();
	virtual void move_forward();
    
    int speed;
    Direction headingDirection;
};

#endif /* MOVINGENTITY_H_ */
