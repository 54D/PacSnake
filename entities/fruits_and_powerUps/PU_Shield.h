#ifndef PUSHIELD_H
#define PUSHIELD_H

#include "PowerUp.h"
#include <entities/snake/Snake.h>
/* Power Up Ability - Shield
 * Immune attack from ghosts, but still can die due to wall collision
 * */
class PU_Shield : public PowerUp {
public:
	PU_Shield(int row, int col);
	virtual ~PU_Shield();

	virtual PowerUp::PowerUpType get_type() const override;

	virtual void activate(Snake* snake) override;
    virtual void deactivate(Snake* snake) override;
};


#endif //PUSHIELD_H
