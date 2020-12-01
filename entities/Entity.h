#ifndef ENTITY_H_
#define ENTITY_H_

#include <QObject>
#include <QGraphicsPixmapItem>

class Entity : public QObject {
    Q_OBJECT

public:
    virtual ~Entity();

    int get_row() const;
    int get_col() const;

    void set_row(int row);
    void set_col(int col);
    void set_coordinate(int row, int col);
    void set_relative_coordinate(int delta_row, int delta_col);
    QPixmap get_pixmap();

protected:
    Entity();
    Entity(int row, int col);

    int row, col;

    QPixmap pixmap;
};


#endif /* ENTITY_H_ */
