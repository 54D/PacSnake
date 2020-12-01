#ifndef POWERUP_H_
#define POWERUP_H_

#include <entities/Entity.h>

// Forward declarations
class Snake;

class PowerUp : public Entity {
public:
    enum class PowerUpType {NONE, DASH, SHIELD, INVISIBLE};
    virtual ~PowerUp();
    virtual void activate(Snake* snake) = 0;
    virtual void deactivate(Snake* snake) = 0;
    
    virtual PowerUp::PowerUpType get_type() const = 0;

protected:
    PowerUp(double row, double col, PowerUp::PowerUpType type = PowerUp::PowerUpType::NONE);
	PowerUp::PowerUpType type {PowerUp::PowerUpType::NONE};
};

#endif /* POWERUP_H_ */