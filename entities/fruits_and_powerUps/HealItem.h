#ifndef HEALITEM_H
#define HEALITEM_H

#include <entities/Entity.h>
#include <entities/snake/Snake.h>

class HealItem : public Entity {
public:
	HealItem(int row, int col);
	virtual ~HealItem();

	void activate(Snake* snake);
};

#endif // HEALITEM_H
