#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QWidget>
#include <QGraphicsScene>

#include "GameMap.h"

namespace Ui {
class game_view;
}

class game_view : public QWidget
{
    Q_OBJECT

public:
    game_view(QWidget *parent = nullptr);
    ~game_view();
    void Game_start();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void on_main_container_currentChanged(int index);
    void game_timer();
    void collisionEmitter();

signals:
    void snake_collided(QList<QGraphicsItem*> collisions);

private:
    QGraphicsScene scene;
    Ui::game_view *ui;
    void reset_view();
    void render_game_map();
    bool eventFilter(QObject*, QEvent*) override;

    GameMap *game_map;
    QTimer *timer;

    QGraphicsPixmapItem *snake_pixmap;
    QList<QGraphicsPixmapItem*> terrain_pixmaps;
};

#endif // GAME_VIEW_H
