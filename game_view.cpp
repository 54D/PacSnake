#include <iostream>
#include <sstream>
#include <string>

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QDebug>
#include <QMediaPlayer>

#include "game_view.h"
#include "ui_game_view.h"
#include "main_container.h"
#include "ui_main_container.h"
#include "entities/snake/SnakeBody.h"
#include "entities/snake/Snake.h"
#include "achievements/achievements_container.h"
#include "credits/credits_container.h"
#include "credits/credits_view.h"
#include "ui_achievements_container.h"
#include "GameMap.h"
#include "entities/fruits_and_powerUps/PU_Dash.h"
#include "entities/fruits_and_powerUps/PU_Shield.h"

Snake snakeobj {25, 25, 10};
Snake* s = &snakeobj;

const QString game_view::image_lookup[1][4] {
    {
        ":/assets/sprite/snake-head-up.png",
        ":/assets/sprite/snake-body-vertical.png",
        ":/assets/sprite/snake-corner-up-right.png",
        ":/assets/sprite/snake-tail-up.png"
    }
};

game_view::game_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_view)
{
    timer = new QTimer(this);
    ui->setupUi(this);
    selectSound = new QMediaPlayer();
    selectSound->setMedia(QUrl("qrc:/assets/sound/select.wav"));
}

game_view::~game_view()
{
	delete selectSound;
	delete ui;
    timer->stop();
    delete timer;
}

void game_view::render_game_map(){
    for(int i=0;i<terrain_pixmaps.size();i++){
        scene.removeItem(terrain_pixmaps.at(i));
        delete terrain_pixmaps.at(i);
    }
    terrain_pixmaps.clear();
    for(int r=0;r<game_map->get_num_rows();r++){
        for(int c=0;c<game_map->get_num_cols();c++){
            QString path;
            switch(game_map->get_terrainState(r,c)){
            case GameMap::TerrainState::EMPTY:
                path = ":/assets/sprite/plains.png";
                break;
            case GameMap::TerrainState::BLOCKED:
                path = ":/assets/sprite/mountain.png";
                break;
            default:
                path = ":/assets/sprite/mike_wazowski.png";
                break;
            }
            QGraphicsPixmapItem *img = scene.addPixmap(QPixmap(path));
            QGraphicsRectItem *rect_item = new QGraphicsRectItem();
            rect_item->setRect(0,0,20,100);
            scene.addItem(rect_item);
            img->setOffset(c*32,r*32);
            img->setZValue(5);
            terrain_pixmaps.append(img);
        }
    }
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
	selectSound->play();

    SnakeBody* temp = &snakeobj;
    for (int i = 0; i <= s->get_length(); i++){
        qDebug() << temp->get_col() << temp->get_row();

        int pic_ref = -1;
        if (temp->get_prev() == nullptr) pic_ref = 0;
        if (temp->get_next() == nullptr) pic_ref = 3;
        if (temp->get_prev() != nullptr && temp->get_next() != nullptr){
            if (temp->get_prev()->get_headingDirection()!= temp->get_next()->get_headingDirection()) pic_ref = 2;
        }
        if (pic_ref == -1) pic_ref = 1;
        QPixmap pic(image_lookup[0][pic_ref]);
        QGraphicsPixmapItem *snake_pic = scene.addPixmap(pic);
        temp->register_view(snake_pic);
        snake_pic->setZValue(999);
        snake_pic->setOffset(temp->get_col()*32,temp->get_row()*32);
        temp = temp->get_next();
    }
    timer->start(1000);
    //delete game_map;
    game_map = new GameMap();
    game_map->load_terrian_map(":/game_map/GameMap.txt");
    render_game_map();
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
    ui->graphicsView->show();
    ui->pushButton->setVisible(false);
}

void game_view::on_back_button_clicked()
{
    selectSound->play();
    backButtonPressed = true;
    emit previous_menu();
}

void game_view::setup_view(){
    ui->pushButton->setVisible(true);
    ui->graphicsView->installEventFilter(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(game_timer()));
    connect(timer, SIGNAL(timeout()), this, SLOT(collisionEmitter())); // TODO: remove
    connect(s, SIGNAL(powerUp_added()), this, SLOT(refresh_powerUp_list()));
}

void game_view::reset_view(){
    timer->stop();
    timeCount = 0;
    // TODO: 54D: remove all moving snake
    // scene.clear(); // TODO: this causes issues when reopening the widget.
    ui->graphicsView->removeEventFilter(this);
    disconnect(timer, SIGNAL(timeout()), this, SLOT(game_timer()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(collisionEmitter()));
    disconnect(s, SIGNAL(powerUp_added()), this, SLOT(refresh_powerUp_list()));
}

void game_view::stackedWidgetChanged(int index){
    if(index!=1&&backButtonPressed){
        backButtonPressed = false;
        reset_view();
    }else{
        setup_view();
    }
}

void game_view::refresh_powerUp_list(){
    std::deque<PowerUp*> inventory = s->get_pu_inventory();
    int pos = 0;
    QString path;
    ui->powerUp1Label->setStyleSheet("");
    ui->powerUp2Label->setStyleSheet("");
    ui->powerUp3Label->setStyleSheet("");
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        switch((*it)->get_type()){
        case PowerUp::PowerUpType::DASH:
            path = PU_Dash::get_resourceURI();
            break;
        case PowerUp::PowerUpType::SHIELD:
            path = PU_Shield::get_resourceURI();
            break;
        default:
            qDebug() << "refresh_powerUp_list | Invalid PowerUpType specified";
            break;
        }
        switch(pos){
        case 0: // TODO: set to correct image
            ui->powerUp1Label->setStyleSheet("QLabel { background-image: url(" + path + "); }");
            break;
        case 1:
            ui->powerUp2Label->setStyleSheet("QLabel { background-image: url(" + path + "); }");
            break;
        case 2:
            ui->powerUp3Label->setStyleSheet("QLabel { background-image: url(" + path + "); }");
            break;
        default:
            qDebug() << "refresh_powerUp_list | Invalid position reached";
            break;
        }
        ++pos;
    }
}

static QString parseTime(long seconds){
    long hh = (long)( (seconds / (60*60)) % 24 );
    int mm = (int)( (seconds / (60)) % 60 );
    int ss = (int)( seconds%60 );
    std::ostringstream builder;
    if(hh<10)builder << "0";
    builder << hh << ":";
    if(mm<10)builder << "0";
    builder << mm << ":";
    if(ss<10)builder << "0";
    builder << ss;
    return QString::fromStdString(builder.str());
}

void game_view::game_timer(){
    //qDebug() << "hi";
    //s->increase_length(1);
    s->move_forward();
    SnakeBody* temp = &snakeobj;
    for (int i = 0; i <= s->get_length(); i++){
        temp->get_pixmap()->setOffset(temp->get_col()*32,temp->get_row()*32);
        temp->refresh_pixmap();
        temp = temp->get_next();
    }
    ++timeCount;
    ui->Timer_label->setText(parseTime(timeCount));
    //s->setPos(s->x()+20,s->y());
}

void game_view::collisionEmitter(){
    QList<QGraphicsItem*> empty;
    emit snake_collided(empty);
    /* TODO: 54D: wait for snake_pixmap to be readded into game_view (@bonzi)
    QList<QGraphicsItem*> collisions = ui->graphicsView->scene()->collidingItems(this->snake_pixmap);
    if(!collisions.empty()){
        emit snake_collided(collisions);
    }*/
}
