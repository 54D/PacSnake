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
#include "credits_container.h"
#include "credits_view.h"
#include "game_view.h"
#include "ui_achievements_container.h"
#include "ui_main_container.h"

main_container::main_container(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::main_container)
{
    ui->setupUi(this);
    game_view *gv = {new game_view};
    ui->stackedWidget->addWidget(gv);
    ui->stackedWidget->addWidget(new achievements_container);
    ui->stackedWidget->addWidget(new credits_container);

    connect(ui->stackedWidget->widget(2), SIGNAL(previous_menu()), this, SLOT(bring_back()));
    connect(ui->stackedWidget->widget(3), SIGNAL(previous_menu()), this, SLOT(bring_back()));
    connect(this, SIGNAL(stackedWidgetChange(int)), gv, SLOT(stackedWidgetChanged(int)));

	selectSound = new QMediaPlayer();
	selectSound->setMedia(QUrl("qrc:/assets/sound/select.wav"));
}

main_container::~main_container()
{
	delete selectSound;
    delete ui;
}

void main_container::on_startButton_clicked()
{
	selectSound->play();
    ui->stackedWidget->setCurrentIndex(1);
}

void main_container::on_achButton_clicked()
{
	selectSound->play();
	ui->stackedWidget->setCurrentIndex(2);
}

void main_container::on_creditsButton_clicked()
{
	selectSound->play();
	ui->stackedWidget->setCurrentIndex(3);
}

void main_container::on_leaveButton_clicked()
{
	selectSound->play();
	QCoreApplication::exit(0);
}

void main_container::on_stackedWidget_currentChanged(int index){
    emit stackedWidgetChange(index);
}

void main_container::bring_back()
{
    qDebug() << "bring_back | RECEIVE";
    ui->stackedWidget->setCurrentIndex(0);
}
