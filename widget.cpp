#include "widget.h"
#include "ui_widget.h"
#include "GameEngine.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>

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
    scene->addItem(user);
    ui->graphicsView->setScene(scene);
    //start_game();
    //QGraphicsView *view = new QGraphicsView(scene);
    ui->graphicsView->show();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(game_timer()));
    timer->start(1000);
}

void Widget::game_timer(){
       //qDebug() << "hi";
       ui->
       user->setPos(user->x()+20,user->y());
}
