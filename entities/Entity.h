#ifndef ENTITY_H_
#define ENTITY_H_

class Entity {
public:
    virtual ~Entity();

    int get_row() const;
    int get_col() const;

    void set_row(int row);
    void set_col(int col);
    void set_coordinate(int row, int col);
    void set_relative_coordinate(int delta_row, int delta_col);

protected:
    Entity();
    Entity(int row, int col);

    int row, col;
};


#endif /* ENTITY_H_ */
