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
#include "achievements/Achievement.h"

namespace Ui {
class game_view;
}

class game_view : public QWidget
{
    Q_OBJECT

public:

	/**
	 * Constructor for game_view.
	 * @param	parent			This constructor must accept its parent node as a parameter as specified by Qt.
	 * @param	achievement		The achievement object to track the data.
	 */
	game_view(QWidget *parent = nullptr, Achievement *achievement = nullptr);
	/**
	 * Destructor for game_view.
	 */
	~game_view();

	/**
	 * Public const. 
	 */
	static const int GAME_TICK_UPDATE_TIME = 10;

	static const int NUM_OF_NORMAL_GHOST = 4;
	static const int NUM_OF_BIG_GHOST = 2;
	static const int MAX_MUN_OF_FRUIT = 15;
	static const int MAX_NUM_OF_POWERUP = 2;

protected:

	/**
	 * Handler for key presses
	 * @param	event	The event to process.
	 */
    void keyPressEvent(QKeyEvent *event) override;

private slots:

	/**
	 * Handler for `pushButton` which starts the game.
	 */
    void on_pushButton_clicked();
	/**
	 * Handler for `pauseButton` which toggles pause status.
	 */
    void on_pauseButton_clicked();
	/**
	 * Handler for `resetButton` which resets the game map.
	 */
    void on_resetButton_clicked();
	/**
	 * Handler for `back_button` which brings `stackedWidget` back to main menu.
	 */
    void on_back_button_clicked();
	/**
	 * Handler for `stackedWidget` switching to the game view.
	 */
    void stackedWidgetChanged(int index);
	/**
	 * Refreshes the powerup inventory.
	 * Called when there is a potential change in powerup inventory.
	 */
    void refresh_powerUp_list();
	/**
	 * Updates the timer.
	 * Called when the timer needs to be updated.
	 */
	void update_timer();
	/**
	 * Updates the health view.
	 * Called when there is a potential change in health.
	 */
	void update_health();
	/**
	 * Updates the game map.
	 * Called at every game tick advance.
	 */
	void gameTickUpdate();
	/**
	 * Handler for `volume_control` which toggles the visibility for volume slider.
	 */
    void on_volume_control_clicked();
	/**
	 * Handler for `vol_Slider` which controls the volume of sound effects.
	 */
    void on_vol_Slider_valueChanged(int value);

signals:

	/**
	 * Signal fired when previous menu navigation has been requested.
	 */
    void previous_menu();
	/**
	 * Signal fired when the game over conditions are reached.
	 */
	void game_over_signal();
	/**
	 * Signal fired when a powerup is added to the inventory.
	 */
	void powerUp_added();

private:

	/**
	 * Generates a random number with bounds `[lower,upper)`
	 * @param	lower	Lower bound, inclusive.
	 * @param	upper	Upper bound, exclusive.
	 */
	int random(int lower, int upper) const;
	/**
	 * Standard Qt Event Filter. Used to filter additional keypress events that may be consumed by child widgets.
	 * @param	obj		Object captured.
	 * @param	event	Event captured.
	 */
	bool eventFilter(QObject *obj, QEvent *event) override;
	/**
	 * Sets up the entire UI.
	 */
    void setup_view();
	/**
	 * Resets the entire UI.
	 */
    void reset_view();
	/**
	 * Populates the game area with images.
	 */
    void render_game_map();

	/**
	 * Instantiates a powerup.
	 */
	void powerUp_instantiation();
	/**
	 * Instantiates a fruit.
	 */
	void fruit_instantiation();
	/**
	 * Instantiates a normal ghost.
	 */
	void normalGhost_instantiation();
	/**
	 * Instantiates a big ghost.
	 */
	void bigGhost_instantiation();

	/**
	 * Detects whether an Entity will collide with the wall or a ghost on its next movement.
	 * @param	row					Current row location.
	 * @param	col					Current column location.
	 * @param	headingDirection	Current heading direction.
	 * @return	Prediction result.
	 */
	bool next_move_ghost_wall_collision(int row, int col, MovingEntity::Direction headingDirection) const;
	/**
	 * Detects whether an Entity will collide with the snake on its next movement.
	 * @param	row					Current row location.
	 * @param	col					Current column location.
	 * @param	headingDirection	Current heading direction.
	 * @return	Prediction result.
	 */
	bool next_move_snake_collision(int row, int col, MovingEntity::Direction headingDirection) const;
	/**
	 * Detects whether an Entity will collide with a ghost on its next movement.
	 * @param	row					Current row location.
	 * @param	col					Current column location.
	 * @param	headingDirection	Current heading direction.
	 * @return	Prediction result.
	 */
	bool next_move_ghost_collision(int row, int col, MovingEntity::Direction headingDirection) const;

	/**
	 * Checks if the game over conditions have been reached.
	 * @return	Whether the game is over.
	 */
	bool is_game_over() const;
	/**
	 * Removes content in the game view.
	 */
	void remove_game_content();

	/* GAME CONTENT */
	QGraphicsScene scene;
	Ui::game_view *ui;

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

    QList<QGraphicsPixmapItem*> terrain_pixmaps;
	QMediaPlayer* selectSoundEffect;
	QMediaPlayer* eatSoundEffect;
	QMediaPlayer* hurtSoundEffect;
	QMediaPlayer* deathSoundEffect;
	QMediaPlayer* gameOverSoundEffect;

    Stats* curr_stats;

};

#endif // GAME_VIEW_H
