#ifndef ACHIEVEMENTS_CONTAINER_H
#define ACHIEVEMENTS_CONTAINER_H

#include <QWidget>
#include <QMediaPlayer>

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

private slots:

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

};

#endif // ACHIEVEMENTS_CONTAINER_H
