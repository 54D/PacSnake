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

	/**
	 * Constructor for main_container.
	 * @param	parent	This constructor must accept its parent node as a parameter as specified by Qt.
	 */
    main_container(QWidget *parent = nullptr);
	/**
	 * Destructor for main_container.
	 */
    ~main_container();

private slots:

	/**
	 * Handler for `startButton`.
	 */
    void on_startButton_clicked();
	/**
	 * Handler for `achButton`.
	 */
    void on_achButton_clicked();
	/**
	 * Handler for `creditsButton`.
	 */
    void on_creditsButton_clicked();
	/**
	 * Handler for `leaveButton`.
	 */
    void on_leaveButton_clicked();
	/**
	 * Handler for change of `stackedWidget` view.
	 * This essentially simply passes the information to a self-defined signal.
	 */
    void on_stackedWidget_currentChanged(int index);
	/**
	 * Switches the `stackedWidget` current view back to main menu.
	 */
    void bring_back();

signals:

	/**
	 * Signal fired when the `stackedWidget` in main menu has changed index.
	 * @param	index	New index of `stackedWidget`.
	 */
    void stackedWidgetChange(int index);

private:

    Ui::main_container *ui;
	QMediaPlayer* selectSoundEffect;

};
#endif // WIDGET_H
