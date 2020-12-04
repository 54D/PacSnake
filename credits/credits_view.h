#ifndef CREDITS_VIEW_H
#define CREDITS_VIEW_H

#include <QWidget>
#include <QMediaPlayer>

namespace Ui {
class credits_view;
}

class credits_view : public QWidget
{
    Q_OBJECT

public:

	/**
	 * Constructor for credits_view.
	 * @param	parent	This constructor must accept its parent node as a parameter as specified by Qt.
	 */
    credits_view(QWidget *parent = nullptr);

	/**
	 * Destructor for credits_view.
	 */
    ~credits_view();

private:
    Ui::credits_view *ui;
	QMediaPlayer* selectSoundEffect;

};

#endif // CREDITS_VIEW_H
