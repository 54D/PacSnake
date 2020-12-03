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

#include "achievements/Stats.h"
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
#include "credits/credits_container.h"
#include "credits/credits_view.h"
#include "ui_achievements_container.h"
#include "GameMap.h"
#include "entities/fruits_and_powerUps/PU_Dash.h"
#include "entities/fruits_and_powerUps/PU_Shield.h"

// util
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

const QString game_view::image_lookup[4][4] {
    {
        ":/assets/sprite/snake-head-up.png",
        ":/assets/sprite/snake-head-down.png",
        ":/assets/sprite/snake-head-left.png",
        ":/assets/sprite/snake-head-right.png",
    },
    {
        ":/assets/sprite/snake-body-vertical.png",
        ":/assets/sprite/snake-body-horizontal.png",
    },
    {
        ":/assets/sprite/snake-corner-up-left.png",
        ":/assets/sprite/snake-corner-up-right.png",
        ":/assets/sprite/snake-corner-down-left.png",
        ":/assets/sprite/snake-corner-down-right.png",
    },
    {
        ":/assets/sprite/snake-tail-up.png",
        ":/assets/sprite/snake-tail-down.png",
        ":/assets/sprite/snake-tail-left.png",
        ":/assets/sprite/snake-tail-right.png",
    }
};

game_view::game_view(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game_view)
{
    timer = new QTimer(this);
    ui->setupUi(this);

    // Generate ramdom seed
    srand(time(NULL));

    // Gametick for game update
    gameTickTimer = new QTimer(this);
    connect(gameTickTimer, SIGNAL(timeout()), this, SLOT(gameTickUpdate()));

    // Init select sound
    selectSoundEffect = new QMediaPlayer();
    selectSoundEffect->setMedia(QUrl("qrc:/assets/sound/select.wav"));
    selectSoundEffect->setVolume(50);
    hurtSoundEffect = new QMediaPlayer();
    hurtSoundEffect->setMedia(QUrl("qrc:/assets/sound/hurt.wav"));
    hurtSoundEffect->setVolume(50);
    deathSoundEffect = new QMediaPlayer();
    deathSoundEffect->setMedia(QUrl("qrc:/assets/sound/death.wav"));
    deathSoundEffect->setVolume(50);
    gameOverSoundEffect = new QMediaPlayer();
    gameOverSoundEffect->setMedia(QUrl("qrc:/assets/sound/gameOver.mp3"));
    gameOverSoundEffect->setVolume(50);
    ui->volume_control->setVisible(true);
    ui->volume_control->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    QPixmap pixmap(":/assets/volume_control.png");
    QIcon ButtonIcon(pixmap);
    ui->volume_control->setIcon(pixmap);
    ui->volume_control->setIconSize(QSize(32,32));
    ui->vol_Slider->setVisible(false);

    Stats gamestats;
    curr_stats = &gamestats;
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
                path = ":/assets/sprite/plains.png";
                break;
            case GameMap::TerrainState::BLOCKED:
                path = ":/assets/sprite/mountain.png";
                break;
            default:
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

void game_view::fruit_instantiation() {
    int row, col;
    do {
        row	= rand() % game_map->get_num_rows();
        col = rand() % game_map->get_num_cols();
    } while (game_map->get_terrainState(row, col) != GameMap::TerrainState::EMPTY);
    Fruit* fruit_temp = new Fruit {row, col};
    game_map->set_terrainState(fruit_temp->get_row(), fruit_temp->get_col(), GameMap::TerrainState::FRUIT_OCCUPIED);
    fruits.push_back(fruit_temp);

    // Init UI
    QPixmap pic(Fruit::image_lookup[rand() % 5]);
    QGraphicsPixmapItem* fruit_pic = scene.addPixmap(pic);
    fruit_temp->register_view(fruit_pic);
    fruit_pic->setZValue(998);
    fruit_pic->setOffset(fruit_temp->get_col() * 32, fruit_temp->get_row() * 32);
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
    snake = new Snake {20, 25};
    // Init UI
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
    for (int i = 0; i < NUM_OF_NORMAL_GHOST; i++) {
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

        // Init UI
        QPixmap pic(NormalGhost::image_lookup[rand() % 5]);
        QGraphicsPixmapItem* ghost_pic = scene.addPixmap(pic);
        currentGhost->register_view(ghost_pic);
        ghost_pic->setZValue(999);
        ghost_pic->setOffset(currentGhost->get_col() * 32, currentGhost->get_row() * 32);
    }

    /* BIG GHOSTS */
    for (int i = 0; i < NUM_OF_BIG_GHOST; i++) {
        int row, col;
        do {
            row	= rand() % game_map->get_num_rows();
            col = rand() % game_map->get_num_cols();
        } while ((game_map->get_terrainState(row	, col)		!= GameMap::TerrainState::EMPTY) ||
                 (game_map->get_terrainState(row	, col + 1)	!= GameMap::TerrainState::EMPTY) ||
                 (game_map->get_terrainState(row + 1, col + 1)	!= GameMap::TerrainState::EMPTY) ||
                 (game_map->get_terrainState(row + 1, col)		!= GameMap::TerrainState::EMPTY));
        int upperBGSpeed = static_cast<int>(MovingEntity::MAX_SPEED * 1 / 4);
        int lowerBGSpeed = static_cast<int>(1);
        int speed = rand() % (upperBGSpeed - lowerBGSpeed + 1) + lowerBGSpeed;
        BigGhost* currentGhost = new BigGhost {row, col, speed};
        bigGhosts.push_back(currentGhost);

        // Record the OCCUPIED state on game_map
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                game_map->set_terrainState(currentGhost->get_row() + i, currentGhost->get_col() + j, GameMap::TerrainState::GHOST_OCCUPIED);
            }
        }

        // Init UI
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
    for (int i = 0; i < MAX_MUN_OF_FRUIT; i++) {
        fruit_instantiation();
    }

    /* POWER UPS */
    // TODO
    connect(snake, SIGNAL(powerUp_added()), this, SLOT(refresh_powerUp_list()));

    /* START TIMER */
    // Start gameTickTimer update every GAME_TICK_UPDATE_TIME ms
    gameTickTimer->start(GAME_TICK_UPDATE_TIME);
    // Start timer to update every 1 seconds
    timer->start(1000);
    isPlaying = true;
    ui->pushButton->setVisible(false);
    ui->pauseButton->setVisible(true);
    ui->resetButton->setVisible(true);
}

void game_view::on_pauseButton_clicked(){
    if(isPlaying){
        ui->pauseButton->setText("Resume");
    }else{
        ui->pauseButton->setText("Pause");
    }
    isPlaying = !isPlaying;
    // TODO: 54D: pausing functionality is not implemented
}

void game_view::on_resetButton_clicked(){
    isPlaying = false;
    gameTickTimer->stop();
    gameTickCount = 0;
    timer->stop();
    timeCount = 0;
    ui->pushButton->setVisible(true);
    ui->pauseButton->setText("Pause");
    ui->pauseButton->setVisible(false);
    ui->resetButton->setVisible(false);
    ui->Timer_label->setText(parseTime(timeCount));
}

void game_view::on_back_button_clicked()
{
    selectSoundEffect->play();
    backButtonPressed = true;
    emit previous_menu();
}

void game_view::setup_view(){
    ui->pauseButton->setText("Pause");
    ui->pushButton->setVisible(true);
    ui->pauseButton->setVisible(false);
    ui->resetButton->setVisible(false);
    ui->graphicsView->installEventFilter(this);
    update_health();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));
}

void game_view::reset_view(){
    isPlaying = false;
    gameTickTimer->stop();
    gameTickCount = 0;
    timer->stop();
    timeCount = 0;
    // TODO: 54D: remove all moving snake
    // scene.clear(); // TODO: this causes issues when reopening the widget.
    ui->graphicsView->removeEventFilter(this);
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    if(snake!=nullptr){
        disconnect(snake, SIGNAL(powerUp_added()), this, SLOT(refresh_powerUp_list()));
    }
}

void game_view::stackedWidgetChanged(int index){
    if(index!=1&&backButtonPressed){
        backButtonPressed = false;
        reset_view();
    }else{
        setup_view();
    }
}

void game_view::refresh_powerUp_list(){
    std::deque<PowerUp*> inventory = snake->get_pu_inventory();
    int pos = 0;
    QString path;
    ui->powerUp1Label->setStyleSheet("");
    ui->powerUp2Label->setStyleSheet("");
    ui->powerUp3Label->setStyleSheet("");
    for (auto it = inventory.begin(); it != inventory.end(); it++) {
        switch((*it)->get_type()){
        case PowerUp::PowerUpType::DASH:
            path = PU_Dash::get_resourceURI();
            break;
        case PowerUp::PowerUpType::SHIELD:
            path = PU_Shield::get_resourceURI();
            break;
        default:
            qDebug() << "refresh_powerUp_list | Invalid PowerUpType specified";
            break;
        }
        switch(pos){
        case 0: // TODO: set to correct image
            ui->powerUp1Label->setStyleSheet("QLabel { background-image: url(" + path + "); }");
            break;
        case 1:
            ui->powerUp2Label->setStyleSheet("QLabel { background-image: url(" + path + "); }");
            break;
        case 2:
            ui->powerUp3Label->setStyleSheet("QLabel { background-image: url(" + path + "); }");
            break;
        default:
            qDebug() << "refresh_powerUp_list | Invalid position reached";
            break;
        }
        ++pos;
    }
}

void game_view::update_timer(){
    ++timeCount;
    ui->Timer_label->setText(parseTime(timeCount));
}

void game_view::update_health(){
    if(snake!=nullptr&&snake->get_health()>0){
        ui->heart1Label->setStyleSheet("QLabel { background-image: url(:/assets/sprite/full-health.png); }");
    }else{
        ui->heart1Label->setStyleSheet("QLabel { background-image: url(:/assets/sprite/empty-health.png); }");
    }
    if(snake!=nullptr&&snake->get_health()>1){
        ui->heart2Label->setStyleSheet("QLabel { background-image: url(:/assets/sprite/full-health.png); }");
    }else{
        ui->heart2Label->setStyleSheet("QLabel { background-image: url(:/assets/sprite/empty-health.png); }");
    }
    if(snake!=nullptr&&snake->get_health()>2){
        ui->heart3Label->setStyleSheet("QLabel { background-image: url(:/assets/sprite/full-health.png); }");
    }else{
        ui->heart3Label->setStyleSheet("QLabel { background-image: url(:/assets/sprite/empty-health.png); }");
    }
}

void game_view::gameTickUpdate() {
    /*
     * This function is called everyime game tick
     * The function does the following procedure :
     * - Game over condition
     * - Move the Entity according to their speed
     * - Update Entity's UI
     * - Collision checking
     */
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
        qDebug() << "Fruits eaten:" << snake->get_num_fruits_eaten();
        qDebug() << "Survival time:" << timeCount;
        qDebug() << "Fruits eaten:" << snake->get_longest_length();
        curr_stats->update_fruits_eaten(snake->get_num_fruits_eaten());
        curr_stats->update_survival_time(timeCount);
        curr_stats->update_snake_length(snake->get_longest_length());


        // Play sound effect
        deathSoundEffect->play();
        gameOverSoundEffect->play();

        emit game_over_signal();
    }
    else {
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
            for (SnakeBody* currentSnakeBody = snake; currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
                game_map->set_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col(), GameMap::TerrainState::EMPTY);
            }

            snake->move_forward();

            // game_map update occupied state
            for (SnakeBody* currentSnakeBody = snake; currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
                if (game_map->get_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col()) == GameMap::TerrainState::EMPTY) {
                    game_map->set_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col(), GameMap::TerrainState::SNAKE_OCCUPIED);
                }
            }
        }
        // UI update
        // TODO
        for (SnakeBody* currentSnakeBody = snake; currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
            currentSnakeBody->get_pixmap()->setOffset(currentSnakeBody->get_col() * 32, currentSnakeBody->get_row() * 32);
            currentSnakeBody->refresh_pixmap();
            curr_stats->add_in_game_distance();
        }
        update_health();

        /* NORMAL GHOSTS */
        for (auto it = normalGhosts.begin(); it != normalGhosts.end(); it++) {
            // Movement update
            if ((gameTickCount % static_cast<int>(1.0 / (*it)->get_speed() * MovingEntity::MAX_SPEED)) == 0) {
                // Update game_map state
                game_map->set_terrainState((*it)->get_row(), (*it)->get_col(), GameMap::TerrainState::EMPTY);

                // Avoid wall collison checking
                while (next_move_ghost_wall_collision((*it)->get_row(), (*it)->get_col(), (*it)->get_headingDirection())) {
                    // Rotate heading direction of Normal ghost
                    (*it)->set_headingDirection((*it)->get_rotated_headingDirection());
                }

                // Show Fruits on game_map again if the Ghost was stepped on it
                int prev_row, prev_col;
                bool isFruitCoord = false;
                for (auto f_it = fruits.begin(); f_it != fruits.end() && !isFruitCoord; f_it++) {
                    if ((*f_it)->get_row() == (*it)->get_row() && (*f_it)->get_col() == (*it)->get_col()) {
                        isFruitCoord = true;
                        prev_row = (*f_it)->get_row();
                        prev_col = (*f_it)->get_col();
                    }
                }

                // Move forward
                (*it)->move_forward();

                // Show Fruits
                if (isFruitCoord) {
                    game_map->set_terrainState(prev_row, prev_col, GameMap::TerrainState::FRUIT_OCCUPIED);
                }

                // Update game_map state
                game_map->set_terrainState((*it)->get_row(), (*it)->get_col(), GameMap::TerrainState::GHOST_OCCUPIED);
            }
            // UI update
            (*it)->get_pixmap()->setOffset((*it)->get_col() * 32, (*it)->get_row() * 32);
        }


        /* BIG GHOST*/
        for (auto it = bigGhosts.begin(); it != bigGhosts.end(); it++) {
            // Movement update
            if ((gameTickCount % static_cast<int>(1.0 / (*it)->get_speed() * MovingEntity::MAX_SPEED)) == 0) {
                // Update game_map state
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        game_map->set_terrainState((*it)->get_row() + i, (*it)->get_col() + j, GameMap::TerrainState::EMPTY);
                    }
                }

                // Avoid wall collison checking
                // Check each part of BigGhost's GhostBody
                GhostBody* currentGhostBody = *it;
                do {
                    while (next_move_ghost_wall_collision(currentGhostBody->get_row(), currentGhostBody->get_col(), (*it)->get_headingDirection()))	{
                        // Rotate heading direction of whole Big ghost
                        (*it)->set_headingDirection((*it)->get_rotated_headingDirection());
                    }
                    currentGhostBody = currentGhostBody->get_next();
                } while (currentGhostBody != (*it));

                // Show Fruits on game_map again if the Ghost was stepped on it
                int prev_row, prev_col;
                bool isFruitCoord = false;
                for (auto f_it = fruits.begin(); f_it != fruits.end() && !isFruitCoord; f_it++) {
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                            if ((*f_it)->get_row() == ((*it)->get_row() + i) && (*f_it)->get_col() == ((*it)->get_col() + j)) {
                                isFruitCoord = true;
                                prev_row = (*f_it)->get_row();
                                prev_col = (*f_it)->get_col();
                            }
                        }
                    }
                }

                // Move forward
                (*it)->move_forward();

                // Show Fruits
                if (isFruitCoord) {
                    game_map->set_terrainState(prev_row, prev_col, GameMap::TerrainState::FRUIT_OCCUPIED);
                }

                // Update game_map state
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 2; j++) {
                        game_map->set_terrainState((*it)->get_row() + i, (*it)->get_col() + j, GameMap::TerrainState::GHOST_OCCUPIED);
                    }
                }
            }
            // UI Update
            GhostBody* currentGhostBody = (*it);
            do {
                currentGhostBody->get_pixmap()->setOffset(currentGhostBody->get_col() * 32, currentGhostBody->get_row() * 32);
                currentGhostBody = currentGhostBody->get_next();
            } while (currentGhostBody != (*it));
        }


        /* Collision checking */
        // Check if snake (head) collide with fruit
        if (game_map->get_terrainState(snake->get_row(), snake->get_col()) == GameMap::TerrainState::FRUIT_OCCUPIED) {
            int collideFruitIndex = -1;
            Fruit* fruit_temp = nullptr;
            // Search for the Fruit being collided
            for (int i = 0; i < fruits.size() && collideFruitIndex == -1; i++) {
                if (fruits.at(i)->get_row() == snake->get_row() && fruits.at(i)->get_col() == snake->get_col()) {
                    collideFruitIndex = i;
                    fruit_temp = fruits.at(i);
                }
            }
            // If the snake collide with the fruit
            if (collideFruitIndex != -1) {
                // Remove fruit from map
                game_map->set_terrainState(fruit_temp->get_row(), fruit_temp->get_col(), GameMap::TerrainState::EMPTY);
                scene.removeItem(fruit_temp->get_pixmap());
                delete fruit_temp;
                fruits.removeAt(collideFruitIndex);


                snake->increase_num_fruits_eaten(1);
                snake->increase_length(1);
                // Update UI
                SnakeBody* lastSnakeBody = snake;
                while (lastSnakeBody->get_next() != nullptr) {
                    lastSnakeBody = lastSnakeBody->get_next();
                }
                QPixmap pic(image_lookup[0][3]);
                QGraphicsPixmapItem *snake_pic = scene.addPixmap(pic);
                lastSnakeBody->register_view(snake_pic);
                snake_pic->setZValue(999);
                snake_pic->setOffset(lastSnakeBody->get_col()*32, lastSnakeBody->get_row()*32);
                // Refresh UI
                // TODO
                for (SnakeBody* currentSnakeBody = snake; currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
                    currentSnakeBody->refresh_pixmap();
                }


                // Update snake speed
                snake->set_speed(snake->calculate_level_speed());
                qDebug() << "Fruit eaten: " << snake->get_num_fruits_eaten();

                // Generate a new fruit on map
                fruit_instantiation();
            }
            else {
                qDebug() << "[ERROR] Collided fruit not found!";
            }
        }

        // Check if snake collide with PowerUp
        // TODO

        // Check if snake collide with wall
        if (game_map->get_terrainState(snake->get_row(), snake->get_col()) == GameMap::TerrainState::BLOCKED) {
            // Instant death
            if (snake->get_length() > snake->get_longest_length()){
                snake->set_longest_length(snake->get_length());
            }
            snake->set_health(0);
            qDebug() << "Snake hits the wall!";
            return;
        }

        // Check if snake collide with itself
        for (SnakeBody* currentSnakeBody = snake->get_next(); currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
            if (snake->get_row() == currentSnakeBody->get_row() && snake->get_col() == currentSnakeBody->get_col()) {
                // Instant death
                if (snake->get_length() > snake->get_longest_length()){
                    snake->set_longest_length(snake->get_length());
                }
                snake->set_health(0);
                qDebug() << "Snake hits itslef";
                return;
            }
        }

        // Check if snake (head) collide with ghosts
        if (game_map->get_terrainState(snake->get_row(), snake->get_col()) == GameMap::TerrainState::GHOST_OCCUPIED) {
            // Instant death
            if (snake->get_length() > snake->get_longest_length()){
                snake->set_longest_length(snake->get_length());
            }
            snake->set_health(0);
            qDebug() << "Snake (head) hits a ghost!";
            return;
        }

        // Check if snake (body) collide with ghosts
        for (SnakeBody* currentSnakeBody = snake->get_next(); currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
            if (game_map->get_terrainState(currentSnakeBody->get_row(), currentSnakeBody->get_col()) == GameMap::TerrainState::GHOST_OCCUPIED) {
                //Update max length
                if (snake->get_length() > snake->get_longest_length()){
                    snake->set_longest_length(snake->get_length());
                }
                // Play sound effecct
                if (hurtSoundEffect->state() == QMediaPlayer::PlayingState) {
                    hurtSoundEffect->setPosition(0);
                }
                else if (hurtSoundEffect->state() == QMediaPlayer::StoppedState) {
                    hurtSoundEffect->play();
                }

                qDebug() << "Snake (body) hits a ghost!";
                snake->set_relative_health(-1);
                qDebug() << "Health" << snake->get_health() << snake->get_max_health();

                // Search for the Ghost and change its headingDirection to avoid multiple hits
                GhostBody* collidedGhostBody = nullptr;
                for (auto it = normalGhosts.begin(); it != normalGhosts.end() && collidedGhostBody == nullptr; it++) {
                    if ((*it)->get_row() == currentSnakeBody->get_row() && (*it)->get_col() == currentSnakeBody->get_col()) {
                        collidedGhostBody = *it;
                        (*it)->set_headingDirection((*it)->get_rotated_headingDirection());
                        qDebug() << "DIRECTION CHANGED!";
                    }
                }
                for (auto it = bigGhosts.begin(); it != bigGhosts.end() && collidedGhostBody == nullptr; it++) {
                    GhostBody* currentGhostsBody = (*it);
                    do {
                        if (currentGhostsBody->get_row() == currentSnakeBody->get_row() && currentGhostsBody->get_col() == currentSnakeBody->get_col()) {
                            collidedGhostBody = *it;
                            (*it)->set_headingDirection((*it)->get_rotated_headingDirection());
                            qDebug() << "DIRECTION CHANGED!";
                        }
                    } while (currentGhostsBody != (*it) && collidedGhostBody == nullptr);
                }
                if (collidedGhostBody == nullptr) {
                    qDebug() << "[ERROR] Collided GhostBody not found!";
                }


                // Update game_map state, the SnakeBody being cut is reset to TrrrainState::EMPTY
                // Note that the collided part is not updated as the GhostBody is occupying the game_map already
                scene.removeItem(currentSnakeBody->get_pixmap());
                for (SnakeBody* removeSnakeBody = currentSnakeBody->get_next(); removeSnakeBody != nullptr; removeSnakeBody = removeSnakeBody->get_next()) {
                    // Update the game_map state of the remaining SnakeBody
                    game_map->set_terrainState(removeSnakeBody->get_row(), removeSnakeBody->get_col(), GameMap::TerrainState::EMPTY);
                    scene.removeItem(removeSnakeBody->get_pixmap());
                }
                snake->remove_tail(currentSnakeBody->get_prev());
                return;
            }
        }
    }
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
        game_map->get_terrainState(row, col) == GameMap::TerrainState::GHOST_OCCUPIED)
        return true;
    return false;
}

// TODO: merge into reset_view
void game_view::remove_game_content() {
    timer->stop();
    timeCount = 0;
    gameTickTimer->stop();
    gameTickCount = 0;

    for(int i=0;i<terrain_pixmaps.size();i++){
        scene.removeItem(terrain_pixmaps.at(i));
        delete terrain_pixmaps.at(i);
    }
    terrain_pixmaps.clear();

    delete game_map;
    game_map = nullptr;

    for (SnakeBody* currentSnakeBody = snake; currentSnakeBody != nullptr; currentSnakeBody = currentSnakeBody->get_next()) {
        scene.removeItem(currentSnakeBody->get_pixmap());
    }
    delete snake;
    snake = nullptr;

    for (auto it = normalGhosts.begin(); it != normalGhosts.end(); it++) {
        scene.removeItem((*it)->get_pixmap());
        delete (*it);
    }
    normalGhosts.clear();

    for (auto it = bigGhosts.begin(); it != bigGhosts.end(); it++) {
        GhostBody* currentGhostBody = *it;
        do {
            scene.removeItem(currentGhostBody->get_pixmap());
            currentGhostBody = currentGhostBody->get_next();
        } while (currentGhostBody != *it);
        delete (*it);
    }
    bigGhosts.clear();

    for (auto it = fruits.begin(); it != fruits.end(); it++) {
        scene.removeItem((*it)->get_pixmap());
        delete (*it);
    }
    fruits.clear();

    for (auto it = powerups.begin(); it != powerups.end(); it++) {
        scene.removeItem((*it)->get_pixmap());
        delete (*it);
    }
    powerups.clear();
}

void game_view::on_volume_control_clicked()
{
    if (ui->vol_Slider->isVisible()){
        ui->vol_Slider->setVisible(false);
    }else{
        ui->vol_Slider->setVisible(true);
    }
}

void game_view::on_vol_Slider_valueChanged(int value)
{
    selectSoundEffect->setVolume(value);
    hurtSoundEffect->setVolume(value);
    deathSoundEffect->setVolume(value);
    gameOverSoundEffect->setVolume(value);
}


