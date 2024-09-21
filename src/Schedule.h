#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iomanip>
#include <fstream>
#include <functional>
#include "Screen.h"
#include "Core.h"

class Schedule
{
    static std::unique_ptr<Core> core;

public:
    static void marca_atendimento(const int dia, const int hora, const char nome[50]); // Procedimento utilizado para inserir dados na Matriz
    static bool horario_ocupado(int dia, int hora);                                    // Funcao responsavel por procurar horarios ocupados
    static bool mapa_ocupado(int dia, int hora);                                       // Funcao responsavel por identificar pontos ocupados no mapa
    static void abre_atendimento(Screen &screen);  // Procedimento responsavel por abrir a pagina para marcar atendimento
    static void abre_desmarcacao(Screen &screen);  // Procedimento responsavel por abrir a pagina para desmarcar atendimento
    static void lista_cliente(Screen &screen);     // Procedimento responsavel por mostrar clientes em determinado horario
    static void horarios_cliente(Screen &screen);  // Procedimento responsavel por mostrar os horarios de cada cliente solicitado pelo usuario
    static void mapa_horarios(Screen &screen);     // Mapa que identifica os horarios ocupados e disponiveis no tempo em que a agenda esta disponivel
};

#endif