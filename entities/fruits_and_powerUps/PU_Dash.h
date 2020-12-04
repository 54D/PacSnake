#ifndef PU_DASH_H_
#define PU_DASH_H_

#include <QObject>

#include "PowerUp.h"
#include <entities/snake/Snake.h>

/* Power Up Ability - Dash
 * When activate, the snake will gain a short movement speed bonus for a split second (i.e.: few game ticks)
*/
class PU_Dash : public PowerUp {
	Q_OBJECT
public slots:
    /**
     * Deactivate the PowerUp.
     */
	virtual void deactivate() override;

public:
	static const int DURATION = 50;
	static const QString image_lookup;

    /**
     * Constructer for PU_Dash
     */
    PU_Dash(int row, int col);

    /**
     * Destructer for PU_Dash
     */
    virtual ~PU_Dash();
    
    /**
     * Get the type of the PowerUp to PU_Dash
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
#endif /* PU_DASH_H_ */
