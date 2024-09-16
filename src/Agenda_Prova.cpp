#include <iostream>
#include <clocale>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdio>
#include "ScreenFunctions.h"

using namespace std;

void buildMenu();

struct winsize getTerminalSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

char atendimento[31][10][50];     // Esta e a variavel responsavel por armazenar todos os nomes, dias e horas
int controla_leitura_arquivo = 0; // Como o proprio nome diz, esta variavel controla a leitura do arquivo, para que ocorra apenas ao iniciar

void marca_atendimento(int dia, int hora, char nome[50]) // Procedimento utilizado para inserir dados na Matriz
{
    char *pnome = 0;
    pnome = nome;
    int i = 0;
    while (*pnome)
    {
        std::cout << *pnome;
        atendimento[dia][hora][i] = *pnome;
        pnome++;
        i++;
    }
}
bool horario_ocupado(int dia, int hora) // Funcao responsavel por procurar horarios ocupados
{
    char *pcliente = 0;
    pcliente = atendimento[dia][hora];
    if (*pcliente)
    {
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << "Horario ocupado por ";
        while (*pcliente)
        {
            cout.put(*pcliente);
            pcliente++;
        }
        return true;
    }
    else
    {
        return false;
    }
}
bool mapa_ocupado(int dia, int hora) // Funcao responsavel por identificar pontos ocupados no mapa
{
    char *ocupado = 0;
    ocupado = atendimento[dia][hora];
    if (*ocupado)
        return true;
    else
        return false;
}
void abre_atendimento() // Procedimento responsavel por abrir a pagina para marcar atendimento
{
    char dia[2], hora[2], nome[50];
    int dia_inteiro;
    ScreenFunctions funcoes;
    funcoes.clearScreen();
    funcoes.moveCursor(1, 1);
    cout << endl;
    cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl
         << endl;
    cout << "                                                 MARCAR ATENDIMENTO                                    ";
    cout << endl
         << endl
         << endl;
    cout << " INFORME O DIA .....: ";
    do
    {
        cin >> dia;
        cin.ignore(80, '\n');
        if (atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " Dia inválido.";
        cout << endl
             << " Pressione <Enter> para nova tentativa.";
        if (cin.get())
        {
            funcoes.moveCursor(23, 7);
            funcoes.clearLine(23, 7);
            funcoes.clearLine(1, 14);
            funcoes.clearLine(1, 15);
        }
    } while (atoi(dia) < 1 || atoi(dia) > 31);
    dia_inteiro = atoi(dia);
    cout << " INFORME A HORA ....: ";
    do
    {
        cin >> hora;
        cin.ignore(80, '\n');
        if (atoi(hora) >= 8 && atoi(hora) <= 17)
        {
            break;
        }
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " Hora inválida.";
        cout << endl
             << " Pressione <Enter> para nova tentativa.";
        if (cin.get())
        {
            funcoes.moveCursor(23, 8);
            funcoes.clearLine(23, 8);
            funcoes.clearLine(1, 15);
            funcoes.clearLine(1, 16);
        }
    } while (atoi(hora) < 8 || atoi(hora) > 17);
    int hora_inteiro = atoi(hora);
    if (horario_ocupado(dia_inteiro - 1, hora_inteiro - 8))
    {
        cout << endl
             << "Tecle <Enter> para voltar ao menu.";
        cin.get();
        buildMenu();
    }
    else
    {
        cout << " INFORME A NOME ....: ";
        cin.getline(nome, sizeof(nome));
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " SUCESSO, REGISTRO ADICIONADO." << endl;
        cout << " Tecle <Enter> para voltar ao menu.";
        marca_atendimento(dia_inteiro - 1, hora_inteiro - 8, nome);
        if (cin.get())
            buildMenu();
    }
}

void abre_desmarcacao() // Procedimento responsavel por abrir pagina para desmarcar atendimento
{
    char dia[2], hora[2];
    int dia_inteiro;
    ScreenFunctions funcoes;
    funcoes.clearScreen();
    funcoes.moveCursor(1, 1);
    cout << endl;
    cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl
         << endl;
    cout << "                                                 DESMARCAR ATENDIMENTO                                    ";
    cout << endl
         << endl
         << endl;
    cout << " INFORME O DIA .....: ";
    do
    {
        cin >> dia;
        cin.ignore(80, '\n');
        if (atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " Dia inválido.";
        cout << endl
             << " Pressione <Enter> para nova tentativa.";
        if (cin.get())
        {
            funcoes.moveCursor(23, 7);
            funcoes.clearLine(23, 7);
            funcoes.clearLine(1, 14);
            funcoes.clearLine(1, 15);
        }
    } while (atoi(dia) < 1 || atoi(dia) > 31);
    dia_inteiro = atoi(dia);
    cout << " INFORME A HORA ....: ";
    do
    {
        cin >> hora;
        cin.ignore(80, '\n');
        if (atoi(hora) >= 8 && atoi(hora) <= 17)
        {
            break;
        }
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " Hora inválida.";
        cout << endl
             << " Pressione <Enter> para nova tentativa.";
        if (cin.get())
        {
            funcoes.moveCursor(23, 8);
            funcoes.clearLine(23, 8);
            funcoes.clearLine(1, 15);
            funcoes.clearLine(1, 16);
        }
    } while (atoi(hora) < 8 || atoi(hora) > 17);
    int hora_inteiro = atoi(hora);
    if (horario_ocupado(dia_inteiro - 1, hora_inteiro - 8))
    {
        char resp;
        cout << endl
             << "Desmarca? (S/N): ";
        cin >> resp;
        resp = toupper(resp);
        if (resp == 'S')
        {
            strcpy(atendimento[dia_inteiro - 1][hora_inteiro - 8], "");
        }
        buildMenu();
    }
    else
    {
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " Horário livre.";
        cout << endl
             << " Pressione <Enter> para voltar.";
        if (cin.get())
            buildMenu();
    }
}
void lista_cliente() // Procedimento responsavel por mostrar clientes em determinado horario
{
    char dia[2];
    char *pcliente = 0;
    ScreenFunctions funcoes;
    funcoes.clearScreen();
    funcoes.moveCursor(1, 1);
    cout << endl;
    cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl
         << endl;
    cout << "                                                   CLIENTES DO DIA                                    ";
    cout << endl
         << endl;
    cout << " Informe o dia: ";
    do
    {
        cin >> dia;
        cin.ignore(80, '\n');
        if (atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << " Dia inválido.";
        cout << endl
             << " Pressione <Enter> para nova tentativa.";
        if (cin.get())
        {
            funcoes.moveCursor(17, 6);
            funcoes.clearLine(16, 6);
            funcoes.clearLine(1, 13);
            funcoes.clearLine(1, 14);
        }
    } while (atoi(dia) < 1 || atoi(dia) > 31);
    int dia_inteiro = atoi(dia);
    cout << " LISTAGEM DOS CLIENTES" << endl
         << endl;
    cout << setiosflags(ios::right);
    for (int i = 8; i <= 17; i++)
    {
        pcliente = atendimento[dia_inteiro - 1][i - 8];
        cout << " ";
        cout << setw(2) << i;
        cout << " HORAS   ";
        if (*pcliente)
            while (*pcliente)
            {
                cout.put(*pcliente);
                pcliente++;
            }
        cout << endl;
    }
    cout << endl
         << endl
         << " Tecle <Enter> para voltar ao menu.";
    if (cin.get())
        buildMenu();
}
void horarios_cliente() // Procedimento responsavel por mostrar os horarios de cada cliente solicitado pelo usuario
{
    ScreenFunctions funcoes;
    funcoes.clearScreen();
    funcoes.moveCursor(1, 1);
    char nome[50];
    cout << endl;
    cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl
         << endl;
    cout << "                                                HORÁRIOS DE UM CLIENTE                                    ";
    cout << endl
         << endl
         << endl;
    cout << " Entre o nome do cliente: ";
    cin.getline(nome, sizeof(nome));
    cout << endl
         << endl;
    cout << " Horário para o cliente " << nome << endl;
    setiosflags(ios::right);
    for (int i = 0; i <= 30; i++)
        for (int j = 8; j <= 17; j++)
        {
            {
                if (strcmp(nome, atendimento[i][j - 8]) == 0)
                    cout << " DIA " << setw(2) << i + 1 << " ÀS " << setw(2)
                         << j << " HORAS" << endl;
            }
        }
    cout << endl
         << endl
         << endl
         << " Tecle <Enter> para voltar ao menu.";
    if (cin.get())
        buildMenu();
}
void mapa_horarios() // Mapa que identifica os horarios ocupados e disponiveis no tempo em que a agenda esta disponivel
{

    ScreenFunctions funcoes;
    funcoes.clearScreen();
    funcoes.moveCursor(1, 1);
    cout << endl;
    cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl
         << endl;
    cout << "                                             MAPA DOS HORÁRIOS OCUPADOS                                    ";
    cout << endl
         << endl
         << endl;
    cout << "                                       HORA          1         2         3" << endl;
    cout << "                                            1234567890123456789012345678901" << endl;
    int linha = 9;
    cout << setiosflags(ios::right);
    for (int i = 8; i <= 17; i++)
    {
        funcoes.moveCursor(42, linha);
        cout << setw(2) << i << endl;
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
                funcoes.moveCursor(coluna, linha);
                cout << ".";
                coluna++;
            }
            else
            {
                funcoes.moveCursor(coluna, linha);
                cout << "*";
                coluna++;
            }
        }
        cout << endl;
        linha++;
        coluna = 45;
    }
    cout << endl
         << endl
         << endl
         << " Tecle <Enter> para voltar ao menu.";
    if (cin.get())
        buildMenu();
}

void escrevearquivo() // Procedimento que escreve os dados no arquivo
{
    fstream arquivo("../ARQUIVO.AGENDAMENTOS", ios::out | ios::binary);
    arquivo.write(reinterpret_cast<char *>(&atendimento), sizeof(atendimento));
    arquivo.close();
}

void buildMenu()
{
    char option[2];
    ScreenFunctions funcoes;
    funcoes.clearScreen();
    funcoes.moveCursor(1, 1);
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
            abre_atendimento();
            break;
        case 2:
            abre_desmarcacao();
            break;
        case 3:
            lista_cliente();
            break;
        case 4:
            horarios_cliente();
            break;
        case 5:
            mapa_horarios();
            break;
        case 6:
            escrevearquivo();
            exit(0);
        default:
            struct winsize w = getTerminalSize();
            int line = (w.ws_row / 2) + 3;
            int column = (w.ws_col / 2) - 9;
            funcoes.clearLine(line, column);
            funcoes.moveCursor(line, column);
        }
    } while (atoi(option) != 6);
}

int main(void) // Funcao principal
{
    fstream arquivo("../ARQUIVO.AGENDAMENTOS", ios::in | ios::binary);
    if (arquivo.good())
    {
        arquivo.read(reinterpret_cast<char *>(&atendimento), sizeof(atendimento));
    }
    else
    {
        arquivo.open("../ARQUIVO.AGENDAMENTOS", ios::out | ios::binary);
    }

    buildMenu();

    return 0;
}
