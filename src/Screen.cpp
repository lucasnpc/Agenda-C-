#include "Screen.h"
#include <iostream>

void Screen::clearScreen()
{
    std::cout << "\033[2J\033[3J\033[H"; // Clear screen, clear scrollback buffer, move cursor to home position
}

void Screen::clearLine(int line, int column)
{
    std::cout << "\033[" << line << ";" << column << "H"; // Move cursor to specified position
    std::cout << "\033[K";                                // Clear line from cursor to end
}

void Screen::moveCursor(int line, int column)
{
    std::cout << "\033[" << line << ";" << column << "H"; // Move cursor to specified position
}
