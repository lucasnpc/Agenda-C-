#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include "Screen.h"
#include "Schedule.h"
#include "Menu.h"

struct winsize getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

int main(void) // Funcao principal
{
    Screen screen;
    Schedule schedule;
    Menu menu;

    char option[2];

    do
    {
        menu.renderMenu(screen);
        std::cin >> option;
        std::cin.ignore(80, '\n');
        switch (atoi(option))
        {
        case 1:
            schedule.abre_atendimento(screen);
            break;
        case 2:
            schedule.abre_desmarcacao(screen);
            break;
        case 3:
            schedule.lista_cliente(screen);
            break;
        case 4:
            schedule.horarios_cliente(screen);
            break;
        case 5:
            schedule.mapa_horarios(screen);
            break;
        case 6:
            exit(0);
        default:
            struct winsize w = getTerminalSize();
            int line = (w.ws_row / 2) + 3;
            int column = (w.ws_col / 2) - 9;
            screen.clearLine(line, column);
            screen.moveCursor(line, column);
        }
    } while (atoi(option) != 6);

    return 0;
}
