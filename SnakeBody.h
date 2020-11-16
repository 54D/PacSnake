#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_

#include "Body.h"

class SnakeBody : public Body {
public:
	SnakeBody();
	virtual ~SnakeBody();
	
private:
	SnakeBody* prev {nullptr};
	SnakeBody* next {nullptr};
};

#endif /* SNAKEBODY_H_ */