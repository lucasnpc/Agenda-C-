#include "Screen.h"
#include <iostream>

void Screen::clearScreen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
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
