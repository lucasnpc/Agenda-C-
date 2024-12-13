#include "Schedule.h"
#include <iostream>

std::unique_ptr<Core> Schedule::core = std::make_unique<Core>();

void Schedule::marca_atendimento(const int dia, const int hora, const char nome[50])
{
    const char *pnome = 0;
    pnome = nome;
    int i = 0;
    while (*pnome)
    {
        core->atendimento[dia][hora][i] = *pnome;
        pnome++;
        i++;
    }
}

bool Schedule::mapa_ocupado(int dia, int hora)
{
    char *ocupado = 0;
    ocupado = core->atendimento[dia][hora];
    if (*ocupado)
        return true;
    else
        return false;
}

bool Schedule::horario_ocupado(int dia, int hora, SDL_Renderer *renderer, TTF_Font *font)
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

    char *pcliente = core->atendimento[dia][hora];
    if (*pcliente)
    {
        std::string message = "Horario ocupado por ";
        while (*pcliente)
        {
            message += *pcliente;
            pcliente++;
        }
        renderText(message.c_str(), 50, 50); // Adjust x and y as needed
        return true;
    }
    else
    {
        return false;
    }
}

void Schedule::abre_atendimento(Screen &screen, SDL_Renderer *renderer, TTF_Font *font)
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

    auto getInput = [](std::string input)
    {
        SDL_Event event;
        bool done = false;
        while (!done)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    done = true;
                    break;
                }
                else if (event.type == SDL_TEXTINPUT)
                {
                    input += event.text.text;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        done = true;
                    }
                    else if (event.key.keysym.sym == SDLK_BACKSPACE && !input.empty())
                    {
                        input.pop_back();
                    }
                }
            }
        }
    };

    std::string dia, hora, nome;
    int dia_inteiro;

    screen.clearScreen(renderer);
    SDL_Delay(500);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderText("*** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***", 50, 50);
    renderText("MARCAR ATENDIMENTO", 50, 100);
    renderText("INFORME O DIA .....: ", 50, 150);
    SDL_RenderPresent(renderer);

    getInput(dia);
    // SDL_RenderPresent(renderer);

    // do
    // {
    //     getInput(dia);
    //     dia_inteiro = std::stoi(dia);
    //     if (dia_inteiro >= 1 && dia_inteiro <= 31)
    //     {
    //         break;
    //     }
    //     renderText("Dia inválido. Pressione <Enter> para nova tentativa.", 50, 200);
    //     SDL_Event event;
    //     while (SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN)
    //         ;
    //     screen.clearLine(200, 50); // Clear the line where the error message was displayed
    // } while (dia_inteiro < 1 || dia_inteiro > 31);

    // renderText("INFORME A HORA ....: ", 50, 200);

    // do
    // {
    //     getInput(hora);
    //     int hora_inteiro = std::stoi(hora);
    //     if (hora_inteiro >= 8 && hora_inteiro <= 17)
    //     {
    //         break;
    //     }
    //     renderText("Hora inválida. Pressione <Enter> para nova tentativa.", 50, 250);
    //     SDL_Event event;
    //     while (SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN)
    //         ;
    //     screen.clearLine(250, 50); // Clear the line where the error message was displayed
    // } while (atoi(hora.c_str()) < 8 || atoi(hora.c_str()) > 17);

    // int hora_inteiro = std::stoi(hora);

    // if (horario_ocupado(dia_inteiro - 1, hora_inteiro - 8, renderer, font))
    // {
    //     renderText("Tecle <Enter> para voltar ao menu.", 50, 300);
    //     SDL_Event event;
    //     while (SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN)
    //         ;
    // }
    // else
    // {
    //     renderText("INFORME A NOME ....: ", 50, 300);
    //     getInput(nome);
    //     renderText("SUCESSO, REGISTRO ADICIONADO.", 50, 350);
    //     renderText("Tecle <Enter> para voltar ao menu.", 50, 400);
    //     marca_atendimento(dia_inteiro - 1, hora_inteiro - 8, nome.c_str());
    //     SDL_Event event;
    //     while (SDL_WaitEvent(&event) && event.type != SDL_KEYDOWN)
    //         ;
    // }
}

void Schedule::abre_desmarcacao(Screen &screen, SDL_Renderer *renderer,
                                TTF_Font *font)
{
    char dia[2], hora[2];
    int dia_inteiro;
    screen.clearScreen(renderer);
    screen.moveCursor(1, 1);
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << "                                                 DESMARCAR ATENDIMENTO                                    ";
    std::cout << std::endl
              << std::endl
              << std::endl;
    std::cout << " INFORME O DIA .....: ";
    do
    {
        std::cin >> dia;
        std::cin.ignore(80, '\n');
        if (atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        std::cout << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << " Dia inválido.";
        std::cout << std::endl
                  << " Pressione <Enter> para nova tentativa.";
        if (std::cin.get())
        {
            screen.moveCursor(23, 7);
            screen.clearLine(23, 7);
            screen.clearLine(1, 14);
            screen.clearLine(1, 15);
        }
    } while (atoi(dia) < 1 || atoi(dia) > 31);
    dia_inteiro = atoi(dia);
    std::cout << " INFORME A HORA ....: ";
    do
    {
        std::cin >> hora;
        std::cin.ignore(80, '\n');
        if (atoi(hora) >= 8 && atoi(hora) <= 17)
        {
            break;
        }
        std::cout << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << " Hora inválida.";
        std::cout << std::endl
                  << " Pressione <Enter> para nova tentativa.";
        if (std::cin.get())
        {
            screen.moveCursor(23, 8);
            screen.clearLine(23, 8);
            screen.clearLine(1, 15);
            screen.clearLine(1, 16);
        }
    } while (atoi(hora) < 8 || atoi(hora) > 17);
    int hora_inteiro = atoi(hora);
    if (horario_ocupado(dia_inteiro - 1, hora_inteiro - 8, renderer, font))
    {
        char resp;
        std::cout << std::endl
                  << "Desmarca? (S/N): ";
        std::cin >> resp;
        resp = toupper(resp);
        if (resp == 'S')
        {
            strcpy(core->atendimento[dia_inteiro - 1][hora_inteiro - 8], "");
        }
    }
    else
    {
        std::cout << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << " Horário livre.";
        std::cout << std::endl
                  << " Pressione <Enter> para voltar.";
        std::cin.get();
    }
}

void Schedule::lista_cliente(Screen &screen, SDL_Renderer *renderer,
                             TTF_Font *font)
{
    char dia[2];
    char *pcliente = 0;
    screen.clearScreen(renderer);
    screen.moveCursor(1, 1);
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << "                                                   CLIENTES DO DIA                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << " Informe o dia: ";
    do
    {
        std::cin >> dia;
        std::cin.ignore(80, '\n');
        if (atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        std::cout << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << " Dia inválido.";
        std::cout << std::endl
                  << " Pressione <Enter> para nova tentativa.";
        if (std::cin.get())
        {
            screen.moveCursor(17, 6);
            screen.clearLine(16, 6);
            screen.clearLine(1, 13);
            screen.clearLine(1, 14);
        }
    } while (atoi(dia) < 1 || atoi(dia) > 31);
    int dia_inteiro = atoi(dia);
    std::cout << " LISTAGEM DOS CLIENTES" << std::endl
              << std::endl;
    std::cout << std::setiosflags(std::ios::right);
    for (int i = 8; i <= 17; i++)
    {
        pcliente = core->atendimento[dia_inteiro - 1][i - 8];
        std::cout << " ";
        std::cout << std::setw(2) << i;
        std::cout << " HORAS   ";
        if (*pcliente)
            while (*pcliente)
            {
                std::cout.put(*pcliente);
                pcliente++;
            }
        std::cout << std::endl;
    }
    std::cout << std::endl
              << std::endl
              << " Tecle <Enter> para voltar ao menu.";
    std::cin.get();
}

void Schedule::horarios_cliente(Screen &screen, SDL_Renderer *renderer,
                                TTF_Font *font)
{
    screen.clearScreen(renderer);
    screen.moveCursor(1, 1);
    char nome[50];
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << "                                                HORÁRIOS DE UM CLIENTE                                    ";
    std::cout << std::endl
              << std::endl
              << std::endl;
    std::cout << " Entre o nome do cliente: ";
    std::cin.getline(nome, sizeof(nome));
    std::cout << std::endl
              << std::endl;
    std::cout << " Horário para o cliente " << nome << std::endl;
    std::setiosflags(std::ios::right);
    for (int i = 0; i <= 30; i++)
        for (int j = 8; j <= 17; j++)
        {
            {
                if (strcmp(nome, core->atendimento[i][j - 8]) == 0)
                    std::cout << " DIA " << std::setw(2) << i + 1 << " ÀS " << std::setw(2)
                              << j << " HORAS" << std::endl;
            }
        }
    std::cout << std::endl
              << std::endl
              << std::endl
              << " Tecle <Enter> para voltar ao menu.";
    std::cin.get();
}

void Schedule::mapa_horarios(Screen &screen, SDL_Renderer *renderer,
                             TTF_Font *font)
{
    screen.clearScreen(renderer);
    screen.moveCursor(1, 1);
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << "                                             MAPA DOS HORÁRIOS OCUPADOS                                    ";
    std::cout << std::endl
              << std::endl
              << std::endl;
    std::cout << "                                       HORA          1         2         3" << std::endl;
    std::cout << "                                            1234567890123456789012345678901" << std::endl;
    int linha = 9;
    std::cout << std::setiosflags(std::ios::right);
    for (int i = 8; i <= 17; i++)
    {
        screen.moveCursor(42, linha);
        std::cout << std::setw(2) << i << std::endl;
        linha++;
    }
    linha = 9;
    int coluna = 45;
    for (int i = 0; i <= 9; i++)
    {
        for (int j = 0; j <= 30; j++)
        {
            if (not mapa_ocupado(j, i))
            {
                screen.moveCursor(coluna, linha);
                std::cout << ".";
                coluna++;
            }
            else
            {
                screen.moveCursor(coluna, linha);
                std::cout << "*";
                coluna++;
            }
        }
        std::cout << std::endl;
        linha++;
        coluna = 45;
    }
    std::cout << std::endl
              << std::endl
              << std::endl
              << " Tecle <Enter> para voltar ao menu.";
    std::cin.get();
}
