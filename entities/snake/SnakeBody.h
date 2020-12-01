#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_

#include <entities/MovingEntity.h>

class SnakeBody : public MovingEntity {
public:
	friend class Snake;
	virtual ~SnakeBody();
    
    const SnakeBody* get_prev() const;
    const SnakeBody* get_next() const;

protected:
    // Remove all the SnakeBody after this SnakeBody
	SnakeBody(int row, int col, int speed, Direction headingDirection = Direction::NORTH, SnakeBody* prev = nullptr, SnakeBody* next = nullptr);
	
	virtual void move_forward() override;
	void remove_tail();
    virtual QPixmap get_pixmap() override;
    
    SnakeBody* prev {nullptr};
    SnakeBody* next {nullptr};
};

#endif /* SNAKEBODY_H_ */
