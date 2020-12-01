#include "widget.h"
#include "ui_widget.h"
#include "entities/snake/SnakeBody.h"
#include "entities/snake/Snake.h"
#include "achievements/achievements_container.h"
#include "credits_container.h"
#include "credits_view.h"
#include "ui_achievements_container.h"
#include "GameEngine.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <string>

Snake snakeobj {100.0, 100.0, 10.0};
Snake* s = &snakeobj;

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

void Widget::keyPressEvent(QKeyEvent *event) {
    //qDebug() << event->text();
    if (event->key() == Qt::Key_A){
        s->set_headingDirection(MovingEntity::Direction::WEST);
        s->move_forward();
    }
    else if (event->key() == Qt::Key_D){
        s->set_headingDirection(MovingEntity::Direction::EAST);
        s->move_forward();
    }
    else if (event->key() == Qt::Key_W){
        s->set_headingDirection(MovingEntity::Direction::NORTH);
        s->move_forward();
    }
    else if (event->key() == Qt::Key_S){
        s->set_headingDirection(MovingEntity::Direction::SOUTH);
        s->move_forward();
    }
}

void Widget::on_pushButton_clicked()
{
    //QGraphicsScene * scene = new QGraphicsScene(0,0,1600,1600,this);
    SnakeBody* temp = &snakeobj;
    for (int i = 0; i <= s->get_length(); i++){
        scene.addItem(temp);
        temp = temp->get_next();
    }
    //ui->graphicsView->setScene(scene);
    //start_game();
    //QGraphicsView *view = new QGraphicsView(scene);
    //ui->graphicsView->show();
    /*for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            QGraphicsRectItem *map_bg = new QGraphicsRectItem(j*16,i*16,16,16);
            scene->addItem(map_bg);
        }
    }*/
    //ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
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
       //s->increase_length(1);
       s->move_forward();
       ++timeCount;
       ui->Timer_label->setText(parseTime(timeCount));
       //s->setPos(s->x()+20,s->y());
}

void Widget::bring_back(){
    qDebug() << "bring_back | RECEIVE";
    ui->stackedWidget->setCurrentIndex(0);
}
