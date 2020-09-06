#include <iostream>
#include <clocale>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

int main(void);
/*Esta classe e responsavel por fornecer funcionalidades extras ao codigo principal. Como limpar tela, linha e ajustar a posicao
do cursor*/
class func_auxiliares
{
    public:
        func_auxiliares();
        void limpatela();
        void limpalinha(int linha, int coluna);
        void voltacursor(int linha, int coluna);

    protected:

    private:
};
func_auxiliares::func_auxiliares()
{
}
void func_auxiliares::limpatela(void)
{
    HANDLE tela;
    DWORD escrita = 0;
    COORD pos;
    tela = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = 0;
    pos.Y = 0;
    FillConsoleOutputCharacter(tela, 32, 80*32, pos, &escrita);
    return;
}
void func_auxiliares::limpalinha(int linha, int coluna)
{
    HANDLE tela;
    DWORD escrita = 0;
    COORD pos;
    tela = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = linha - 1;
    pos.Y = coluna - 1;
    FillConsoleOutputCharacter(tela, 32, 80- pos.X, pos, &escrita);
    return;
}
void func_auxiliares::voltacursor(int linha, int coluna)
{
    HANDLE tela;
    COORD pos;
    tela = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = linha - 1;
    pos.Y = coluna - 1;
    SetConsoleCursorPosition(tela, pos);
    return;
}
/*Fim da classe*/

char atendimento[31][10][50];  //Esta e a variavel responsavel por armazenar todos os nomes, dias e horas
int controla_leitura_arquivo = 0; //Como o proprio nome diz, esta variavel controla a leitura do arquivo, para que ocorra apenas ao iniciar

void marca_atendimento(int dia, int hora, char nome[50]) //Procedimento utilizado para inserir dados na Matriz
{
    char *pnome = 0; pnome = nome;
    int i =0;
    while(*pnome){
        atendimento[dia][hora][i] = *pnome; pnome++; i++;
    }
}
bool horario_ocupado(int dia, int hora) //Funcao responsavel por procurar horarios ocupados
{
    char *pcliente = 0; pcliente = atendimento[dia][hora];
    if(*pcliente){
        cout << endl << endl << endl << endl << endl << endl << "Horario ocupado por ";
        while(*pcliente)
        {
            cout.put(*pcliente); pcliente++;
        }
        return true;
    }else
    {
        return false;
    }
}
bool mapa_ocupado(int dia, int hora) //Funcao responsavel por identificar pontos ocupados no mapa
{
    char *ocupado = 0; ocupado = atendimento[dia][hora];
    if(*ocupado)
        return true;
    else
        return false;
}
void abre_atendimento() //Procedimento responsavel por abrir a pagina para marcar atendimento
{
    char dia[2], hora[2], nome[50];
    int dia_inteiro;
    func_auxiliares funcoes;
    funcoes.limpatela(); funcoes.voltacursor(1,1);
    cout << endl;
    cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl << endl;
    cout << "                                                 MARCAR ATENDIMENTO                                    ";
    cout << endl << endl << endl;
    cout << " INFORME O DIA .....: ";
    do
    {
        cin >> dia;
        cin.ignore(80, '\n');
        if(atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        cout << endl << endl << endl << endl << endl << endl << " Dia inválido.";
        cout << endl << " Pressione <Enter> para nova tentativa.";
        if(cin.get())
        {
            funcoes.voltacursor(23,7); funcoes.limpalinha(23,7); funcoes.limpalinha(1,14); funcoes.limpalinha(1,15);
        }
    }while(atoi(dia) < 1 || atoi(dia) > 31);
    dia_inteiro = atoi(dia);
    cout << " INFORME A HORA ....: ";
    do
    {
        cin >> hora;
        cin.ignore(80, '\n');
        if(atoi(hora) >= 8 && atoi(hora) <= 17)
        {
            break;
        }
        cout << endl << endl << endl << endl << endl << endl << " Hora inválida.";
        cout << endl << " Pressione <Enter> para nova tentativa.";
        if(cin.get())
        {
            funcoes.voltacursor(23,8); funcoes.limpalinha(23,8); funcoes.limpalinha(1,15); funcoes.limpalinha(1,16);
        }
    }while(atoi(hora) < 8 || atoi(hora) > 17);
    int hora_inteiro = atoi(hora);
    if(horario_ocupado(dia_inteiro - 1, hora_inteiro - 8)){
            cout << endl << "Tecle <Enter> para voltar ao menu."; cin.get(); main();
    }else{
        cout << " INFORME A NOME ....: "; cin.getline(nome, sizeof(nome));
        cout << endl << endl << endl << endl << endl << endl << " SUCESSO, REGISTRO ADICIONADO." << endl;
        cout << " Tecle <Enter> para voltar ao menu.";
        marca_atendimento(dia_inteiro-1,hora_inteiro-8,nome);
        if(cin.get())
            main();
    }
}

void abre_desmarcacao() //Procedimento responsavel por abrir pagina para desmarcar atendimento
{
    char dia[2], hora[2];
    int dia_inteiro;
    func_auxiliares funcoes;
    funcoes.limpatela(); funcoes.voltacursor(1,1);
    cout << endl;
    cout << "                                    *** AGENDA PARA DESMARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl << endl;
    cout << "                                                 DESMARCAR ATENDIMENTO                                    ";
    cout << endl << endl << endl;
    cout << " INFORME O DIA .....: ";
    do
    {
        cin >> dia;
        cin.ignore(80, '\n');
        if(atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        cout << endl << endl << endl << endl << endl << endl << " Dia inválido.";
        cout << endl << " Pressione <Enter> para nova tentativa.";
        if(cin.get())
        {
            funcoes.voltacursor(23,7); funcoes.limpalinha(23,7); funcoes.limpalinha(1,14); funcoes.limpalinha(1,15);
        }
    }while(atoi(dia) < 1 || atoi(dia) > 31);
    dia_inteiro = atoi(dia);
    cout << " INFORME A HORA ....: ";
    do
    {
        cin >> hora;
        cin.ignore(80, '\n');
        if(atoi(hora) >= 8 && atoi(hora) <= 17)
        {
            break;
        }
        cout << endl << endl << endl << endl << endl << endl << " Hora inválida.";
        cout << endl << " Pressione <Enter> para nova tentativa.";
        if(cin.get())
        {
            funcoes.voltacursor(23,8); funcoes.limpalinha(23,8); funcoes.limpalinha(1,15); funcoes.limpalinha(1,16);
        }
    }while(atoi(hora) < 8 || atoi(hora) > 17);
    int hora_inteiro = atoi(hora);
    if(horario_ocupado(dia_inteiro - 1, hora_inteiro -8))
    {
        char resp;
        cout << endl << "Desmarca? (S/N): "; cin >> resp; resp = toupper(resp);
        if(resp == 'S')
        {
            strcpy(atendimento[dia_inteiro-1][hora_inteiro-8], "");
        }
        main();
    }
    else
    {
        cout << endl << endl << endl << endl << endl << endl << " Horário livre.";
        cout << endl << " Pressione <Enter> para voltar.";
        if(cin.get())
            main();
    }
}
void lista_cliente() //Procedimento responsavel por mostrar clientes em determinado horario
{
    char dia[2];
    char *pcliente = 0;
    func_auxiliares funcoes;
    funcoes.limpatela(); funcoes.voltacursor(1,1);
    cout << endl;
    cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl << endl;
    cout << "                                                   CLIENTES DO DIA                                    ";
    cout << endl << endl;
    cout << " Informe o dia: ";
    do
    {
        cin >> dia;
        cin.ignore(80, '\n');
        if(atoi(dia) >= 1 && atoi(dia) <= 31)
        {
            break;
        }
        cout << endl << endl << endl << endl << endl << endl << " Dia inválido.";
        cout << endl << " Pressione <Enter> para nova tentativa.";
        if(cin.get())
        {
            funcoes.voltacursor(17,6); funcoes.limpalinha(16,6); funcoes.limpalinha(1,13); funcoes.limpalinha(1,14);
        }
    }while(atoi(dia) < 1 || atoi(dia) > 31);
    int dia_inteiro = atoi(dia);
    cout << " LISTAGEM DOS CLIENTES" << endl << endl;
    cout << setiosflags(ios::right);
    for(int i = 8; i<= 17; i++)
    {
        pcliente = atendimento[dia_inteiro-1][i-8];
        cout << " ";
        cout << setw(2) << i;
        cout << " HORAS   ";
        if(*pcliente)
            while(*pcliente)
            {
                cout.put(*pcliente); pcliente++;
            }
        cout << endl;
    }
    cout << endl << endl << " Tecle <Enter> para voltar ao menu.";
    if(cin.get())
        main();
}
void horarios_cliente() //Procedimento responsavel por mostrar os horarios de cada cliente solicitado pelo usuario
{
    func_auxiliares funcoes;
    funcoes.limpatela(); funcoes.voltacursor(1,1);
    char nome[50];
    cout << endl;
    cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl << endl;
    cout << "                                                HORÁRIOS DE UM CLIENTE                                    ";
    cout << endl << endl << endl;
    cout << " Entre o nome do cliente: "; cin.getline(nome, sizeof(nome)); cout << endl << endl;
    cout << " Horário para o cliente " << nome << endl;
    setiosflags(ios::right);
    for(int i = 0; i<= 30;i++)
        for(int j = 8;j <= 17; j++)
    {
        {
            if(strcmp(nome, atendimento[i][j-8]) == 0)
                cout << " DIA " << setw (2) << i+1 << " ÀS " << setw(2)
                << j << " HORAS" << endl;
        }
    }
    cout << endl << endl << endl << " Tecle <Enter> para voltar ao menu.";
    if(cin.get())
        main();
}
void mapa_horarios() //Mapa que identifica os horarios ocupados e disponiveis no tempo em que a agenda esta disponivel
{

    func_auxiliares funcoes;
    funcoes.limpatela(); funcoes.voltacursor(1,1);
    cout << endl;
    cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl << endl;
    cout << "                                             MAPA DOS HORÁRIOS OCUPADOS                                    ";
    cout << endl << endl << endl;
    cout << "                                       HORA          1         2         3" << endl;
    cout << "                                            1234567890123456789012345678901" << endl;
    int linha = 9;
    cout << setiosflags(ios::right);
    for(int i = 8; i<= 17; i++)
    {
        funcoes.voltacursor(42,linha);
        cout << setw(2) << i << endl; linha ++;
    }
    linha = 9;
    int coluna = 45;
    for(int i = 0; i <= 9; i++)
    {
        for(int j = 0; j<= 30;j++)
        {
            if(not mapa_ocupado(j,i))
            {
                funcoes.voltacursor(coluna,linha); cout << "."; coluna++;
            }
            else
            {
                funcoes.voltacursor(coluna,linha); cout << "*"; coluna++;
            }
        }
        cout << endl; linha++; coluna = 45;
    }
    cout << endl << endl << endl << " Tecle <Enter> para voltar ao menu.";
    if(cin.get())
        main();
}
void escrevearquivo() //Procedimento que escreve os dados no arquivo
{
    fstream arquivo("ARQUIVO.LUCAS", ios::out | ios::binary);
    arquivo.write(reinterpret_cast<char*>(&atendimento), sizeof(atendimento)); arquivo.close();
}
int main(void) //Funcao principal
{
    if(controla_leitura_arquivo == 0)
    {
        fstream arquivo("ARQUIVO.LUCAS", ios::in | ios::binary);
        if(arquivo.good()){
            arquivo.read(reinterpret_cast<char*>(&atendimento), sizeof(atendimento)); controla_leitura_arquivo = 1;
        }else{
            arquivo.open("ARQUIVO.LUCAS", ios::out | ios::binary); controla_leitura_arquivo = 1;}
    }
    char option[2];
    func_auxiliares funcoes;
    funcoes.limpatela(); funcoes.voltacursor(1,1);
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    cout << endl;
    cout << "                                    *** AGENDA PARA MARCAÇÃO DE ATENDIMENTO ***                                    ";
    cout << endl << endl;
    cout << "                                                   MENU PRINCIPAL                                    ";
    cout << endl << endl << endl;
    cout << "                                          [1] MARCAR ATENDIMENTO" << endl;
    cout << "                                          [2] DESMARCAR ATENDIMENTO" << endl;
    cout << "                                          [3] LISTAR MARCAÇÕES DO DIA" << endl;
    cout << "                                          [4] CLIENTES MARCADOS NO DIA" << endl;
    cout << "                                          [5] MAPA DOS HORÁRIOS LIVRES" << endl;
    cout << "                                          [6] FIM DO PROGRAMA" << endl << endl;
    cout << "                                          ==> ";

    do{
      cin >> option;
      cin.ignore(80, '\n');
      switch(atoi(option))
      {
        case 1: abre_atendimento(); break;
        case 2: abre_desmarcacao(); break;
        case 3: lista_cliente();    break;
        case 4: horarios_cliente(); break;
        case 5: mapa_horarios();    break;
        case 6: escrevearquivo();   exit(0);
        default: funcoes.limpalinha(47,14); funcoes.voltacursor(47,14);
      }
    }while(atoi(option) != 6);

    return 0;
}

