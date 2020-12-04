#ifndef HEALITEM_H
#define HEALITEM_H

#include <QObject>

#include "PowerUp.h"
#include "entities/snake/Snake.h"

class PU_Heal : public PowerUp {
	Q_OBJECT
public slots:
    /**
     * Deactivate the PowerUp.
     */
	virtual void deactivate() override;

public:
	static const int DURATION = 500;
	static const QString image_lookup;

    /**
     * Constructer for PU_Heal
     */
	PU_Heal(int row, int col);

    /**
     * Destructer for PU_Heal
     */
	virtual ~PU_Heal();

    /**
     * Get the type of the PowerUp to PU_Heal
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

#endif // HEALITEM_H
