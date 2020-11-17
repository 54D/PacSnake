#ifndef ENTITIESBODY_H_
#define ENTITIESBODY_H_

class EntitiesBody {
public:
	EntitiesBody();
	virtual ~EntitiesBody();

	int get_row() const;
	int get_col() const;

protected:
	int row, col;
};

#endif /* ENTITIESBODY_H_ */