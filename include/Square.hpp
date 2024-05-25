#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <SFML/Graphics.hpp>
#include <functional> // for std::hash

struct Square
{
    sf::Color color = sf::Color::Red;
    sf::RectangleShape shape;
    Square(int x, int y);
    Square(Square &&sq) noexcept;
    Square(Square &sq)
    {
        shape.setPosition(sq.shape.getPosition());
    };
    Square(const Square &sq);
    Square &operator=(const Square &sq);
    Square &operator=(Square &&sq) noexcept;
    bool operator==(const Square &other) const;
    bool operator==(Square &other) const;
    int get_x() const;
    int get_y() const;
    void move_down();
    void move_top();
    void move_left();
    void move_right();

    void init_square();
};

struct SquareHash
{
    std::size_t operator()(const Square &s) const noexcept;
};

#endif