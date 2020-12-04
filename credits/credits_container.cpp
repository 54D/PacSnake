#include "credits_container.h"
#include "ui_credits_container.h"
#include "credits_view.h"
#include <QStackedWidget>
#include <QDebug>

/* PUBLIC */

credits_container::credits_container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credits_container)
{
    ui->setupUi(this);

	// set sound effects
	selectSoundEffect = new QMediaPlayer();
	selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));

	// embeds a credits_view ui
    credits_view_widget = new credits_view;
    ui->scrollArea->setWidget(credits_view_widget);
}

credits_container::~credits_container()
{
    delete credits_view_widget;
	delete selectSoundEffect;
    delete ui;
}

/* PRIVATE SLOTS */

void credits_container::on_back_button_clicked()
{
	// play sound effect
	selectSoundEffect->play();

	// fire signal when previous navigation is requested
	emit previous_menu();
}
