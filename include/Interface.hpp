#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Figure.hpp"
#include "Field.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

struct Interface
{
    Figure *figure;
    Field *field;
    sf::RenderWindow *window;

    sf::Font font;
    sf::Text title;
    sf::RectangleShape startbtn;
    sf::Text startText;

    bool button_clicked = true;
    bool game_status = true;
    bool start_status = true;

    Interface(sf::RenderWindow *window)
        : window(window)
    {
        field = new Field();
        figure = new Figure();
    }

    ~Interface()
    {
        delete field;
        delete figure;
    }

    void button_click_event_handle()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);
            if (mouse_position.x >= startbtn.getPosition().x && mouse_position.x <= (startbtn.getPosition().x + startbtn.getSize().x) && mouse_position.y >= startbtn.getPosition().y && mouse_position.y <= (startbtn.getPosition().y + startbtn.getSize().y))
            {
                start_status = false;
                button_clicked = true;
            }
        }
    }

    void window_events_handle()
    {

        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                start_status = false;
                game_status = false;
                window->close();
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::A:
                    if (figure->isMinX())
                    {
                        continue;
                    }
                    figure->move_left();
                    break;
                case sf::Keyboard::Space:
                    figure->rotate();

                    break;
                case sf::Keyboard::D:
                    if (figure->isMaxX())
                    {
                        continue;
                    }
                    figure->move_right();
                    break;
                case sf::Keyboard::S:

                    if (figure->isFigureAtBottom() || check_for_intersect())
                    {
                        move_figure_squares_to_field();
                        continue;
                    }
                    figure->move_down();

                    break;
                case sf::Keyboard::Escape:
                    start_status = false;
                    game_status = false;
                    window->close();
                    break;
                }
                break;
            };

            if (button_clicked)
            {
                button_click_event_handle();
            }
            // break;
        };
    }

    void init_text()
    {
        if (!font.loadFromFile("../romans.ttf"))
        {
            std::cerr << "FAILURE ON LOADING FONT\n";
            exit(-1);
        }
        title = sf::Text("TETRIS", font, 50);
        startText = sf::Text("START", font, 50);

        int title_width = 50 * 6;
        int title_height = 50;
        title.setPosition(
            (SCR_WIDTH / 2.0f) - (title_width / 2.0f),
            (SCR_HEIGHT / 4.0f) - (title_height / 2.0f));

        startbtn.setSize(sf::Vector2f(200, 100));
        startbtn.setPosition(
            (SCR_WIDTH / 2.0f) - (startbtn.getSize().x / 2),
            (SCR_HEIGHT / 2.0f) - (startbtn.getSize().y / 2));

        sf::FloatRect rectBounds = startbtn.getGlobalBounds();
        sf::Vector2f rectCenter(
            rectBounds.left + rectBounds.width / 2.0f,
            rectBounds.top + rectBounds.height / 2.0f);
        sf::FloatRect textBounds = startText.getLocalBounds();

        startText.setOrigin(
            textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        startText.setPosition(rectCenter);

        startbtn.setFillColor(sf::Color(0, 0, 0, 0));
        startbtn.setOutlineColor(sf::Color::White);
        startbtn.setOutlineThickness(1);
    }

    void start_loop()
    {
        init_text();
        for (int i{0}; i <= 3; i++)
        {
            std::cout << get_random_figure() << '\n';
        }
        while (start_status)
        {
            window_events_handle();
            window->clear(sf::Color::Black);
            window->draw(title);
            window->draw(startbtn);
            window->draw(startText);
            window->display();
        }
    }
    void game_over()
    {
        game_status = false;
        std::cerr << "Game Over" << std::endl;
    }
    void check_for_complete_row(int max_row = SQUARE_MAX_Y_POS)
    {
        // for (int curr_row_index = max_row; curr_row_index > SQUARE_MIN_Y_POS; curr_row_index -= SQUARE_SIDE)
        // {
        //     int count = 0;
        //     for (int i = 0; i <= MAX_COL_INDEX; i++)
        //     {
        //         Square sq = Square(fieldPosition.x + SQUARE_SIDE * i, fieldPosition.y + SQUARE_SIDE * curr_row_index);
        //         if (field->squares.count(sq))
        //         {
        //             count++;
        //         }
        //     }
        //     if (count == 10)
        //     {
        //         for (int i = 0; i <= MAX_COL_INDEX; i++)
        //         {
        //             Square sq = Square(fieldPosition.x + SQUARE_SIDE * i, fieldPosition.y + SQUARE_SIDE * curr_row_index);
        //             field->squares.erase(sq);
        //         };

        //     }
        // }

        for (int row = max_row; row >= 0; --row)
        {
            int row_count = 0;
            for (const auto &sq : field->squares)
            {
                if (sq.get_y() == fieldPosition.y + row * SQUARE_SIDE)
                {
                    ++row_count;
                }
            }

            if (row_count == 10)
            {
                auto it = field->squares.begin();
                while (it != field->squares.end())
                {
                    if (it->get_y() == fieldPosition.y + row * SQUARE_SIDE)
                    {
                        it = field->squares.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }

                for (auto &sq : field->squares)
                {
                    if (sq.get_y() <= fieldPosition.y + row * SQUARE_SIDE)
                    {
                        Square new_sq = sq;
                        new_sq.move_down();
                        field->squares.erase(sq);
                        field->squares.insert(new_sq);
                    }
                }
            }
        }
    }

    void game_loop()
    {
        window->setKeyRepeatEnabled(false);
        seed_rng();
        figure->set_random_figure();
        while (game_status)
        {
            window_events_handle();

            if (figure->isFigureAtBottom() || check_for_intersect())
            {
                move_figure_squares_to_field();
                check_for_complete_row();

                figure->set_random_figure();
                continue;
            }
            window->clear();

            // MOVE FIGURE

            figure->move_down();

            draw_field();
            draw_squares();
            figure->draw_figure(window);

            window->display();

            sf::sleep(sf::milliseconds(500));
        }
    }

    void init_field()
    {
        field->shape->setPosition(fieldPosition);
        field->shape->setFillColor(sf::Color::Black);
        field->shape->setOutlineThickness(1.0f);
        field->shape->setOutlineColor(sf::Color::White);
    }

    void draw_squares()
    {
        for (auto sq : field->squares)
        {
            sq.shape.setSize(SQUARE_SIZE);
            sq.shape.setFillColor(sq.color);
            sq.shape.setOutlineColor(sf::Color::White);
            sq.shape.setOutlineThickness(-2);
            window->draw(sq.shape);
        }
    }
    void draw_field()
    {
        init_field();
        window->draw(*(field->shape));
    }

    bool isSquareInTheAir(Square &sq)
    {
        Square test_sq = sq;
        test_sq.move_down();
        if (field->squares.count(test_sq))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool check_for_intersect()
    {
        for (const auto &sq : figure->squares)
        {
            Square bottom_square(sq);
            bottom_square.move_down();
            if (field->squares.count(bottom_square))
            {
                return true;
            }
        }
        return false;
    }

    void move_figure_squares_to_field()
    {
        for (const auto &sq : figure->squares)
        {
            field->squares.insert(sq);
        }
    }
};

#endif
