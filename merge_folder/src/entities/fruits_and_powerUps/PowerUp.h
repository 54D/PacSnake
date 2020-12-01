#ifndef POWERUP_H_
#define POWERUP_H_

#include <entities/Entity.h>

// Forward declarations
class Snake;

class PowerUp : public Entity {
public:
    enum class PowerUpType {NONE, DASH, SHIELD, INVISIBLE};
    virtual ~PowerUp();
    
	virtual PowerUp::PowerUpType get_type() const;
    
    virtual void activate(Snake* snake) = 0;
    virtual void deactivate(Snake* snake) = 0;

protected:
    PowerUp(int row, int col, PowerUp::PowerUpType type = PowerUp::PowerUpType::NONE);
	PowerUp::PowerUpType type {PowerUp::PowerUpType::NONE};
};

#endif /* POWERUP_H_ */