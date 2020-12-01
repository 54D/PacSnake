#ifndef ACHIEVEMENTS_CONTAINER_H
#define ACHIEVEMENTS_CONTAINER_H

#include <QWidget>

namespace Ui {
class achievements_container;
}

class achievements_container : public QWidget
{
    Q_OBJECT

public:
    achievements_container(QWidget *parent = nullptr);
    ~achievements_container();

private slots:
   void on_back_button_clicked();

signals:
   void previous_menu();

private:
    Ui::achievements_container *ui;
};

#endif // ACHIEVEMENTS_CONTAINER_H
