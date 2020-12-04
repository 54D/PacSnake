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
	virtual void deactivate() override;

public:
	static const int DURATION = 1500;
	static const QString image_lookup;

    PU_Dash(int row, int col);
    virtual ~PU_Dash();
    
	virtual PowerUp::PowerUpType get_type() const override;

    virtual void activate(Snake* snake) override;

	virtual const QString get_image_lookup() override;
    static QString get_resourceURI();

private:
	static QString resourceURI;
};
#endif /* PU_DASH_H_ */
