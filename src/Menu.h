#ifndef MENU_H
#define MENU_H

#include "Screen.h"
#include <SDL.h>
#include <SDL_ttf.h>

class Menu
{
public:
    void renderMenu(Screen &screen, SDL_Renderer *renderer, TTF_Font *font);
};

#endif