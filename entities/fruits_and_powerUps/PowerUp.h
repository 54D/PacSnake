#ifndef POWERUP_H_
#define POWERUP_H_

#include <entities/Entity.h>
#include <QMediaPlayer>

// Forward declarations
class Snake;

class PowerUp : public Entity {
public slots:
	virtual void deactivate() = 0;

public:
    /**
     * Type of PowerUP:
     * Dash: When activate, the snake will gain a short movement speed bonus for a split second (i.e.: few game ticks)
     * Heal: Heal 1 health point for the snake
     * Shield: Immune attack from ghosts, but still can die due to wall collision
     */
	enum class PowerUpType {NONE, DASH, HEAL ,SHIELD};

    /**
     * Destructor for PowerUP.
     */
    virtual ~PowerUp();
    
    /**
     * Get the type of the PowerUp item
     */
	virtual PowerUp::PowerUpType get_type() const;
    
    /**
     * Activate the PowerUp
     */
    virtual void activate(Snake* snake) = 0;

    /**
     * Get the image of the PowerUp from its type
     */
	virtual const QString get_image_lookup() = 0;

protected:
    PowerUp(int row, int col, PowerUp::PowerUpType type = PowerUp::PowerUpType::NONE);
	PowerUp::PowerUpType type {PowerUp::PowerUpType::NONE};
	Snake* pu_owner {nullptr};

	QMediaPlayer* activateSoundEffect;
	QMediaPlayer* deactivateSoundEffect;
	QTimer* deactivateCountDown;
};

#endif /* POWERUP_H_ */
