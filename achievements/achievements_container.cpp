#include "achievements_container.h"
#include "ui_achievements_container.h"

achievements_container::achievements_container(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::achievements_container)
{
    ui->setupUi(this);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
}

achievements_container::~achievements_container()
{
    delete ui;
}

void achievements_container::on_back_button_clicked()
{
    emit previous_menu();
}
