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
	virtual void deactivate() override;
public:
	static const int DURATION = 2000;
	static const QString image_lookup;

	PU_Shield(int row, int col);
	virtual ~PU_Shield();

	virtual PowerUp::PowerUpType get_type() const override;

	virtual void activate(Snake* snake) override;

	virtual const QString get_image_lookup() override;
    static QString get_resourceURI();

private:
    static QString resourceURI;
};


#endif //PUSHIELD_H
