#include "PowerUp.h"
#include "PU_Shield.h"

PU_Shield::PU_Shield(int row, int col) :
    PowerUp(row, col, PowerUp::PowerUpType::SHIELD) {
    //this->pixmap = QPixmap(":/assets/image");
}

PU_Shield::~PU_Shield() {}

PowerUp::PowerUpType PU_Shield::get_type() const {
	return type;
}

void PU_Shield::activate(Snake *snake) {
	// Play sound effect
	if (activateSound->state() == QMediaPlayer::PlayingState) {
		activateSound->setPosition(0);
	}
	else if (activateSound->state() == QMediaPlayer::StoppedState) {
		activateSound->play();
	}

	// Only one power up can be activated at the same time
	if (snake->get_pu_activate() != nullptr)
		return;

	snake->set_ghost_immunity(true);
	// Set activated power up
	snake->set_pu_activate(this);
}

void PU_Shield::deactivate(Snake *snake) {
	if (snake->get_pu_activate() == nullptr)
		return;
	// Reset immunity
	snake->set_pu_activate(nullptr);
	snake->set_ghost_immunity(false);
}
