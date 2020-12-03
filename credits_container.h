#ifndef CREDITS_CONTAINER_H
#define CREDITS_CONTAINER_H

#include <QWidget>
#include <QMediaPlayer>
#include "credits_view.h"

namespace Ui {
class credits_container;
}

class credits_container : public QWidget
{
    Q_OBJECT

public:
    credits_container(QWidget *parent = nullptr);
    ~credits_container();

private slots:
   void on_back_button_clicked();

signals:
   void previous_menu();

private:
    Ui::credits_container *ui;
	QMediaPlayer* selectSound;
    credits_view* credits_view_widget;
};

#endif // CREDITS_CONTAINER_H
