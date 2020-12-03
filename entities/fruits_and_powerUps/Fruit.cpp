#include "Fruit.h"

// TODO: Change picture, thx
const QString Fruit::image_lookup[5] {
	":/assets/sprite/apple.png",
	":/assets/sprite/grape.png",
	":/assets/sprite/pear.png",
	":/assets/sprite/strawberry.png",
	":/assets/sprite/tangerine.png"
};

Fruit::Fruit(int row, int col) :
	Entity(row, col) {}

Fruit::~Fruit() {}
