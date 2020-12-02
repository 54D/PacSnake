#include "Entity.h"

Entity::~Entity() {}

int Entity::get_row() const {
    return row;
}

int Entity::get_col() const {
    return col;
}

void Entity::set_row(int row) {
    this->row = row;
}

void Entity::set_col(int col) {
    this->col = col;
}

void Entity::set_coordinate(int row, int col) {
    this->row = row;
    this->col = col;
}

void Entity::set_relative_coordinate(int delta_row, int delta_col) {
    row = row + delta_row;
    col = col + delta_col;
}

void Entity::register_view(QGraphicsPixmapItem *pixmap){
    this->pixmap = pixmap;
}

void Entity::refresh_pixmap(){
    //todo
    //pixmap->setPixmap()
    return;
}

QGraphicsPixmapItem* Entity::get_pixmap() {
    return this->pixmap;
}

Entity::Entity() {}

Entity::Entity(int row, int col) :
        row(row), col(col) {}
