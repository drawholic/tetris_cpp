#ifndef FIGURE_HPP
#define FIGURE_HPP
#include "Square.hpp"
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "utilities.hpp"
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
    Figure();
    void move_top();
    void move_down();
    void move_left();
    void move_right();

    void draw_figure(sf::RenderWindow *window) const;
    bool isFigureAtBottom();
    bool isSquareAtBottom(const Square &sq);
    bool isMaxY();
    bool isMaxX();
    bool isMinY();
    bool isMinX();

    void set_origin(Square &sq);
    void rotate();

    void insert_square(Square &sq);
    void set_I_figure();
    void set_J_figure();
    void set_L_figure();
    void set_O_figure();
    void set_Z_figure();
    void set_T_figure();
    void set_S_figure();

    void set_random_figure();
};

#endif
