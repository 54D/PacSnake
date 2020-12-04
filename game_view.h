#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <random>

#include <entities/snake/Snake.h>
#include <entities/ghosts/NormalGhost.h>
#include <entities/ghosts/BigGhost.h>
#include <entities/fruits_and_powerUps/Fruit.h>
#include <entities/fruits_and_powerUps/PowerUp.h>
#include "GameMap.h"
#include "achievements/Stats.h"

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
	static const int GAME_TICK_UPDATE_TIME = 10;

	static const int NUM_OF_NORMAL_GHOST = 4;
	static const int NUM_OF_BIG_GHOST = 2;
	static const int MAX_MUN_OF_FRUIT = 15;
	static const int MAX_NUM_OF_POWERUP = 2;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();
    void on_pauseButton_clicked();
    void on_resetButton_clicked();
    void on_back_button_clicked();
    void stackedWidgetChanged(int index);
    void refresh_powerUp_list();
	void update_timer();
    void update_health();
	void gameTickUpdate();
    void on_volume_control_clicked();
    void on_vol_Slider_valueChanged(int value);

signals:
    void snake_collided(QList<QGraphicsItem*> collisions);
    void previous_menu();
	void game_over_signal();
	void powerUp_added();

private:
    QGraphicsScene scene;
    Ui::game_view *ui;
	int random(int lower, int upper) const;
    bool eventFilter(QObject*, QEvent*) override;
    void setup_view();
    void reset_view();
    void render_game_map();

	void powerUp_instantiation();
	void fruit_instantiation();

	// Detect will the Entity collide with the wall or ghost on its next movement
	bool next_move_ghost_wall_collision(int row, int col, MovingEntity::Direction headingDirection) const;
	// Detect will the Entity collide with the snake on its next movement
	bool next_move_snake_collision(int row, int col, MovingEntity::Direction headingDirection) const;
	// Detect will the Entity collide with the ghost on its next movemebt
	bool next_move_ghost_collision(int row, int col, MovingEntity::Direction headingDirection) const;

	bool is_game_over() const;
	void remove_game_content();

	/* GAME CONTENT */
	GameMap* game_map {nullptr};
	Snake* snake {nullptr};
	QList<NormalGhost*> normalGhosts;
	QList<BigGhost*> bigGhosts;
	QList<Fruit*> fruits;
	QList<PowerUp*> powerups;

	bool allowKeyboardInput {false};
    bool isPlaying = false;
	QTimer* gameTickTimer;
	long long gameTickCount {0};
	QTimer* timer;
    long timeCount = 0;
    bool backButtonPressed = false;

    //QGraphicsPixmapItem *snake_pixmap;
    QList<QGraphicsPixmapItem*> terrain_pixmaps;
	QMediaPlayer* selectSoundEffect;
	QMediaPlayer* eatSoundEffect;
	QMediaPlayer* hurtSoundEffect;
	QMediaPlayer* deathSoundEffect;
	QMediaPlayer* gameOverSoundEffect;

    //achievement
    Stats* curr_stats;
};

#endif // GAME_VIEW_H
