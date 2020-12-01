#include "game_view.h"
#include "ui_game_view.h"
#include "main_container.h"
#include "ui_main_container.h"
#include "entities/snake/SnakeBody.h"
#include "entities/snake/Snake.h"
#include "achievements/achievements_container.h"
#include "credits_container.h"
#include "credits_view.h"
#include "ui_achievements_container.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <sstream>
#include <string>

Snake snakeobj {100, 100, 10};
Snake* s = &snakeobj;

game_view::game_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_view)
{
    ui->setupUi(this);
    ui->graphicsView->installEventFilter(this);
}

game_view::~game_view()
{
    delete ui;
}

void game_view::keyPressEvent(QKeyEvent *event) {
    qDebug() << event->text();
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

bool game_view::eventFilter(QObject *obj, QEvent *event)
{
    QKeyEvent *keyEvent = NULL;     // event data, if this is a keystroke event
    bool result = false;            // return true to consume the keystroke

    if(event->type() == QEvent::KeyPress){
         keyEvent = dynamic_cast<QKeyEvent*>(event);
         this->keyPressEvent(keyEvent);
         result = true;
    }else if(event->type() == QEvent::KeyRelease){
        keyEvent = dynamic_cast<QKeyEvent*>(event);
        this->keyReleaseEvent(keyEvent);
        result = true;
    }else{                           // standard event processing
        result = QObject::eventFilter(obj,event);
    }
    return result;
}

void game_view::on_pushButton_clicked()
{
    //QGraphicsScene * scene = new QGraphicsScene(0,0,1600,1600,this);
    SnakeBody* temp = &snakeobj;
    for (int i = 0; i <= s->get_length(); i++){
        // TODO: 54D: lines 62 and 63 error: you're adding a SnakeBody *, but addItem only accepts QGraphicsItem *. These lines are commented for build
        //scene.addItem(temp);
        //temp = temp->get_next();
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

void game_view::game_timer(){
       //qDebug() << "hi";
       //s->increase_length(1);
       s->move_forward();
       ++timeCount;
       ui->Timer_label->setText(parseTime(timeCount));
       //s->setPos(s->x()+20,s->y());
}
