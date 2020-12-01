#include "widget.h"
#include "ui_widget.h"
#include "src/entities/snake/SnakeBody.h"
#include "src/entities/snake/Snake.h"
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

void Widget::Game_start(){

}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
    ui->graphicsView->fitInView(0,0,scene.width(),scene.height(),Qt::KeepAspectRatio);
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
