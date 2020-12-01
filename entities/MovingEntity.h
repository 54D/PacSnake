#ifndef MOVINGENTITY_H_
#define MOVINGENTITY_H_

#include "Entity.h"

class MovingEntity : public Entity {
public:
    enum class Direction {NORTH, EAST, SOUTH, WEST};

    virtual ~MovingEntity();

    int get_speed() const;
    Direction get_headingDirection() const;

    virtual void set_speed(int speed);
    virtual void set_headingDirection(MovingEntity::Direction headingDirection);
 
protected:
    MovingEntity();
    MovingEntity(int row, int col, int speed, Direction headingDirection = Direction::NORTH);
	void set_random_headingDirection();
	virtual void move_forward();
    
    int speed;
    Direction headingDirection;
};

#endif /* MOVINGENTITY_H_ */