#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>


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
    void on_back_button_clicked();
    void stackedWidgetChanged(int index);
    void refresh_powerUp_list();
    void game_timer();
    void collisionEmitter();

signals:
    void snake_collided(QList<QGraphicsItem*> collisions);
    void previous_menu();

private:
    QGraphicsScene scene;
    Ui::game_view *ui;
    bool eventFilter(QObject*, QEvent*) override;
    void setup_view();
    void reset_view();
    void render_game_map();

    GameMap *game_map;
    QTimer *timer;
    long timeCount = 0;
    bool backButtonPressed = false;

    //QGraphicsPixmapItem *snake_pixmap;
    QList<QGraphicsPixmapItem*> terrain_pixmaps;
	QMediaPlayer* selectSound;
};

#endif // GAME_VIEW_H
