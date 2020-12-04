#include "PowerUp.h"

PowerUp::~PowerUp () {
	delete activateSoundEffect;
	delete deactivateSoundEffect;
}

PowerUp::PowerUpType PowerUp::get_type() const {
	return type;
}

PowerUp::PowerUp(int row, int col, PowerUp::PowerUpType type) :
	Entity(row, col), type(type) {

	activateSoundEffect = new QMediaPlayer();
	activateSoundEffect->setMedia(QUrl("qrc:/assets/sound/powerup.wav"));
	activateSoundEffect->setVolume(50);

	deactivateSoundEffect = new QMediaPlayer();
	deactivateSoundEffect->setMedia(QUrl("qrc:/assets/sound/powerup_deactivate.wav"));
	deactivateSoundEffect->setVolume(50);
}
