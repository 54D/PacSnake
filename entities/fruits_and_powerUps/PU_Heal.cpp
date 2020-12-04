#include <QGraphicsPixmapItem>
#include <QTimer>

#include "PU_Heal.h"

const QString PU_Heal::image_lookup = ":/assets/sprite/heal.png";

PU_Heal::PU_Heal(int row, int col) :
	PowerUp(row, col, PowerUp::PowerUpType::HEAL) {}

PU_Heal::~PU_Heal() {}

QString PU_Heal::resourceURI = ":/assets/sprite/heal.png";

PowerUp::PowerUpType PU_Heal::get_type() const {
	return type;
}

void PU_Heal::activate(Snake* snake) {
	// Only one power up can be activated at the same time
	if (snake->get_pu_activate() != nullptr) {
		qDebug() << "[ERROR] No power up in inventory";
		return;
	}

	qDebug() << "HEAL activated";
	// Play sound effect
	if (activateSound->state() == QMediaPlayer::PlayingState) {
		activateSound->setPosition(0);
	}
	else if (activateSound->state() == QMediaPlayer::StoppedState) {
		activateSound->play();
	}

	pu_owner = snake;
	// Heal 1 health point
	snake->set_relative_health(1);

	// Set activated power up
	snake->set_pu_activate(this);
	snake->updatePowerUpState();

	deactivateCountDown = new QTimer(this);
	connect(deactivateCountDown, SIGNAL(timeout()), this, SLOT(deactivate()));
	deactivateCountDown->start(DURATION);
}

void PU_Heal::deactivate() {
	if (pu_owner->get_pu_activate() == nullptr)	{
		qDebug() << "[ERROR] No power up to deactivate";
		return;
	}
	qDebug() << "HEAL deactivated";
	deactivateCountDown->stop();

	pu_owner->set_pu_activate(nullptr);
	pu_owner->updatePowerUpState();

	disconnect(deactivateCountDown, SIGNAL(timeout()), this, SLOT(deactivate()));
	delete deactivateCountDown;
}

const QString PU_Heal::get_image_lookup() {
	return PU_Heal::image_lookup;
}

QString PU_Heal::get_resourceURI(){
	return resourceURI;
}
