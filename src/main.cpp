#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Screen.h"
#include "Schedule.h"
#include "Menu.h"

struct winsize getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

struct SDLWindowDeleter
{
    void operator()(SDL_Window *window) const
    {
        SDL_DestroyWindow(window);
    }
};

struct SDLRendererDeleter
{
    void operator()(SDL_Renderer *renderer) const
    {
        SDL_DestroyRenderer(renderer);
    }
};

void initSDLAndTTF()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << "\n";
        SDL_Quit();
    }
}

std::unique_ptr<SDL_Window, SDLWindowDeleter> initSDLWindow()
{
    try
    {
        return std::unique_ptr<SDL_Window, SDLWindowDeleter>(
            SDL_CreateWindow("Agenda para Marcação e Desmarcação de Atendimentos",
                             SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, 800,
                             600, SDL_WINDOW_SHOWN));
    }
    catch (const std::exception &e)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return nullptr;
    }
}

int main(void)
{
    initSDLAndTTF();
    auto sdl_window = initSDLWindow();

    if (nullptr == sdl_window)
    {
        return 1;
    }

    auto sdl_renderer =
        std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (nullptr == sdl_renderer)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
        SDL_Quit();
    }

    auto font = TTF_OpenFont("../fonts/AovelSansRounded-rdDL.ttf", 24);
    if (!font)
    {
        std::cerr << "Font could not be loaded.\n";
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
        SDL_Quit();
    }

    Screen screen;
    Schedule schedule;
    Menu menu;

    SDL_Event e;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_1:
                    schedule.abre_atendimento(screen, sdl_renderer.get(), font);
                    break;
                case SDLK_2:
                    schedule.abre_desmarcacao(screen, sdl_renderer.get(), font);
                    break;
                case SDLK_3:
                    schedule.lista_cliente(screen, sdl_renderer.get(), font);
                    break;
                case SDLK_4:
                    schedule.horarios_cliente(screen, sdl_renderer.get(), font);
                    break;
                case SDLK_5:
                    schedule.mapa_horarios(screen, sdl_renderer.get(), font);
                    break;
                case SDLK_6:
                    running = false;
                    break;
                default:
                    break;
                }
            }
        }

        // Render your menu here
        menu.renderMenu(screen, sdl_renderer.get(), font);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(sdl_renderer.get());
    SDL_Quit();

    return 0;
}
