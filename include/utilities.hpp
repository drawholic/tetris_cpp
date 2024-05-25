#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>

const int MAX_CLOCK_VALUE = 500;

const int MAX_ROW_INDEX = 18;
const int MAX_COL_INDEX = 9;

const int SCR_HEIGHT = 1000;
const int SCR_WIDTH = 700;

const int FIELD_HEIGHT = SCR_HEIGHT / 3 * 2;
const int FIELD_WIDTH = SCR_WIDTH / 2;

const int SQUARE_SIDE = FIELD_WIDTH / 10;

const int fieldX = SCR_WIDTH / 4;
const int fieldY = SCR_HEIGHT / 6;

const sf::Vector2f fieldPosition = sf::Vector2f(fieldX, fieldY);

const int SQUARE_MAX_Y_POS = fieldPosition.y + SQUARE_SIDE * MAX_ROW_INDEX;
const int SQUARE_MAX_X_POS = fieldPosition.y + SQUARE_SIDE * MAX_COL_INDEX;

const int SQUARE_MIN_Y_POS = fieldPosition.y;
const int SQUARE_MIN_X_POS = fieldPosition.x;

const sf::Vector2f SQUARE_SIZE(SQUARE_SIDE, SQUARE_SIDE);



#endif
