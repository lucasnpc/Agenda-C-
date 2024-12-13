#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

class Screen
{
public:
    void clearScreen(SDL_Renderer *renderer);
    void clearLine(int line, int column);
    void moveCursor(int line, int column);
};

#endif