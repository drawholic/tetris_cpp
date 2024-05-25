#include "Figure.hpp"
#include "utilities.hpp"

int get_random_figure()
{
    return 1 + std::rand() % 7;
};

Figure::Figure() : color(sf::Color::Red){};

void Figure::move_top()
{
    std::unordered_set<Square, SquareHash> new_squares;
    for (auto it = squares.begin(); it != squares.end(); it++)
    {
        Square newSquare(*it);
        newSquare.color = it->color;
        newSquare.move_top();
        new_squares.insert(newSquare);
    };
    squares = std::move(new_squares);
};

void Figure::move_down()
{
    std::unordered_set<Square, SquareHash> new_squares;
    for (auto it = squares.begin(); it != squares.end(); it++)
    {
        Square newSquare(*it);
        newSquare.color = it->color;
        newSquare.move_down();
        new_squares.insert(newSquare);
    };
    squares = std::move(new_squares);
}

void Figure::move_left()
{
    std::unordered_set<Square, SquareHash> new_squares;
    for (auto it = squares.begin(); it != squares.end(); it++)
    {
        Square newSquare(*it);
        newSquare.color = it->color;
        newSquare.move_left();
        new_squares.insert(newSquare);
    };
    squares = std::move(new_squares);
}

void Figure::move_right()
{
    std::unordered_set<Square, SquareHash> new_squares;
    for (auto it = squares.begin(); it != squares.end(); it++)
    {
        Square newSquare(*it);
        newSquare.color = it->color;
        newSquare.move_right();
        new_squares.insert(newSquare);
    };
    squares = std::move(new_squares);
}

void Figure::draw_figure(sf::RenderWindow *window) const
{
    for (auto sq : squares)
    {
        if (sq.get_y() < fieldPosition.y)
        {
            continue;
        }
        sq.shape.setOutlineColor(sf::Color::White);
        sq.shape.setOutlineThickness(-2);

        sq.shape.setFillColor(sq.color);
        sq.shape.setSize(SQUARE_SIZE);
        window->draw(sq.shape);
    }
}

bool Figure::isFigureAtBottom()
{
    for (const auto &sq : squares)
    {
        if (isSquareAtBottom(sq))
        {
            return true;
        };
    }
    return false;
}

bool Figure::isSquareAtBottom(const Square &sq)
{
    return sq.shape.getPosition().y >= SQUARE_MAX_Y_POS;
}

bool Figure::isMaxY()
{
    for (auto sq : squares)
    {
        if (sq.shape.getPosition().y >= SQUARE_MAX_Y_POS)
        {
            return true;
        }
    }
    return false;
}

bool Figure::isMaxX()
{

    for (auto sq : squares)
    {
        if (sq.get_x() >= SQUARE_MAX_X_POS)
        {
            return true;
        }
    }
    return false;
}

bool Figure::isMinY()
{

    for (auto sq : squares)
    {
        if (sq.get_y() == SQUARE_MIN_Y_POS)
        {
            return true;
        }
    };
    return false;
};

bool Figure::isMinX()
{
    for (auto sq : squares)
    {
        if (sq.get_x() == SQUARE_MIN_X_POS)
        {
            return true;
        }
    }
    return false;
}

void Figure::set_origin(Square &sq)
{
    sq.shape.setOrigin(figure_start_pos.x, figure_start_pos.y);
}

void Figure::rotate()
{
    if (type == O_block)
        return; // The O_block does not rotate.

    std::unordered_set<Square, SquareHash> new_squares;
    auto it = squares.begin();
    if (it == squares.end())
        return;

    Square center = *it;
    sf::Vector2f centerPosition = center.shape.getPosition();

    for (auto &sq : squares)
    {
        sf::Vector2f relativePos = sq.shape.getPosition() - centerPosition;
        sf::Vector2f rotatedPos(-relativePos.y, relativePos.x);
        sf::Vector2f newPos = centerPosition + rotatedPos;

        Square newSquare(newPos.x, newPos.y);
        newSquare.color = sq.color;
        new_squares.insert(newSquare);
    }

    squares = std::move(new_squares);
    while (isMaxX())
    {
        move_left();
    };
    while (isMinX())
    {
        move_right();
    }
    while (isMaxY())
    {
        move_top();
    }
}

void Figure::insert_square(Square &sq)
{
    set_origin(sq);
    sq.shape.setFillColor(color);
    squares.insert(
        Square(sq.get_x(), sq.get_y()));
}

void Figure::set_I_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
}

void Figure::set_J_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_left();
    insert_square(sq);
}

void Figure::set_L_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_right();
    insert_square(sq);
}

void Figure::set_O_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();

    insert_square(sq);
    sq.move_right();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_left();
    insert_square(sq);
}

void Figure::set_Z_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();

    insert_square(sq);
    sq.move_right();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_right();
    insert_square(sq);
}

void Figure::set_T_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();

    insert_square(sq);

    sq.move_right();
    insert_square(sq);

    sq.move_right();
    insert_square(sq);

    sq.move_left();
    sq.move_down();

    insert_square(sq);
}

void Figure::set_S_figure()
{
    Square sq(figure_start_pos.x, figure_start_pos.y);
    sq.init_square();

    insert_square(sq);
    sq.move_left();
    insert_square(sq);
    sq.move_down();
    insert_square(sq);
    sq.move_left();
    insert_square(sq);
}

void Figure::set_random_figure()
{
    squares.clear();
    int choice = get_random_figure();
    switch (choice)
    {
    case 1:
        set_I_figure();
        type = FigureType::I_block;
        break;
    case 2:
        set_J_figure();
        type = FigureType::J_block;
        break;
    case 3:
        set_L_figure();
        type = FigureType::L_block;

        break;
    case 4:
        set_O_figure();
        type = FigureType::O_block;

        break;
    case 5:
        set_Z_figure();
        type = FigureType::Z_block;

        break;
    case 6:
        set_T_figure();
        type = FigureType::T_block;

        break;
    case 7:
        set_S_figure();
        type = FigureType::S_block;

        break;

    default:
        break;
    }
}