#ifndef PACSNAKE_GHOSTBODY_H
#define PACSNAKE_GHOSTBODY_H

#include <entities/MovingEntity.h>

class GhostBody : public MovingEntity {
public:
	friend class BigGhost;
	virtual ~GhostBody();
	GhostBody* get_next() const;
	
protected:
	GhostBody(int row, int col, int speed, Direction headingDirection = Direction::NORTH, GhostBody* next = nullptr);

	virtual void move_forward();
	
private:
	GhostBody* next {nullptr};
};


#endif //GHOSTBODY_H
