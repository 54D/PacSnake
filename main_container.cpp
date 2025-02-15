#include <iostream>
#include <sstream>
#include <string>

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QMediaPlayer>

#include "main_container.h"
#include "ui_main_container.h"
#include "entities/snake/SnakeBody.h"
#include "entities/snake/Snake.h"
#include "achievements/achievements_container.h"
#include "achievements/Achievement.h"
#include "credits/credits_container.h"
#include "credits/credits_view.h"
#include "game_view.h"
#include "ui_achievements_container.h"
#include "ui_main_container.h"

/* PUBLIC */

main_container::main_container(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_container)
{
    ui->setupUi(this);

	// Initialize subwidgets and add them to the stackedWidget.
	achievements_container *av = {new achievements_container};
	ui->stackedWidget->addWidget(av);
	game_view *gv = new game_view(this,av->get_achievement_object());
	ui->stackedWidget->addWidget(gv);
    ui->stackedWidget->addWidget(new credits_container);

	// Connects the previous_menu() signal such that stackedWidget brings the view back to the main menu when needed.
    connect(ui->stackedWidget->widget(1), SIGNAL(previous_menu()), this, SLOT(bring_back()));
    connect(ui->stackedWidget->widget(2), SIGNAL(previous_menu()), this, SLOT(bring_back()));
	connect(ui->stackedWidget->widget(3), SIGNAL(previous_menu()), this, SLOT(bring_back()));
	connect(this, SIGNAL(stackedWidgetChange(int)), gv, SLOT(stackedWidgetChanged(int)));
	connect(this, SIGNAL(stackedWidgetChange(int)), av, SLOT(stackedWidgetChanged(int)));

	// Setup sound effect.
	selectSoundEffect = new QMediaPlayer();
	selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));
}

main_container::~main_container()
{
	delete selectSoundEffect;
    delete ui;
}

/* PRIVATE SLOTS */

void main_container::on_startButton_clicked()
{
	selectSoundEffect->play();
	ui->stackedWidget->setCurrentIndex(2);
}

void main_container::on_achButton_clicked()
{
	selectSoundEffect->play();
	ui->stackedWidget->setCurrentIndex(1);
}

void main_container::on_creditsButton_clicked()
{
	selectSoundEffect->play();
	ui->stackedWidget->setCurrentIndex(3);
}

void main_container::on_leaveButton_clicked()
{
	selectSoundEffect->play();
	QCoreApplication::exit(0);
}

void main_container::on_stackedWidget_currentChanged(int index){
    emit stackedWidgetChange(index);
}

void main_container::bring_back()
{
    ui->stackedWidget->setCurrentIndex(0);
}
