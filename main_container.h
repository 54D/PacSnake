#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class main_container; }
QT_END_NAMESPACE

class main_container : public QWidget
{
    Q_OBJECT

public:
    main_container(QWidget *parent = nullptr);
    ~main_container();

private slots:
    void on_startButton_clicked();
    void on_achButton_clicked();
    void on_creditsButton_clicked();
    void on_leaveButton_clicked();
    void bring_back();

private:
    Ui::main_container *ui;
};
#endif // WIDGET_H
