#include <QMediaPlayer>

#include "achievements_container.h"
#include "ui_achievements_container.h"

achievements_container::achievements_container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achievements_container)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);

	selectSoundEffect = new QMediaPlayer();
	selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));
}

achievements_container::~achievements_container()
{
	delete selectSoundEffect;
    delete ui;
}

void achievements_container::on_back_button_clicked()
{
	selectSoundEffect->play();
    emit previous_menu();
}
