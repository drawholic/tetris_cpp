#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "Square.hpp"
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
const sf::Vector2f figure_start_pos(fieldPosition.x + 5 * SQUARE_SIDE, fieldPosition.y - 4 * SQUARE_SIDE);

enum FigureType
{
    I_block,
    J_block,
    L_block,
    O_block,
    Z_block,
    T_block,
    S_block,
};

struct Figure
{
    FigureType type;
    std::unordered_set<Square, SquareHash> squares;
    sf::Color color;
    Figure() : color(sf::Color::Red){};

    void move_top()
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
    }
    void move_down()
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
    };
    void move_left()
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
    };
    void move_right()
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
    void draw_figure(sf::RenderWindow *window) const
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
    bool isFigureAtBottom()
    {
        for (const auto &sq : squares)
        {
            if (isSquareAtBottom(sq))
            {
                return true;
            };
        }
        return false;
    };
    bool isSquareAtBottom(const Square &sq)
    {
        return sq.shape.getPosition().y >= SQUARE_MAX_Y_POS;
    };
    bool isMaxY()
    {
        for (auto sq : squares)
        {
            if (sq.shape.getPosition().y >= SQUARE_MAX_Y_POS)
            {
                return true;
            }
        }
        return false;
    };
    bool isMaxX()
    {
        for (auto sq : squares)
        {
            if (sq.get_x() >= SQUARE_MAX_X_POS)
            {
                return true;
            }
        }
        return false;
    };
    bool isMinY()
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
    bool isMinX()
    {
        for (auto sq : squares)
        {
            if (sq.get_x() == SQUARE_MIN_X_POS)
            {
                return true;
            }
        }
        return false;
    };

    void set_origin(Square &sq)
    {
        sq.shape.setOrigin(figure_start_pos.x, figure_start_pos.y);
    };
    void rotate()
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

    void insert_square(Square &sq)
    {
        set_origin(sq);
        sq.shape.setFillColor(color);
        squares.insert(
            Square(sq.get_x(), sq.get_y()));
    }
    void set_I_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);

        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
    };
    void set_J_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_left();
        insert_square(sq);
    };
    void set_L_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_right();
        insert_square(sq);
    };
    void set_O_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);
        insert_square(sq);
        sq.move_right();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_left();
        insert_square(sq);
    };
    void set_Z_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);
        insert_square(sq);
        sq.move_right();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_right();
        insert_square(sq);
    };
    void set_T_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);
        insert_square(sq);

        sq.move_right();
        insert_square(sq);

        sq.move_right();
        insert_square(sq);

        sq.move_left();
        sq.move_down();

        insert_square(sq);
    };
    void set_S_figure()
    {
        Square sq(figure_start_pos.x, figure_start_pos.y);
        insert_square(sq);
        sq.move_left();
        insert_square(sq);
        sq.move_down();
        insert_square(sq);
        sq.move_left();
        insert_square(sq);
    };

    void set_random_figure()
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
};

#endif
