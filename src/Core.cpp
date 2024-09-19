#include "Core.h"
#include <iostream>
#include <fstream>
#include <iomanip>

char Core::atendimento[31][10][50] = {};

Core::Core()
{
    std::ifstream arquivo("../ARQUIVO.AGENDAMENTOS", std::ios::binary);
    if (arquivo.good())
    {
        arquivo.read(reinterpret_cast<char *>(&atendimento), sizeof(atendimento));
    }
    else
    {
        std::ofstream createFile("../ARQUIVO.AGENDAMENTOS", std::ios::binary);
    }
}

Core::~Core()
{
    std::ofstream arquivo("../ARQUIVO.AGENDAMENTOS", std::ios::binary);
    if (arquivo.is_open())
    {
        arquivo.write(reinterpret_cast<char *>(&atendimento), sizeof(atendimento));
        if (arquivo.fail())
        {
            std::cerr << "Error: Failed to write to file." << std::endl;
        }
        arquivo.flush();
        arquivo.close();
    }
}
