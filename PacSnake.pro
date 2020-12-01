QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameMap.cpp \
    achievements/Achievement.cpp \
    achievements/achievements_container.cpp \
    credits_container.cpp \
    credits_view.cpp \
    entities/Entity.cpp \
    entities/MovingEntity.cpp \
    entities/snake/Snake.cpp \
    entities/snake/SnakeBody.cpp \
    game_view.cpp \
    main.cpp \
    main_container.cpp

HEADERS += \
    GameMap.h \
    achievements/Achievement.h \
    achievements/achievements_container.h \
    credits_container.h \
    credits_view.h \
    entities/Entity.h \
    entities/MovingEntity.h \
    entities/fruits_and_powerUps/Fruit.h \
    entities/fruits_and_powerUps/PowerUp.h \
    entities/ghosts/Ghost.h \
    entities/ghosts/NormalGhost.h \
    entities/snake/Snake.h \
    entities/snake/SnakeBody.h \
    game_view.h \
    main_container.h

FORMS += \
    achievements/achievements_container.ui \
    credits_container.ui \
    credits_view.ui \
    game_view.ui \
    main_container.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
