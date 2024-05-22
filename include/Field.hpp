#ifndef FIELD_HPP
#define FIELD_HPP
#include <unordered_set>
#include "Square.hpp"
#include "utilities.hpp"

#include <SFML/Graphics.hpp>
struct Field
{
    
    std::unordered_set<Square, SquareHash> squares;
    sf::RectangleShape *shape;
    Field()
    {
        shape = new sf::RectangleShape(sf::Vector2f(FIELD_WIDTH, FIELD_HEIGHT));
    }
    auto begin()
    {
        return squares.begin();
    };
    auto end()
    {
        return squares.end();
    }
};

#endif