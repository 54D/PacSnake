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

	/**
	 * Constructor for credits_container.
	 * @param	parent	This constructor must accept its parent node as a parameter as specified by Qt.
	 */
    credits_container(QWidget *parent = nullptr);

	/**
	 * Destructor for credits_container.
	 */
    ~credits_container();

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
    Ui::credits_container *ui;
	QMediaPlayer* selectSoundEffect;
    credits_view* credits_view_widget;

};

#endif // CREDITS_CONTAINER_H
