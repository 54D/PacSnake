#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QWidget>
#include <QGraphicsScene>

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
    void game_timer();

signals:
    void snake_collided(QList<QGraphicsItem*> collisions);

private:
    QGraphicsScene scene;
    Ui::game_view *ui;
    bool eventFilter(QObject*, QEvent*) override;
    void collisionEmitter();

    QGraphicsItem *snake; // TODO: change to Snake class after merging Edward's code
};

#endif // GAME_VIEW_H
