#ifndef PU_DASH_H_
#define PU_DASH_H_

#include "PowerUp.h"
#include <entities/snake/Snake.h>
/*  Power Up Ability - Dash
    When activate, the snake will gain a short movement speed bonus for a split second (i.e.: few game ticks)
*/

class Snake;

class PU_Dash : public PowerUp {
public:
    PU_Dash(double row, double col);
    virtual ~PU_Dash();
    virtual void activate(Snake* snake);
    virtual void deactivate(Snake* snake);
	
	PowerUp::PowerUpType get_type() const;
};

#endif /* PU_DASH_H_ */