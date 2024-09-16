#include "ScreenFunctions.h"
#include <iostream>

void ScreenFunctions::clearScreen()
{
    std::cout << "\033[2J\033[3J\033[H"; // Clear screen, clear scrollback buffer, move cursor to home position
}

void ScreenFunctions::clearLine(int line, int column)
{
    std::cout << "\033[" << line << ";" << column << "H"; // Move cursor to specified position
    std::cout << "\033[K";                                // Clear line from cursor to end
}

void ScreenFunctions::moveCursor(int line, int column)
{
    std::cout << "\033[" << line << ";" << column << "H"; // Move cursor to specified position
}
