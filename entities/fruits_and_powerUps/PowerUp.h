#ifndef POWERUP_H_
#define POWERUP_H_

#include <entities/Entity.h>
#include <QMediaPlayer>

// Forward declarations
class Snake;

class PowerUp : public Entity {
public:
	enum class PowerUpType {NONE, DASH, HEAL ,SHIELD};
    virtual ~PowerUp();
    
	virtual PowerUp::PowerUpType get_type() const;
    
    virtual void activate(Snake* snake) = 0;
	virtual void deactivate() = 0;
	virtual const QString get_image_lookup() = 0;

protected:
    PowerUp(int row, int col, PowerUp::PowerUpType type = PowerUp::PowerUpType::NONE);
	PowerUp::PowerUpType type {PowerUp::PowerUpType::NONE};
	Snake* pu_owner {nullptr};

	QMediaPlayer* activateSound;
	QTimer* deactivateCountDown;
};

#endif /* POWERUP_H_ */
