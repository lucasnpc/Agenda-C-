#include <iostream>
#include <clocale>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include "Screen.h"
#include "Schedule.h"

void buildMenu();
Screen screen;
Schedule schedule;

struct winsize getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

void buildMenu()
{
    char option[2];
    screen.clearScreen();
    screen.moveCursor(1, 1);
    setlocale(LC_ALL, "pt_BR.UTF-8");
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << "                                                   MENU PRINCIPAL                                    ";
    std::cout << std::endl
              << std::endl
              << std::endl;
    std::cout << "                                          [1] MARCAR ATENDIMENTO" << std::endl;
    std::cout << "                                          [2] DESMARCAR ATENDIMENTO" << std::endl;
    std::cout << "                                          [3] LISTAR MARCAÇÕES DO DIA" << std::endl;
    std::cout << "                                          [4] CLIENTES MARCADOS NO DIA" << std::endl;
    std::cout << "                                          [5] MAPA DOS HORÁRIOS LIVRES" << std::endl;
    std::cout << "                                          [6] FIM DO PROGRAMA" << std::endl
              << std::endl;
    std::cout << "                                          ==> ";

    do
    {
        std::cin >> option;
        std::cin.ignore(80, '\n');
        switch (atoi(option))
        {
        case 1:
            schedule.abre_atendimento(
                screen, []()
                { buildMenu(); });
            break;
        case 2:
            schedule.abre_desmarcacao(
                screen, []()
                { buildMenu(); });
            break;
        case 3:
            schedule.lista_cliente(
                screen, []()
                { buildMenu(); });
            break;
        case 4:
            schedule.horarios_cliente(
                screen, []()
                { buildMenu(); });
            break;
        case 5:
            schedule.mapa_horarios(
                screen, []()
                { buildMenu(); });
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
}

int main(void) // Funcao principal
{
    screen = Screen();
    schedule = Schedule();
    buildMenu();

    return 0;
}
