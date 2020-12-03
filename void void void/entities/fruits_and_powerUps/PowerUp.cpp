#include "PowerUp.h"

PowerUp::~PowerUp () {
	delete activateSound;
}

PowerUp::PowerUpType PowerUp::get_type() const {
	return type;
}

PowerUp::PowerUp(int row, int col, PowerUp::PowerUpType type) :
	Entity(row, col), type(type) {

	activateSound = new QMediaPlayer();
	activateSound->setMedia(QUrl("qrc:/assets/sound/powerup.wav"));
}
