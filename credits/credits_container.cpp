#include "credits_container.h"
#include "ui_credits_container.h"
#include "credits_view.h"
#include <QStackedWidget>
#include <QDebug>

credits_container::credits_container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credits_container)
{
    ui->setupUi(this);

	selectSound = new QMediaPlayer();
	selectSound->setMedia(QUrl("qrc:/assets/sound/select.wav"));
    credits_view_widget = new credits_view;
    ui->scrollArea->setWidget(credits_view_widget);
}

credits_container::~credits_container()
{
    delete credits_view_widget;
	delete selectSound;
    delete ui;
}

void credits_container::on_back_button_clicked()
{
	selectSound->play();
    emit previous_menu();
}
