#include "credits_view.h"
#include "ui_credits_view.h"

/* PUBLIC */

credits_view::credits_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credits_view)
{
    ui->setupUi(this);

	// Note: All contents in credit_view ui has been implemented directly in credits_view.ui.
}

credits_view::~credits_view()
{
    delete ui;
}
