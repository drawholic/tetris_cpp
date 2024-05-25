#include "Field.hpp"

Field::Field()
{
    shape = new sf::RectangleShape(sf::Vector2f(FIELD_WIDTH, FIELD_HEIGHT));
};