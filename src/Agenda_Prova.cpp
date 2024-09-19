#include <iostream>
#include <clocale>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include "ScreenFunctions.h"
#include "Schedule.h"

void buildMenu();

struct winsize getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

void buildMenu()
{
    ScreenFunctions functions;
    Schedule schedule;
    char option[2];
    functions.clearScreen();
    functions.moveCursor(1, 1);
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
                functions, []()
                { buildMenu(); });
            break;
        case 2:
            schedule.abre_desmarcacao(
                functions, []()
                { buildMenu(); });
            break;
        case 3:
            schedule.lista_cliente(
                functions, []()
                { buildMenu(); });
            break;
        case 4:
            schedule.horarios_cliente(
                functions, []()
                { buildMenu(); });
            break;
        case 5:
            schedule.mapa_horarios(
                functions, []()
                { buildMenu(); });
            break;
        case 6:
            schedule.escrevearquivo();
            exit(0);
        default:
            struct winsize w = getTerminalSize();
            int line = (w.ws_row / 2) + 3;
            int column = (w.ws_col / 2) - 9;
            functions.clearLine(line, column);
            functions.moveCursor(line, column);
        }
    } while (atoi(option) != 6);
}

int main(void) // Funcao principal
{
    Schedule schedule;
    std::fstream arquivo("../ARQUIVO.AGENDAMENTOS", std::ios::in | std::ios::binary);
    if (arquivo.good())
    {
        arquivo.read(reinterpret_cast<char *>(&schedule.atendimento), sizeof(schedule.atendimento));
    }
    else
    {
        arquivo.open("../ARQUIVO.AGENDAMENTOS", std::ios::out | std::ios::binary);
    }

    buildMenu();

    return 0;
}
