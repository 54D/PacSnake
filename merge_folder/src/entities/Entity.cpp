#include "Entity.h"

Entity::~Entity() {}

double Entity::get_row() const {
    return row;
}

double Entity::get_col() const {
    return col;
}

void Entity::set_row(double row) {
    this->row = row;
}

void Entity::set_col(double col) {
    this->col = col;
}

void Entity::set_coordinate(double row, double col) {
    this->row = row;
    this->col = col;
}

void Entity::set_relative_coordinate(double delta_row, double delta_col) {
    this->row = row + delta_row;
    this->col = col + delta_col;
}

Entity::Entity() {}

Entity::Entity(double row, double col) :
        row(row), col(col) {}