#include "helperFunctions.h"
#include <iostream>

void HelperFunctions::clearScreen()
{
    std::cout << "\033[2J\033[H"; // ANSI escape code to clear screen and move cursor to home position
}

void HelperFunctions::clearLine(int line, int column)
{
    std::cout << "\033[" << line << ";" << column << "H"; // Move cursor to specified position
    std::cout << "\033[K";                                // Clear line from cursor to end
}

void HelperFunctions::moveCursor(int line, int column)
{
    std::cout << "\033[" << line << ";" << column << "H"; // Move cursor to specified position
}
