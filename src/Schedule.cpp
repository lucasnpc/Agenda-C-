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

bool Schedule::horario_ocupado(int dia, int hora)
{
    char *pcliente = 0;
    pcliente = core->atendimento[dia][hora];
    if (*pcliente)
    {
        std::cout << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << "Horario ocupado por ";
        while (*pcliente)
        {
            std::cout.put(*pcliente);
            pcliente++;
        }
        return true;
    }
    else
    {
        return false;
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

void Schedule::abre_atendimento(Screen &screen)
{
    char dia[2], hora[2], nome[50];
    int dia_inteiro;
    screen.clearScreen();
    screen.moveCursor(1, 1);
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    std::cout << std::endl
              << std::endl;
    std::cout << "                                                 MARCAR ATENDIMENTO                                    ";
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
    if (horario_ocupado(dia_inteiro - 1, hora_inteiro - 8))
    {
        std::cout << std::endl
                  << "Tecle <Enter> para voltar ao menu.";
        std::cin.get();
    }
    else
    {
        std::cout << " INFORME A NOME ....: ";
        std::cin.getline(nome, sizeof(nome));
        std::cout << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << std::endl
                  << " SUCESSO, REGISTRO ADICIONADO." << std::endl;
        std::cout << " Tecle <Enter> para voltar ao menu.";
        marca_atendimento(dia_inteiro - 1, hora_inteiro - 8, nome);
        std::cin.get();
    }
}

void Schedule::abre_desmarcacao(Screen &screen)
{
    char dia[2], hora[2];
    int dia_inteiro;
    screen.clearScreen();
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
    if (horario_ocupado(dia_inteiro - 1, hora_inteiro - 8))
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

void Schedule::lista_cliente(Screen &screen)
{
    char dia[2];
    char *pcliente = 0;
    screen.clearScreen();
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

void Schedule::horarios_cliente(Screen &screen)
{
    screen.clearScreen();
    screen.moveCursor(1, 1);
    char nome[50];
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
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

void Schedule::mapa_horarios(Screen &screen)
{
    screen.clearScreen();
    screen.moveCursor(1, 1);
    std::cout << std::endl;
    std::cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
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
