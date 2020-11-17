#include "GameEngine.h"
#include <QTCore>
#include <QtDebug>

Timer::Timer(){
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT());
}

void Timer::Myslot(){

   qDebug() << "Testing";
}
