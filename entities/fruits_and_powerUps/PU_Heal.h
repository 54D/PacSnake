#ifndef HEALITEM_H
#define HEALITEM_H

#include <QObject>

#include "PowerUp.h"
#include "entities/snake/Snake.h"

class PU_Heal : public PowerUp {
	Q_OBJECT
public slots:
	virtual void deactivate() override;

public:
	static const int DURATION = 500;
	static const QString image_lookup;

	PU_Heal(int row, int col);
	virtual ~PU_Heal();

	virtual PowerUp::PowerUpType get_type() const override;

	virtual void activate(Snake* snake) override;

	virtual const QString get_image_lookup() override;
	static QString get_resourceURI();

private:
	static QString resourceURI;
};

#endif // HEALITEM_H
