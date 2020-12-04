#ifndef ACHIEVEMENTS_CONTAINER_H
#define ACHIEVEMENTS_CONTAINER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QTableWidgetItem>
#include "Achievement.h"

namespace Ui {
class achievements_container;
}

class achievements_container : public QWidget
{
    Q_OBJECT

public:

	/**
	 * Constructor for achievements_container.
	 * @param	parent	This constructor must accept its parent node as a parameter as specified by Qt.
	 */
    achievements_container(QWidget *parent = nullptr);

	/**
	 * Destructor for credits_container.
	 */
    ~achievements_container();

	/**
	 * Loads achievements into `tableView`.
	 */
	void load_achievements();

	/**
	 * Obtains the stored Achievement object.
	 */
	Achievement* get_achievement_object();

private slots:

	/**
	 * Handler for `stackedWidget` switching to the achievements view.
	 */
	void stackedWidgetChanged(int index);

	/**
	 * Handler for `back_button`.
	 */
   void on_back_button_clicked();

signals:

   /**
	* Signal fired when previous menu navigation has been requested.
	*/
   void previous_menu();

private:
    Ui::achievements_container *ui;
	QMediaPlayer* selectSoundEffect;
    Achievement* curr_ach;
	QList<QTableWidgetItem*> entries;

	bool backButtonPressed = false;
};

#endif // ACHIEVEMENTS_CONTAINER_H
