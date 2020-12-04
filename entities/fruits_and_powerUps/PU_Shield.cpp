#include "PowerUp.h"
#include "PU_Shield.h"

#include <QTimer>

const QString PU_Shield::image_lookup = ":/assets/sprite/shield.png";

PU_Shield::PU_Shield(int row, int col) :
    PowerUp(row, col, PowerUp::PowerUpType::SHIELD) {
    //this->pixmap = QPixmap(":/assets/image");
}

PU_Shield::~PU_Shield() {}

QString PU_Shield::resourceURI = ":/assets/sprite/shield.png";

PowerUp::PowerUpType PU_Shield::get_type() const {
	return type;
}

void PU_Shield::activate(Snake *snake) {
	// Only one power up can be activated at the same time
	if (snake->get_pu_activate() != nullptr) {
		qDebug() << "[ERROR] No power up in inventory";
		return;
	}
	qDebug() << "SHIELD activated!";
	// Play sound effect
	if (activateSound->state() == QMediaPlayer::PlayingState) {
		activateSound->setPosition(0);
	}
	else if (activateSound->state() == QMediaPlayer::StoppedState) {
		activateSound->play();
	}

	pu_owner = snake;
	snake->set_ghost_immunity(true);
	// Set activated power up
	snake->set_pu_activate(this);
	deactivateCountDown = new QTimer(this);
	connect(deactivateCountDown, SIGNAL(timeout()), this, SLOT(deactivate()));
	deactivateCountDown->start(DURATION);
}

void PU_Shield::deactivate() {
	if (pu_owner->get_pu_activate() == nullptr) {
		qDebug() << "[ERROR] No power up to deactivate";
		return;
	}
	qDebug() << "SHIELD deactivated!";
	deactivateCountDown->stop();
	// Reset immunity
	pu_owner->set_pu_activate(nullptr);
	pu_owner->set_ghost_immunity(false);
	disconnect(deactivateCountDown, SIGNAL(timeout()), this, SLOT(deactivate()));
	delete deactivateCountDown;
}

const QString PU_Shield::get_image_lookup() {
	return PU_Shield::image_lookup;
}

QString PU_Shield::get_resourceURI(){
    return resourceURI;
}
