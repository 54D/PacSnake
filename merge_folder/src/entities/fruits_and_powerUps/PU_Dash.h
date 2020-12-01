#ifndef PU_DASH_H_
#define PU_DASH_H_

#include "PowerUp.h"
#include <entities/snake/Snake.h>
/* Power Up Ability - Dash
 * When activate, the snake will gain a short movement speed bonus for a split second (i.e.: few game ticks)
*/
class Snake;

class PU_Dash : public PowerUp {
public:
    PU_Dash(int row, int col);
    virtual ~PU_Dash();
    
	virtual PowerUp::PowerUpType get_type() const override;
    
    virtual void activate(Snake* snake) override;
    virtual void deactivate(Snake* snake) override;
};

#endif /* PU_DASH_H_ */