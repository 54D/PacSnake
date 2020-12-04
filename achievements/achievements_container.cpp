#include <string>
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

	// set dimensions
	ui->tableWidget->setColumnWidth(0, ui->tableWidget->width()/2);
	ui->tableWidget->setColumnWidth(1, (ui->tableWidget->width()/2) - 1);

	// set sound effects
	selectSoundEffect = new QMediaPlayer();
	selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));
    QString temp = QDir::currentPath() + "/stat.txt";
    curr_ach = new Achievement(temp.toStdString());
}

achievements_container::~achievements_container()
{
	for(int i=0;i<entries.length();i++){
		delete entries.at(i);
	}
	entries.clear();
	delete curr_ach;
	delete selectSoundEffect;
	delete ui;
}

void achievements_container::stackedWidgetChanged(int index){
	if(index!=2&&backButtonPressed){
		backButtonPressed = false;
	}else{
		load_achievements();
	}
}

void achievements_container::load_achievements(){
	QTableWidgetItem *ingame_distance_display = new QTableWidgetItem("Distance traveled");
	ui->tableWidget->setItem(0,0,ingame_distance_display);
	entries.append(ingame_distance_display);
	qDebug() << curr_ach;
	qDebug() << curr_ach->get_ingame_distance();
	QTableWidgetItem *ingame_distance_stat = new QTableWidgetItem(QString::fromStdString(std::to_string(curr_ach->get_ingame_distance())));
	ui->tableWidget->setItem(0,1,ingame_distance_stat);
	entries.append(ingame_distance_stat);
	QTableWidgetItem *survival_time_display = new QTableWidgetItem("Time survived");
	ui->tableWidget->setItem(1,0,survival_time_display);
	entries.append(survival_time_display);
	QTableWidgetItem *survival_time_stat = new QTableWidgetItem(QString::fromStdString(std::to_string(curr_ach->get_survival_time())));
	ui->tableWidget->setItem(1,1,survival_time_stat);
	entries.append(survival_time_stat);
	QTableWidgetItem *fruits_eaten_display = new QTableWidgetItem("Fruits eaten");
	ui->tableWidget->setItem(2,0,fruits_eaten_display);
	entries.append(fruits_eaten_display);
	QTableWidgetItem *fruits_eaten_stat = new QTableWidgetItem(QString::fromStdString(std::to_string(curr_ach->get_fruits_eaten())));
	ui->tableWidget->setItem(2,1,fruits_eaten_stat);
	entries.append(fruits_eaten_stat);
	QTableWidgetItem *longest_snake_length_display = new QTableWidgetItem("Longest snake length");
	ui->tableWidget->setItem(3,0,longest_snake_length_display);
	entries.append(longest_snake_length_display);
	QTableWidgetItem *longest_snake_length_stat = new QTableWidgetItem(QString::fromStdString(std::to_string(curr_ach->get_longest_snake_length())));
	ui->tableWidget->setItem(3,1,longest_snake_length_stat);
	entries.append(longest_snake_length_stat);
	QTableWidgetItem *play_count_display = new QTableWidgetItem("Times played");
	ui->tableWidget->setItem(4,0,play_count_display);
	entries.append(play_count_display);
	QTableWidgetItem *play_count_stat = new QTableWidgetItem(QString::fromStdString(std::to_string(curr_ach->get_play_count())));
	ui->tableWidget->setItem(4,1,play_count_stat);
	entries.append(play_count_stat);
}

Achievement* achievements_container::get_achievement_object(){
	return curr_ach;
}

/* PRIVATE SLOTS */

void achievements_container::on_back_button_clicked()
{
	backButtonPressed = true;

	// play sound effect
	selectSoundEffect->play();

	// fire signal when previous navigation is requested
	emit previous_menu();
}
