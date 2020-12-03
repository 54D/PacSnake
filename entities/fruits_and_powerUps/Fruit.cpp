#include "Fruit.h"

// TODO: Change picture, thx
const QString Fruit::image_lookup[5] {
	":/assets/sprite/green.png",
	":/assets/sprite/green.png",
	":/assets/sprite/green.png",
	":/assets/sprite/green.png",
	":/assets/sprite/green.png"
};

Fruit::Fruit(int row, int col) :
	Entity(row, col) {}

Fruit::~Fruit() {}
