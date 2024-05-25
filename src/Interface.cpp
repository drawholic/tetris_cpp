#include "Interface.hpp"

void seed_rng()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
};



Interface::Interface(sf::RenderWindow *window)
    : window(window)
{
    field = Field();
    figure = Figure();
}

void Interface::button_click_event_handle()
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
};

void Interface::window_events_handle()
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
            game_over_status = false;

            break;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::A:
                if (figure.isMinX())
                {
                    continue;
                }
                if (check_for_intersect(FigureMoveEnum::left) || figure.isFigureAtBottom())
                    continue;

                figure.move_left();

                draw_and_display();

                break;
            case sf::Keyboard::Space:

                if (
                    check_for_rotate_intersection() ||
                    check_for_intersect(FigureMoveEnum::left) || figure.isFigureAtBottom())
                    break;

                figure.rotate();
                draw_and_display();

                break;
            case sf::Keyboard::D:
                if (figure.isMaxX())
                {
                    continue;
                }
                if (check_for_intersect(FigureMoveEnum::right) || figure.isFigureAtBottom())
                    continue;
                figure.move_right();

                draw_and_display();

                break;
            case sf::Keyboard::S:

                if (figure.isFigureAtBottom() || check_for_intersect(FigureMoveEnum::down))
                {
                    move_figure_squares_to_field();
                    continue;
                }
                figure.move_down();

                draw_and_display();

                break;
            case sf::Keyboard::Escape:
                start_status = false;
                game_status = false;
                window->close();
                exit(0);
                break;
            }
            break;
        };

        if (button_clicked)
        {
            button_click_event_handle();
        }
    };
}

void Interface::init_text()
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

    game_over_text = sf::Text("GAME OVER", font, 50);
    game_over_text.setPosition(
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
};

void Interface::start_loop()
{
    init_text();

    while (start_status)
    {
        window_events_handle();
        window->clear(sf::Color::Black);
        window->draw(title);
        window->draw(startbtn);
        window->draw(startText);
        window->display();
    }
};

void Interface::game_over()
{
    while (true)
    {
        window_events_handle();
        window->clear();
        window->draw(game_over_text);
        window->display();
    }
};

void Interface::move_rows(int curr_row)
{
    if (curr_row < 0)
        return;
    for (auto it = field.squares.begin(); it != field.squares.end();)
    {
        Square sq = *it;
        if (sq.get_y() == fieldPosition.y + curr_row * SQUARE_SIDE)
        {
            it = field.squares.erase(it);
            sq.move_down();
            field.squares.insert(sq);
        }
        else
        {
            ++it;
        }
    }
    check_for_complete_row(curr_row - 1);
    move_rows(curr_row - 1);
}

void Interface::check_for_complete_row(int curr_row)
{
    if (curr_row < 0)
        return;

    int row_count = 0;
    for (const auto &sq : field.squares)
    {
        if (sq.get_y() == fieldPosition.y + curr_row * SQUARE_SIDE)
        {
            row_count++;
        }
    }

    if (row_count == 10)
    {
        for (auto it = field.squares.begin(); it != field.squares.end();)
        {
            if (it->get_y() == fieldPosition.y + curr_row * SQUARE_SIDE)
            {
                it = field.squares.erase(it);
            }
            else
            {
                ++it;
            }
        }

        move_rows(curr_row - 1);
        check_for_complete_row(curr_row);
    }

    check_for_complete_row(curr_row - 1);
}

bool Interface::is_full_cycle_rate()

{
    elapsed = clock.getElapsedTime();
    if (elapsed.asMilliseconds() > MAX_CLOCK_VALUE)
    {
        clock.restart();
        return true;
    }

    return false;
}

void Interface::draw_and_display()

{
    draw_field();
    draw_squares();
    figure.draw_figure(window);

    window->display();
};

bool Interface::check_for_intersect_start_position()
{
    for (const auto &sq : figure.squares)
    {
        if (field.squares.count(sq))
        {
            return true;
        }
    }
    return false;
}

void Interface::game_loop()
{
    window->setKeyRepeatEnabled(false);
    seed_rng();
    figure.set_random_figure();

    while (game_status)
    {
        window_events_handle();

        if (!is_full_cycle_rate())
        {
            continue;
        }

        if (figure.isFigureAtBottom() || check_for_intersect(FigureMoveEnum::down))
        {
            move_figure_squares_to_field();
            check_for_complete_row();

            figure.set_random_figure();
            if (check_for_intersect_start_position())
            {
                game_over();
                return;
            }
            continue;
        }

        window->clear();

        // MOVE FIGURE

        figure.move_down();

        draw_and_display();
        clock.restart();
    }
};

void Interface::init_field()
{
    field.shape->setPosition(fieldPosition);
    field.shape->setFillColor(sf::Color::Black);
    field.shape->setOutlineThickness(1.0f);
    field.shape->setOutlineColor(sf::Color::White);
};

void Interface::draw_squares()
{
    for (auto sq : field.squares)
    {
        sq.init_square();

        window->draw(sq.shape);
    }
}

void Interface::draw_field()
{
    init_field();
    window->draw(*(field.shape));
};

bool Interface::isSquareInTheAir(Square &sq)
{
    Square test_sq = sq;
    test_sq.move_down();
    if (field.squares.count(test_sq))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Interface::check_for_rotate_intersection()
{
    Figure test_fig = figure;
    test_fig.rotate();
    for (auto sq : test_fig.squares)
    {
        if (field.squares.count(sq))
            return true;
    }
    return false;
}

bool Interface::check_for_intersect(FigureMoveEnum direction)
{
    for (const auto &sq : figure.squares)
    {

        Square next_square(sq);

        switch (direction)
        {
        case FigureMoveEnum::left:
            next_square.move_left();
            break;
        case FigureMoveEnum::right:
            next_square.move_right();
            break;
        case FigureMoveEnum::down:
            next_square.move_down();
            break;
        case FigureMoveEnum::still:
            break;
        }
        if (field.squares.count(next_square))
        {
            return true;
        }
    }
    return false;
};

void Interface::move_figure_squares_to_field()
{

    {
        for (const auto &sq : figure.squares)
        {
            field.squares.insert(sq);
        }
    }
}