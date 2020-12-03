#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QList>
#include <QMediaPlayer>
#include <QTimer>

#include "game_view.h"
#include "ui_game_view.h"
#include "main_container.h"
#include "ui_main_container.h"
#include "entities/MovingEntity.h"
#include "entities/snake/SnakeBody.h"
#include "entities/snake/Snake.h"
#include "entities/ghosts/NormalGhost.h"
#include "entities/ghosts/BigGhost.h"
#include "achievements/achievements_container.h"
#include "credits_container.h"
#include "credits_view.h"
#include "ui_achievements_container.h"
#include "GameMap.h"

const QString game_view::image_lookup[1][4] {
    {
        ":/assets/sprite/snake-head-up.png",
        ":/assets/sprite/snake-body-vertical.png",
        ":/assets/sprite/snake-corner-up-right.png",
        ":/assets/sprite/snake-tail-up.png"
    }
};

game_view::game_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_view)
{
    ui->setupUi(this);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
    timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));

	// Generate ramdom seed
	srand(time(NULL));

	// Gametick for game update
	gameTickTimer = new QTimer(this);
	connect(gameTickTimer, SIGNAL(timeout()), this, SLOT(gameTickUpdate()));

	// Init select sound
	selectSoundEffect = new QMediaPlayer();
	selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));
	hurtSoundEffect = new QMediaPlayer();
	hurtSoundEffect->setMedia(QUrl("qrc:/assets/sound/hurt.wav"));
	deathSoundEffect = new QMediaPlayer();
	deathSoundEffect->setMedia(QUrl("qrc:/assets/sound/death.wav"));
	gameOverSoundEffect = new QMediaPlayer();
	gameOverSoundEffect->setMedia(QUrl("qrc:/assets/sound/gameOver.mp3"));
}

game_view::~game_view()
{
	remove_game_content();

	delete ui;

	timer->stop();
    delete timer;
	gameTickTimer->stop();
	delete gameTickTimer;

	for(int i=0;i<terrain_pixmaps.size();i++){
		scene.removeItem(terrain_pixmaps.at(i));
		delete terrain_pixmaps.at(i);
	}
	terrain_pixmaps.clear();

	delete selectSoundEffect;
	delete hurtSoundEffect;
	delete deathSoundEffect;
	delete gameOverSoundEffect;
}

void game_view::render_game_map(){
	// Clear previous content
	for(int i=0;i<terrain_pixmaps.size();i++){
        scene.removeItem(terrain_pixmaps.at(i));
        delete terrain_pixmaps.at(i);
    }
    terrain_pixmaps.clear();

	// Render game map
    for(int r=0;r<game_map->get_num_rows();r++){
        for(int c=0;c<game_map->get_num_cols();c++){
            QString path;
            switch(game_map->get_terrainState(r,c)){
            case GameMap::TerrainState::EMPTY:
				// qDebug() << "render_game_map | TerrainState::EMPTY";
                path = ":/assets/sprite/plains.png";
                break;
            case GameMap::TerrainState::BLOCKED:
				// qDebug() << "render_game_map | TerrainState::BLOCKED";
                path = ":/assets/sprite/mountain.png";
                break;
            default:
				// qDebug() << "render_game_map | Invalid TerrainState read";
                path = ":/assets/sprite/mike_wazowski.png";
                break;
            }
            QGraphicsPixmapItem *img = scene.addPixmap(QPixmap(path));
            QGraphicsRectItem *rect_item = new QGraphicsRectItem();
            rect_item->setRect(0,0,20,100);
            scene.addItem(rect_item);
            img->setOffset(c*32,r*32);
            img->setZValue(5);
            terrain_pixmaps.append(img);
        }
    }
}

void game_view::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left){
		snake->set_headingDirection(MovingEntity::Direction::WEST);
    }
	else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
		snake->set_headingDirection(MovingEntity::Direction::EAST);
	}
	else if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up){
		snake->set_headingDirection(MovingEntity::Direction::NORTH);
    }
	else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
		snake->set_headingDirection(MovingEntity::Direction::SOUTH);
    }
}

bool game_view::eventFilter(QObject *obj, QEvent *event)
{
    QKeyEvent *keyEvent = NULL;     // event data, if this is a keystroke event
    bool result = false;            // return true to consume the keystroke

    if(event->type() == QEvent::KeyPress){
         keyEvent = dynamic_cast<QKeyEvent*>(event);
         this->keyPressEvent(keyEvent);
         result = true;
    }else if(event->type() == QEvent::KeyRelease){
        keyEvent = dynamic_cast<QKeyEvent*>(event);
        this->keyReleaseEvent(keyEvent);
        result = true;
    }else{                           // standard event processing
        result = QObject::eventFilter(obj,event);
    }
    return result;
}

void game_view::on_pushButton_clicked()
{
	/* Play sound effect */
	selectSoundEffect->play();

	/* Remove previous contents */
	remove_game_content();

	/* GAME MAP */
	// load and render map
	game_map = new GameMap();
	game_map->load_terrian_map(":/game_map/GameMap.txt");
	render_game_map();
	ui->graphicsView->setScene(&scene);
	ui->graphicsView->fitInView(scene.sceneRect(),Qt::KeepAspectRatio);
	ui->graphicsView->show();
	ui->pushButton->setVisible(false);


	/* SNAKE */
	// Init Snake
	// TODO: Stat
	snake = new Snake {20, 25, 10, MovingEntity::Direction::NORTH, 3, 10};
	// UI
	SnakeBody* currentSnakeBody = snake;
	for (int i = 0; i <= snake->get_length(); i++){
        int pic_ref = -1;
		if (currentSnakeBody->get_prev() == nullptr) pic_ref = 0;
		if (currentSnakeBody->get_next() == nullptr) pic_ref = 3;
		if (currentSnakeBody->get_prev() != nullptr && currentSnakeBody->get_next() != nullptr){
			if (currentSnakeBody->get_prev()->get_headingDirection()!= currentSnakeBody->get_next()->get_headingDirection()) pic_ref = 2;
        }
        if (pic_ref == -1) pic_ref = 1;
        QPixmap pic(image_lookup[0][pic_ref]);
        QGraphicsPixmapItem *snake_pic = scene.addPixmap(pic);
		currentSnakeBody->register_view(snake_pic);
        snake_pic->setZValue(999);
		snake_pic->setOffset(currentSnakeBody->get_col()*32,currentSnakeBody->get_row()*32);

		// Record the OCCUPIED state on game_map
		game_map->set_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col(), GameMap::TerrainState::SNAKE_OCCUPIED);
		currentSnakeBody = currentSnakeBody->get_next();
    }

	/* NORMAL GHOSTS */
	// Generate two noraml ghosts
	// TODO : Generate two or more instead of one and set random coord
	for (int i = 0; i < 3; i++) {
		int row, col;
		do {
			row	= rand() % game_map->get_num_rows();
			col = rand() % game_map->get_num_cols();
		} while (game_map->get_terrainState(row, col) != GameMap::TerrainState::EMPTY);
		int upperNGSpeed = static_cast<int>(MovingEntity::MAX_SPEED * 1 / 2);
		int lowerNGSpeed = static_cast<int>(1);
		int speed = rand() % (upperNGSpeed - lowerNGSpeed + 1) + lowerNGSpeed;
		NormalGhost* currentGhost = new NormalGhost {row, col, speed};
		normalGhosts.push_back(currentGhost);

		// Record the OCCUPIED state on game_map
		game_map->set_terrainState(currentGhost->get_row(), currentGhost->get_col(), GameMap::TerrainState::GHOST_OCCUPIED);

		// UI
		QPixmap pic(NormalGhost::image_lookup[i % 5]);
		QGraphicsPixmapItem* ghost_pic = scene.addPixmap(pic);
		currentGhost->register_view(ghost_pic);
		ghost_pic->setZValue(999);
		ghost_pic->setOffset(currentGhost->get_col() * 32, currentGhost->get_row() * 32);
	}

	/* BIG GHOSTS */
	for (int i = 0; i < 2; i++) {
		int row, col;
		do {
			row	= rand() % game_map->get_num_rows();
			col = rand() % game_map->get_num_cols();
		} while ((game_map->get_terrainState(row	, col)		!= GameMap::TerrainState::EMPTY) ||
				 (game_map->get_terrainState(row	, col + 1)	!= GameMap::TerrainState::EMPTY) ||
				 (game_map->get_terrainState(row + 1, col + 1)	!= GameMap::TerrainState::EMPTY) ||
				 (game_map->get_terrainState(row + 1, col)		!= GameMap::TerrainState::EMPTY));
		int upperNGSpeed = static_cast<int>(MovingEntity::MAX_SPEED * 1 / 4);
		int lowerNGSpeed = static_cast<int>(1);
		int speed = rand() % (upperNGSpeed - lowerNGSpeed + 1) + lowerNGSpeed;
		BigGhost* currentGhost = new BigGhost {row, col, speed};
		bigGhosts.push_back(currentGhost);

		// Record the OCCUPIED state on game_map
		game_map->set_terrainState(currentGhost->get_row()		, currentGhost->get_col()	,  GameMap::TerrainState::GHOST_OCCUPIED);
		game_map->set_terrainState(currentGhost->get_row()		, currentGhost->get_col() + 1, GameMap::TerrainState::GHOST_OCCUPIED);
		game_map->set_terrainState(currentGhost->get_row() + 1	, currentGhost->get_col() + 1, GameMap::TerrainState::GHOST_OCCUPIED);
		game_map->set_terrainState(currentGhost->get_row() + 1	, currentGhost->get_col()	,  GameMap::TerrainState::GHOST_OCCUPIED);

		// UI
		int ghostBody_count = 0;
		GhostBody* currentGhostBody = currentGhost;
		do {
			QPixmap pic(BigGhost::image_lookup[ghostBody_count]);
			QGraphicsPixmapItem* ghostBody_pic = scene.addPixmap(pic);
			currentGhostBody->register_view(ghostBody_pic);
			ghostBody_pic->setZValue(999);
			ghostBody_pic->setOffset(currentGhostBody->get_col() * 32, currentGhostBody->get_row() * 32);

			currentGhostBody = currentGhostBody->get_next();
			ghostBody_count++;
		} while (currentGhostBody != currentGhost);
	}

	/* FRUITS */
	// TODO

	/* POWER UPS */
	// TODO

	/* START TIMER */
	// Start gameTickTimer update every 0.1
	gameTickTimer->start(GAME_TICK_UPDATE_TIME);
	// Start timer to update every 1 seconds
    timer->start(1000);
}

void game_view::reset_view(){
	gameTickTimer->stop();
	gameTickCount = 0;
	timer->stop();
    timeCount = 0;
    ui->pushButton->setVisible(true);
	// TODO: ED: if this part is reset everything, remember to avoid memory leak and dangling pointer
}

void game_view::on_stackedWidget_currentChanged(int index){
    if(index==1){
        reset_view();
    }
}

static QString parseTime(long seconds){
    long hh = (long)( (seconds / (60*60)) % 24 );
    int mm = (int)( (seconds / (60)) % 60 );
    int ss = (int)( seconds%60 );
    std::ostringstream builder;
    if(hh<10)builder << "0";
    builder << hh << ":";
    if(mm<10)builder << "0";
    builder << mm << ":";
    if(ss<10)builder << "0";
    builder << ss;
    return QString::fromStdString(builder.str());
}

void game_view::update_timer(){
    ++timeCount;
    ui->Timer_label->setText(parseTime(timeCount));
}

void game_view::collisionEmitter(){
	QList<QGraphicsItem*> empty;
	emit snake_collided(empty);
	/*
	QList<QGraphicsItem*> collisions = ui->graphicsView->scene()->collidingItems(this->snake_pixmap);
	if(!collisions.empty()){
		emit snake_collided(collisions);
	}*/
}

void game_view::gameTickUpdate() {
	gameTickCount++;
	// Overflow prevention
	if (gameTickCount >= LLONG_MAX)
		gameTickCount = 0;

	/* Game Over Condition Checking */
	if(is_game_over()){
		// Stop timer and game update
		gameTickTimer->stop();
		timer->stop();

		qDebug() << "GAME OVER!";
		// Play sound effect
		deathSoundEffect->play();
		gameOverSoundEffect->play();

		emit game_over_signal();
	}

	/* Update movemnt & UI */
	/* Movement will update according to the Entity's speed
	 * As a reference,
	 * If get_speed() == MAX_SPEED,		the Entity will move in every single game tick
	 * If get_speed() == MAX_SPEED / 2, the Entity will move in every 2 game ticks
	 * If get_speed() == 1,				the Entity will move in every MAX_SPEED game ticks (MAX_SPEED * GAME_TICK_UPDATE_TIME ms in real time)
	 *
	 * However, UI will update in every game tick regardless of the Entity's speed
	 */

	/* SNAKE */
	// Movement update
	if ((gameTickCount % static_cast<int>(1.0 / snake->get_speed() * MovingEntity::MAX_SPEED)) == 0) {
		// game_map clear occupied state
		SnakeBody* currentSnakeBody = snake;
		while (currentSnakeBody != nullptr) {
			game_map->set_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col(), GameMap::TerrainState::EMPTY);
			currentSnakeBody = currentSnakeBody->get_next();
		}

		snake->move_forward();

		// game_map update occupied state
		currentSnakeBody = snake;
		while (currentSnakeBody != nullptr) {
			if (game_map->get_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col()) == GameMap::TerrainState::EMPTY) {
				game_map->set_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col(), GameMap::TerrainState::SNAKE_OCCUPIED);
			}
			currentSnakeBody = currentSnakeBody->get_next();
		}
	}
	// UI update
	// TODO
	SnakeBody* currentSnakeBody = snake;
	while (currentSnakeBody != nullptr){
		currentSnakeBody->get_pixmap()->setOffset(currentSnakeBody->get_col() * 32, currentSnakeBody->get_row() * 32);
		currentSnakeBody->refresh_pixmap();
		currentSnakeBody = currentSnakeBody->get_next();
	}

	/* NORMAL GHOSTS */
	for (auto it = normalGhosts.begin(); it != normalGhosts.end(); it++) {
		// Movement update
		if ((gameTickCount % static_cast<int>(1.0 / (*it)->get_speed() * MovingEntity::MAX_SPEED)) == 0) {
			// Update game_map state
			game_map->set_terrainState((*it)->get_row(), (*it)->get_col(), GameMap::TerrainState::EMPTY);

			// Avoid wall collison checking
			MovingEntity::Direction currentHeadingDirection = (*it)->get_headingDirection();
			while (next_move_ghost_wall_collision((*it)->get_row(), (*it)->get_col(), currentHeadingDirection)) {
				// Rotate heading direction of Normal ghost
				switch (currentHeadingDirection) {
					case MovingEntity::Direction::NORTH:currentHeadingDirection	= MovingEntity::Direction::EAST; break;
					case MovingEntity::Direction::EAST:	currentHeadingDirection	= MovingEntity::Direction::SOUTH;break;
					case MovingEntity::Direction::SOUTH:currentHeadingDirection	= MovingEntity::Direction::WEST; break;
					case MovingEntity::Direction::WEST:	currentHeadingDirection = MovingEntity::Direction::NORTH;break;
				}
				(*it)->set_headingDirection(currentHeadingDirection);
			}
			(*it)->move_forward();
			// Update game_map state
			game_map->set_terrainState((*it)->get_row(), (*it)->get_col(), GameMap::TerrainState::GHOST_OCCUPIED);
		}
		// UI
		(*it)->get_pixmap()->setOffset((*it)->get_col() * 32, (*it)->get_row() * 32);
	}

	/* BIG GHOST*/
	for (auto it = bigGhosts.begin(); it != bigGhosts.end(); it++) {
		// Movement update
		if ((gameTickCount % static_cast<int>(1.0 / (*it)->get_speed() * MovingEntity::MAX_SPEED)) == 0) {
			// Update game_map state
			game_map->set_terrainState((*it)->get_row()		, (*it)->get_col()		, GameMap::TerrainState::EMPTY);
			game_map->set_terrainState((*it)->get_row()		, (*it)->get_col() + 1	, GameMap::TerrainState::EMPTY);
			game_map->set_terrainState((*it)->get_row() + 1	, (*it)->get_col() + 1	, GameMap::TerrainState::EMPTY);
			game_map->set_terrainState((*it)->get_row() + 1	, (*it)->get_col()		, GameMap::TerrainState::EMPTY);

			// Avoid wall collison checking
			GhostBody* currentGhostBody = *it;
			do {
				MovingEntity::Direction currentHeadingDirection = currentGhostBody->get_headingDirection();
				while (next_move_ghost_wall_collision(currentGhostBody->get_row(), currentGhostBody->get_col(), currentHeadingDirection))	{
					// Rotate heading direction of whole Big ghost
					switch (currentHeadingDirection) {
						case MovingEntity::Direction::NORTH:currentHeadingDirection	= MovingEntity::Direction::EAST; break;
						case MovingEntity::Direction::EAST:	currentHeadingDirection	= MovingEntity::Direction::SOUTH;break;
						case MovingEntity::Direction::SOUTH:currentHeadingDirection	= MovingEntity::Direction::WEST; break;
						case MovingEntity::Direction::WEST:	currentHeadingDirection = MovingEntity::Direction::NORTH;break;
					}
					(*it)->set_headingDirection(currentHeadingDirection);
				}
				currentGhostBody = currentGhostBody->get_next();
			} while (currentGhostBody != (*it));
			(*it)->move_forward();

			// Update game_map state
			game_map->set_terrainState((*it)->get_row()		, (*it)->get_col()		, GameMap::TerrainState::GHOST_OCCUPIED);
			game_map->set_terrainState((*it)->get_row()		, (*it)->get_col() + 1	, GameMap::TerrainState::GHOST_OCCUPIED);
			game_map->set_terrainState((*it)->get_row() + 1	, (*it)->get_col() + 1	, GameMap::TerrainState::GHOST_OCCUPIED);
			game_map->set_terrainState((*it)->get_row() + 1	, (*it)->get_col()		, GameMap::TerrainState::GHOST_OCCUPIED);

		}
		// UI
		GhostBody* currentGhostBody = (*it);
		do {
			currentGhostBody->get_pixmap()->setOffset(currentGhostBody->get_col() * 32, currentGhostBody->get_row() * 32);

			currentGhostBody = currentGhostBody->get_next();
		} while (currentGhostBody != (*it));
	}

	/* Collision checking */
	// Check if snake collide with wall
	if (game_map->get_terrainState(snake->get_row(), snake->get_col()) == GameMap::TerrainState::BLOCKED) {
		snake->set_health(0);
		qDebug() << "Snake hits the wall!";
		return;
	}

	// Check if snake collide with itself
	for (SnakeBody* currentSnakeBody = snake->get_next(); currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
		if (snake->get_row() == currentSnakeBody->get_row() && snake->get_col() == currentSnakeBody->get_col()) {
			snake->set_health(0);
			qDebug() << "Snake hits itslef";
			return;
		}
	}

	// Check if snake (head) collide with ghosts
	if (game_map->get_terrainState(snake->get_row(), snake->get_col()) == GameMap::TerrainState::GHOST_OCCUPIED) {
		snake->set_health(0);
		qDebug() << "Snake (head) hits a ghost!";
		return;
	}

	// Check if snake (body) collide with ghosts
	for (SnakeBody* currentSnakeBody = snake->get_next(); currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
		if (game_map->get_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col()) == GameMap::TerrainState::GHOST_OCCUPIED) {
			// Play sound effecct
			if (hurtSoundEffect->state() == QMediaPlayer::PlayingState) {
				hurtSoundEffect->setPosition(0);
			}
			else if (hurtSoundEffect->state() == QMediaPlayer::StoppedState) {
				hurtSoundEffect->play();
			}
			qDebug() << "Ouch! That's hurt!";
			qDebug() << "Health" << snake->get_health() << snake->get_max_health();
			snake->set_relative_health(-1);
			for (SnakeBody* removeSnakeBody = currentSnakeBody; removeSnakeBody != nullptr; removeSnakeBody = removeSnakeBody->get_next()) {
				game_map->set_terrainState(removeSnakeBody->get_row(), removeSnakeBody->get_col(), GameMap::TerrainState::EMPTY);
				scene.removeItem(removeSnakeBody->get_pixmap());
			}
			snake->remove_tail(currentSnakeBody->get_prev());
			return;
		}
	}
	// More stuff TODO on collision checking :^ )
}

bool game_view::is_game_over() const {
	if (snake->get_health() <= 0)
		return true;
	return false;
}

bool game_view::next_move_ghost_wall_collision(int row, int col, MovingEntity::Direction headingDirection) const {
	switch(headingDirection) {
		case MovingEntity::Direction::NORTH:row -= 1;	break;
		case MovingEntity::Direction::EAST:	col += 1;	break;
		case MovingEntity::Direction::SOUTH:row += 1;	break;
		case MovingEntity::Direction::WEST:	col -= 1;	break;
	}
	if (game_map->get_terrainState(row, col) == GameMap::TerrainState::BLOCKED ||
		game_map->get_terrainState(row, col) == GameMap::TerrainState::GHOST_OCCUPIED )
		return true;
	return false;
}

void game_view::remove_game_content() {
	delete game_map;
	game_map = nullptr;

	delete snake;
	snake = nullptr;

	for (auto it = normalGhosts.begin(); it != normalGhosts.end(); it++) {
		delete (*it);
	}
	normalGhosts.clear();

	for (auto it = bigGhosts.begin(); it != bigGhosts.end(); it++) {
		delete (*it);
	}
	bigGhosts.clear();

	for (auto it = fruits.begin(); it != fruits.end(); it++) {
		delete (*it);
	}
	fruits.clear();

	for (auto it = powerups.begin(); it != powerups.end(); it++) {
		delete (*it);
	}
	powerups.clear();
}
