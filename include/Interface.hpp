#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Figure.hpp"
#include "Field.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

enum FigureMoveEnum
{
    still,
    left,
    right,
    down,
};

struct Interface
{
    sf::Clock clock;
    sf::Time elapsed;
    int CURRENT_CLOCK_VALUE;

    Figure figure;
    Field field;
    sf::RenderWindow *window;

    sf::Font font;
    sf::Text game_over_text;
    sf::Text title;
    sf::RectangleShape startbtn;
    sf::Text startText;

    bool game_over_status = true;
    bool button_clicked = true;
    bool game_status = true;
    bool start_status = true;

    Interface(sf::RenderWindow *window);

    ~Interface()
    {
    }

    void button_click_event_handle();

    void window_events_handle();

    void init_text();

    void start_loop();
    void game_over();
    void move_rows(int curr_row);

    void check_for_complete_row(int curr_row = SQUARE_MAX_Y_POS);

    bool is_full_cycle_rate();

    void draw_and_display();

    bool check_for_intersect_start_position();

    void game_loop();

    void init_field();

    void draw_squares();
    void draw_field();

    bool isSquareInTheAir(Square &sq);

    bool check_for_rotate_intersection();

    bool check_for_intersect(FigureMoveEnum direction);

    void move_figure_squares_to_field();
};

#endif
