#include <SFML/Graphics.hpp>
#include "utilities.hpp"
#include "Interface.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "TETRIS");
    Interface interface(&window);
    interface.start_loop();
    interface.game_loop();
    interface.game_over();
    return 0;
}