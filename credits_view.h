#ifndef CREDITS_VIEW_H
#define CREDITS_VIEW_H

#include <QWidget>

namespace Ui {
class credits_view;
}

class credits_view : public QWidget
{
    Q_OBJECT

public:
    credits_view(QWidget *parent = nullptr);
    ~credits_view();

private:
    Ui::credits_view *ui;
};

#endif // CREDITS_VIEW_H
