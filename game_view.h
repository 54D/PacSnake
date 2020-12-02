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
    static const QString image_lookup[1][4];

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void game_timer();

signals:
    void snake_collided(QList<QGraphicsItem*> collisions);

private:
    QGraphicsScene scene;
    Ui::game_view *ui;
    void render_game_map(GameMap *game_map);
    bool eventFilter(QObject*, QEvent*) override;
    void collisionEmitter();

    //QGraphicsPixmapItem *snake_pixmap;
    QList<QGraphicsPixmapItem*> terrain_pixmaps;
    //QList<QGraphicsPixmapItem*> snake_pix;
};

#endif // GAME_VIEW_H
