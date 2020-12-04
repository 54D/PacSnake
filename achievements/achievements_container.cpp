#include <QMediaPlayer>

#include "achievements_container.h"
#include "ui_achievements_container.h"

/* PUBLIC */

achievements_container::achievements_container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achievements_container)
{
    ui->setupUi(this);

	// disable interaction with achievement list
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);

	// load achievements
	load_achievements();

	// set sound effects
	selectSoundEffect = new QMediaPlayer();
	selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));
}

achievements_container::~achievements_container()
{
	delete selectSoundEffect;
    delete ui;
}

void achievements_container::load_achievements(){
	ui->tableWidget->clear();
}

/* PRIVATE, SLOTS */

void achievements_container::on_back_button_clicked()
{
	// play sound effect
	selectSoundEffect->play();

	// fire signal when previous navigation is requested
    emit previous_menu();
}
