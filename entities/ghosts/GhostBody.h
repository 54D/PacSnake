#ifndef PACSNAKE_GHOSTBODY_H
#define PACSNAKE_GHOSTBODY_H

#include <entities/MovingEntity.h>

class GhostBody : public MovingEntity {
public:
	/**
	 * Friend class.
	 */
	friend class BigGhost;

	/**
	 * Destructor for GhostBody.
	 */
	virtual ~GhostBody();

	/**
	 * Obtains the next linked GhostBody.
	 * @return	next	Next linked GhostBody. `nullptr` if there is no more linked GhostBody.
	 */
	GhostBody* get_next() const;
	
protected:
	/**
	 * Construtor for GhostBody
	 * @param	row					Initial row location.
	 * @param	col					Initial column location.
	 * @param	speed				Initial speed.
	 * @param	headingDirection	Initial heading direction.
	 * @param	next				Next GhostBody.
	 */
	GhostBody(int row, int col, int speed, Direction headingDirection = Direction::NORTH, GhostBody* next = nullptr);

	/**
	 * Moves this GhostBody by 1 unit, direction specified by `headingDirection`.
	 */
	virtual void move_forward() override;
	
private:
	GhostBody* next {nullptr};
};


#endif //GHOSTBODY_H
