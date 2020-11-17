#include "snake.h"
#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsScene>
#include <QGraphicsView>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QGraphicsScene * scene = new QGraphicsScene(0,0,1000,600,this);
    Snake * snake = new Snake();
    snake->setRect(0,0,20,100);
    scene->addItem(snake);
    snake->setFlag(QGraphicsItem::ItemIsFocusable);
    snake->setFocus();
    ui->graphicsView->setScene(scene);
    //QGraphicsView *view = new QGraphicsView(scene);
    ui->graphicsView->show();
}
