#include "HealItem.h"

HealItem::HealItem(int row, int col) :
	Entity(row, col) {}

HealItem::~HealItem() {}

void HealItem::activate(Snake* snake) {
	snake->set_relative_health(1);
}
