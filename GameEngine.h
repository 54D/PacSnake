#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QtCore>

class Timer : public QObject{
    Q_OBJECT

public:
    Timer();
    QTimer *timer;

public slots:
    void Myslot();
};




#endif // GAMEENGINE_H
