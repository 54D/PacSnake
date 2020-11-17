#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_

#include "../entities/EntitiesBody.h"

class SnakeBody : public EntitiesBody {
public:
	SnakeBody();
	virtual ~SnakeBody();
	
private:
	SnakeBody* prev {nullptr};
	SnakeBody* next {nullptr};
};

#endif /* SNAKEBODY_H_ */