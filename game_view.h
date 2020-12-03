#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>

#include <entities/snake/Snake.h>
#include <entities/ghosts/NormalGhost.h>
#include <entities/ghosts/BigGhost.h>
#include <entities/fruits_and_powerUps/Fruit.h>
#include <entities/fruits_and_powerUps/PowerUp.h>
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
	static const QString image_lookup[1][4]; //TODO: move to Snake
	static const int GAME_TICK_UPDATE_TIME = 50;

	static const int NUM_OF_NORMAL_GHOST = 4;
	static const int NUM_OF_BIG_GHOST = 2;
	static const int MAX_MUN_OF_FRUIT = 15;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void on_stackedWidget_currentChanged(int index);
	void update_timer();
    void collisionEmitter();
	void gameTickUpdate();

signals:
    void snake_collided(QList<QGraphicsItem*> collisions);
	void game_over_signal();

private:
    QGraphicsScene scene;
    Ui::game_view *ui;
    void reset_view();
    void render_game_map();
    bool eventFilter(QObject*, QEvent*) override;

	void fruit_instantiation();

	// Detect will the Entity collide with the wall or ghost in it's next movement
	bool next_move_ghost_wall_collision(int row, int col, MovingEntity::Direction headingDirection) const;

	bool is_game_over() const;
	void remove_game_content();

	/* GAME CONTENT */
	GameMap* game_map {nullptr};
	Snake* snake {nullptr};
	QList<NormalGhost*> normalGhosts;
	QList<BigGhost*> bigGhosts;
	QList<Fruit*> fruits;
	QList<PowerUp*> powerups;

	QTimer* gameTickTimer;
	long long gameTickCount {0};
	QTimer* timer;
    long timeCount = 0;

    //QGraphicsPixmapItem *snake_pixmap;
    QList<QGraphicsPixmapItem*> terrain_pixmaps;
	QMediaPlayer* selectSoundEffect;
	QMediaPlayer* hurtSoundEffect;
	QMediaPlayer* deathSoundEffect;
	QMediaPlayer* gameOverSoundEffect;
};

#endif // GAME_VIEW_H
