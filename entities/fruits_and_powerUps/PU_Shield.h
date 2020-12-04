#ifndef PUSHIELD_H
#define PUSHIELD_H

#include <QObject>

#include "PowerUp.h"
#include <entities/snake/Snake.h>
/* Power Up Ability - Shield
 * Immune attack from ghosts, but still can die due to wall collision
 * */
class PU_Shield : public PowerUp {
	Q_OBJECT
public slots:
    /**
     * Deactivate the PowerUp.
     */
	virtual void deactivate() override;
public:
	static const int DURATION = 2000;
	static const QString image_lookup;

    /**
     * Constructer for PU_Shield
     */
	PU_Shield(int row, int col);

    /**
     * Destructer for PU_Shield
     */
	virtual ~PU_Shield();

    /**
     * Get the type of the PowerUp to PU_Shield
     */
	virtual PowerUp::PowerUpType get_type() const override;

    /**
     * Activate the PowerUp
     */
	virtual void activate(Snake* snake) override;

    /**
     * Get the image of the PowerUp
     */
	virtual const QString get_image_lookup() override;

    /**
     * Get the resource URI of the PowerUp
     */
    static QString get_resourceURI();
private:
    static QString resourceURI;
};


#endif //PUSHIELD_H
