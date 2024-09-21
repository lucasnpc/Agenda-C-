#include "Menu.h"
#include <iostream>

void Menu::renderMenu(Screen &screen)
{
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
}