#include "Menu.h"
#include <iostream>

void Menu::renderMenu(Screen &screen, SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_Color white = {255, 255, 255, 255};

    auto renderText = [&renderer, &font, &white](std::string text, int x, int y)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), white);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect dstrect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderText("*** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***", 50, 50);
    renderText("MENU PRINCIPAL", 50, 100);
    renderText("[1] MARCAR ATENDIMENTO", 50, 150);
    renderText("[2] DESMARCAR ATENDIMENTO", 50, 200);
    renderText("[3] LISTAR MARCAÇÕES DO DIA", 50, 250);
    renderText("[4] CLIENTES MARCADOS NO DIA", 50, 300);
    renderText("[5] MAPA DOS HORÁRIOS LIVRES", 50, 350);
    renderText("[6] FIM DO PROGRAMA", 50, 400);
    renderText("==>", 50, 450);

    SDL_RenderPresent(renderer);
}