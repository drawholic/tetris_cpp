#include "Square.hpp"
#include "utilities.hpp"

Square::Square(int x, int y)
{
    shape.setPosition(x, y);
};

Square::Square(Square &&sq) noexcept
{
    shape.setPosition(sq.shape.getPosition());
};
Square::Square(const Square &sq)
{
    shape.setPosition(sq.shape.getPosition());
    shape.setSize(sq.shape.getSize());
    color = sq.color;
};

Square &Square::operator=(const Square &sq)
{
    if (this == &sq)
        return *this;
    shape.setPosition(sq.shape.getPosition());
    shape.setSize(sq.shape.getSize());
    color = sq.color;
    return *this;
};
// Square &Square::operator=(const Square &sq) noexcept
// {
//     if (this == &sq)
//         return *this;
//     shape.setPosition(sq.shape.getPosition());
//     shape.setSize(sq.shape.getSize());
//     color = sq.color;
//     return *this;
// };

bool Square::operator==(const Square &other) const
{
    return get_x() == other.get_x() && get_y() == other.get_y();
}
bool Square::operator==(Square &other) const
{
    return get_x() == other.get_x() && get_y() == other.get_y();
}

int Square::get_x() const
{
    return shape.getPosition().x;
};
int Square::get_y() const
{
    return shape.getPosition().y;
}
void Square::move_down()
{
    shape.setPosition(shape.getPosition().x, shape.getPosition().y + SQUARE_SIDE);
};
void Square::move_top()
{
    shape.setPosition(shape.getPosition().x, shape.getPosition().y - SQUARE_SIDE);
}

void Square::move_left()
{
    shape.setPosition(shape.getPosition().x - SQUARE_SIDE, shape.getPosition().y);
};
void Square::move_right()
{
    shape.setPosition(shape.getPosition().x + SQUARE_SIDE, shape.getPosition().y);
};

void Square::init_square()
{
    shape.setSize(SQUARE_SIZE);
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(-2);
};

std::size_t SquareHash::operator()(const Square &s) const noexcept
{

    std::size_t hx = std::hash<int>()(s.get_x());
    std::size_t hy = std::hash<int>()(s.get_y());
    return hx ^ (hy << 1);
}