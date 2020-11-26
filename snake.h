#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsRectItem>

class Snake: public QGraphicsRectItem{
public:
    Snake();
    void keyPressEvent(QKeyEvent * event);
};

#endif // SNAKE_H
