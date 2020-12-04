#ifndef ENTITY_H_
#define ENTITY_H_

#include <QObject>
#include <QGraphicsPixmapItem>

class Entity : public QObject {

public:

	/**
	 * Constructor for Entity.
	 */
	Entity();
	/**
	 * Constructor for Entity.
	 * @param	row		Initial row location.
	 * @param	col		Initial column location.
	 */
	Entity(int row, int col);

	/**
	 * Destructor for Entity.
	 */
	virtual ~Entity();

	/**
	 * Obtains this Entity's current row location.
	 * @return	row		Current row location.
	 */
	int get_row() const;
	/**
	 * Obtains this Entity's current column location.
	 * @return	col		Current column location.
	 */
	int get_col() const;

	/**
	 * Sets this Entity's current row location.
	 * @param	row		New row location.
	 */
	void set_row(int row);
	/**
	 * Sets this Entity's current column location.
	 * @param	col		New column location.
	 */
	void set_col(int col);
	/**
	 * Sets this Entity's current coordinates.
	 * @param	row		New row location.
	 * @param	col		New column location.
	 */
	void set_coordinate(int row, int col);
	/**
	 * Moves this Entity's current coordinates by a relative amount.
	 * @param	delta_row	New relative row location.
	 * @param	delta_col	New relative column location.
	 */
	void set_relative_coordinate(int delta_row, int delta_col);
	/**
	 * Stores a `QGraphicsPixmapItem` representation of this Entity. Only one image can be registered at a time.
	 * @param	pixmap		Pixmap representation of this Entity.
	 */
	void register_view(QGraphicsPixmapItem *pixmap);
	/**
	 * Obtains this Entity's `QGraphicsPixmapItem` representation.
	 * @return	pixmap		Pixmap representation of this Entity.
	 */
	QGraphicsPixmapItem* get_pixmap();

protected:

	int row, col;
	QGraphicsPixmapItem *pixmap;

};


#endif /* ENTITY_H_ */
