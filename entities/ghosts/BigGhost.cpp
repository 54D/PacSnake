#include "BigGhost.h"

BigGhost::BigGhost(int row, int col, int speed, Direction headingDirection) :
	GhostBody(row, col, speed, headingDirection) {

	GhostBody* currentGhostBody = this;
	// [2]
	currentGhostBody->next = new GhostBody(row, col + 1, speed, headingDirection);
	currentGhostBody = currentGhostBody->next;
	// [3]
	currentGhostBody->next = new GhostBody(row + 1, col + 1, speed, headingDirection);
	currentGhostBody = currentGhostBody->next;
	// [4]
	currentGhostBody->next = new GhostBody(row + 1, col, speed, headingDirection);
	currentGhostBody = currentGhostBody->next;
}

BigGhost::~BigGhost() {}

void BigGhost::move_forward() {
	current
	do {

	}
}
