#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QMediaPlayer>

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
    void on_stackedWidget_currentChanged(int index);
    void bring_back();

signals:
    void stackedWidgetChange(int index);

private:
    Ui::main_container *ui;
	QMediaPlayer* selectSound;
};
#endif // WIDGET_H
