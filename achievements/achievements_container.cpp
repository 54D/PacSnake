#include <QMediaPlayer>
#include <QDir>
#include <QDebug>
#include "achievements_container.h"
#include "ui_achievements_container.h"
#include "Achievement.h"

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
    Achievement curr_achievement(":/data/stat.txt");
    curr_ach = &curr_achievement;
}

achievements_container::~achievements_container()
{
	//clear all widget items
	delete selectSoundEffect;
    delete ui;
}

void achievements_container::load_achievements(){
	ui->tableWidget->clear();
	QTableWidgetItem *twi = new QTableWidgetItem("Total distance traveled");
}

/* PRIVATE, SLOTS */

void achievements_container::on_back_button_clicked()
{
	// play sound effect
	selectSoundEffect->play();

	// fire signal when previous navigation is requested
    emit previous_menu();
}
