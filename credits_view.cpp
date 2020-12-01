#include "credits_view.h"
#include "ui_credits_view.h"

credits_view::credits_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credits_view)
{
    ui->setupUi(this);
}

credits_view::~credits_view()
{
    delete ui;
}
