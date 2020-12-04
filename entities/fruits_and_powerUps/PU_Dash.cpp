#include "PowerUp.h"
#include "PU_Dash.h"
#include <entities/MovingEntity.h>

#include <QTimer>
#include <QGraphicsPixmapItem>

const QString PU_Dash::image_lookup = ":/assets/sprite/dash.png";

PU_Dash::PU_Dash(int row, int col) :
    PowerUp(row, col, PowerUp::PowerUpType::DASH) {
    //this->pixmap = QPixmap(":/assets/image");
}
	
PU_Dash::~PU_Dash() {}

QString PU_Dash::resourceURI = ":/assets/sprite/dash.png";

PowerUp::PowerUpType PU_Dash::get_type() const {
	return type;
}

void PU_Dash::activate(Snake* snake) {
	// Only one power up can be activated at the same time
	if (snake->get_pu_activate() != nullptr) {
		qDebug() << "[ERROR] No power up in inventory";
		return;
	}

	qDebug() << "DASH activated!";
	// Play sound effect
	if (activateSound->state() == QMediaPlayer::PlayingState) {
		activateSound->setPosition(0);
	}
	else if (activateSound->state() == QMediaPlayer::StoppedState) {
		activateSound->play();
	}


	// Set activated power up
	pu_owner = snake;
	pu_owner->set_pu_activate(this);
	pu_owner->updatePowerUpState();
	pu_owner->set_speed(MovingEntity::MAX_GAMETICK_SPEED);

	deactivateCountDown = new QTimer(this);
	connect(deactivateCountDown, SIGNAL(timeout()), this, SLOT(deactivate()));
	deactivateCountDown->start(DURATION);
}

void PU_Dash::deactivate() {
	if (pu_owner->get_pu_activate() == nullptr) {
		qDebug() << "[ERROR] No power up to deactivate";
		return;
	}
	qDebug() << "DASH activated!";
	deactivateCountDown->stop();
    // Reset speed
	pu_owner->set_pu_activate(nullptr);
	pu_owner->updatePowerUpState();

	int newSpeed = pu_owner->calculate_level_speed();
	pu_owner->set_speed(newSpeed);

	disconnect(deactivateCountDown, SIGNAL(timeout()), this, SLOT(deactivate()));
	delete deactivateCountDown;
}

const QString PU_Dash::get_image_lookup() {
	return PU_Dash::image_lookup;
}

QString PU_Dash::get_resourceURI(){
    return resourceURI;
}
