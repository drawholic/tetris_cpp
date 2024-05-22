#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <SFML/Graphics.hpp>
#include <functional> // for std::hash

struct Square
{
    sf::Color color = sf::Color::Red;
    sf::RectangleShape shape;
    Square(int x, int y)
    {
        shape.setPosition(x, y);
    };
    Square(Square &&sq) noexcept
    {
        shape.setPosition(sq.shape.getPosition());
    };
    Square(Square &sq)
    {
        shape.setPosition(sq.shape.getPosition());
    };
    Square(const Square &sq)
    {
        shape.setPosition(sq.shape.getPosition());
        shape.setSize(sq.shape.getSize());
        color = sq.color;
    }
    Square &operator=(const Square &sq)
    {
        if (this == &sq)
            return *this;
        shape.setPosition(sq.shape.getPosition());
        shape.setSize(sq.shape.getSize());
        color = sq.color;
        return *this;
    }
    Square &operator=(Square &&sq) noexcept
    {
        if (this == &sq)
            return *this;
        shape.setPosition(sq.shape.getPosition());
        shape.setSize(sq.shape.getSize());
        color = sq.color;
        return *this;
    }
    bool operator==(const Square &other) const
    {
        return get_x() == other.get_x() && get_y() == other.get_y();
    }
    bool operator==(Square &other) const
    {
        return get_x() == other.get_x() && get_y() == other.get_y();
    }
    int get_x() const
    {
        return shape.getPosition().x;
    };
    int get_y() const
    {
        return shape.getPosition().y;
    };
    void move_down()
    {
        shape.setPosition(shape.getPosition().x, shape.getPosition().y + SQUARE_SIDE);
    }
    void move_top()
    {
        shape.setPosition(shape.getPosition().x, shape.getPosition().y - SQUARE_SIDE);
    }
    void move_left()
    {
        shape.setPosition(shape.getPosition().x - SQUARE_SIDE, shape.getPosition().y);
    }
    void move_right()
    {
        shape.setPosition(shape.getPosition().x + SQUARE_SIDE, shape.getPosition().y);
    }
};

struct SquareHash
{
    std::size_t operator()(const Square &s) const noexcept
    {
        std::size_t hx = std::hash<int>()(s.get_x());
        std::size_t hy = std::hash<int>()(s.get_y());
        return hx ^ (hy << 1);
    }
};

#endif