#include "snake.h"

#include <QKeyEvent>

Snake::Snake(){
    this->setRect(0,0,20,100);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();
}

void Snake::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        setPos(x()-20,y());
    }
    else if (event->key() == Qt::Key_Right){
        setPos(x()+20,y());
    }
    else if (event->key() == Qt::Key_Up){
        setPos(x(),y()-20);
    }
    else if (event->key() == Qt::Key_Down){
        setPos(x(),y()+20);
    }
}
