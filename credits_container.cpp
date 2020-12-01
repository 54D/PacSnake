#include "credits_container.h"
#include "ui_credits_container.h"
#include <QStackedWidget>
#include <QDebug>

credits_container::credits_container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credits_container)
{
    ui->setupUi(this);
}

credits_container::~credits_container()
{
    delete ui;
}

void credits_container::on_back_button_clicked()
{
    emit previous_menu();
}
