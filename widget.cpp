#include "widget.h"
#include "ui_widget.h"
#include "achievements/achievements_container.h"
#include "credits_container.h"
#include "credits_view.h"
#include "ui_achievements_container.h"
#include "ui_achievements.h"
#include "GameEngine.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <string>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(new achievements_container);
    ui->stackedWidget->addWidget(new credits_container);

    connect(ui->stackedWidget->widget(1), SIGNAL(previous_menu()), this, SLOT(bring_back()));
    connect(ui->stackedWidget->widget(2), SIGNAL(previous_menu()), this, SLOT(bring_back()));
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

void Widget::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Widget::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

// TODO: 54D: move global variable elsewhere
long timeCount = 0;

static QString parseTime(long seconds){
    long hh = (long)( (seconds / (60*60)) % 24 );
    int mm = (int)( (seconds / (60)) % 60 );
    int ss = (int)( seconds%60 );
    std::ostringstream builder;
    builder << hh << ":" << mm << ":" << ss;
    // TODO: 54D: if number less than 10, won't display leading 0. Haven't fixed this sorry
    return QString::fromStdString(builder.str());
}

void Widget::game_timer(){
    //qDebug() << "hi";
    user->setPos(user->x()+20,user->y());

    //54D: add timer
    ++timeCount;
    ui->Timer_label->setText(parseTime(timeCount));
    //54D: end of change, hopefully this works.
}

void Widget::bring_back(){
    qDebug() << "bring_back | RECEIVE";
    ui->stackedWidget->setCurrentIndex(0);
}
