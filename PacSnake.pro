QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameEngine.cpp \
    achievements/Achievement.cpp \
    achievements/achievements_container.cpp \
    credits_container.cpp \
    credits_view.cpp \
    entities/Entity.cpp \
    entities/MovingEntity.cpp \
    main.cpp \
    snake.cpp \
    widget.cpp

HEADERS += \
    GameEngine.h \
    achievements/Achievement.h \
    achievements/achievements_container.h \
    credits_container.h \
    credits_view.h \
    entities/Entity.h \
    entities/MovingEntity.h \
    snake.h \
    widget.h

FORMS += \
    achievements/achievements_container.ui \
    credits_container.ui \
    credits_view.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
