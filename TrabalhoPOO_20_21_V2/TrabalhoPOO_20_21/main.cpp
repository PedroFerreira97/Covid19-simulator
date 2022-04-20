#include <iostream>
#include "SGestao.h"
#include "virus.h"
#include "Mapa.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#define DEBUG 1
#define delayBetweenMoves 501

#define _CRT_SECURE_NO_WARNINGS

int menu()
{
    Mapa mp;
    mp.Mostrar();
    mp.Gravar("..\\MapaFic.txt");
    int nIteracoes = 6;
    //while (nIteracoes < 5)
    //while (true)
 
    char opcao{};
    do {
        cout << "\n--------------------->MENU<---------------------\n" << endl;
        cout << "\tA -> Carregar dados" << endl;
        cout << "\tB -> Mostrar dados" << endl;
        cout << "\tC -> Gravar dados" << endl;
        cout << "\tD -> Lançar Virus aleatório em Pessoa aleatoria" << endl;
        cout << "\tE -> Mostrar Virus mais ativo" << endl;
        cout << "\tF -> Remover Virus" << endl;
        cout << "\tG -> Mostrar Pessoas que faleceram" << endl;
        cout << "\tH -> Determinar a pessoa que mais contagios provocou" << endl;
        cout << "\tI -> Determinar a cidade mais infetada" << endl;
        cout << "\tJ -> Mostrar Pessoas infetadas" << endl;
        cout << "\tL -> Determinar a idade mais infetada" << endl;
        cout << "\tM -> Determinar Pessoas com mais de um Virus" << endl;
        cout << "\tN -> Contar numero de Virus de um Tipo" << endl;
        cout << "\tO -> Verificar se uma Pessoa teve contágio" << endl;
        cout << "\tP -> Mostrar Virus mais ativo" << endl;
        cout << "\tQ -> Memoria Ocupada" << endl;
        cout << "\tR -> Mostrar Pessoas em quarentena" << endl;
        cout << "\tS -> Destruidor de Memoria" << endl;
        cout << "\tT -> Sair do Progama" << endl;
        cout << "\tEscolha uma opcao: ";
        cin >> opcao;
        system("cls");
    } while ((opcao == 'Z'));
    cout << "Opcao: ";
    cout << opcao;
    return opcao;
    while (nIteracoes < 5)
    {
        Uteis::wait(delayBetweenMoves);
        nIteracoes++;
        mp.Mover();
        if (DEBUG)
            mp.Mostrar();
        mp.Gravar("..\\MapaFic.txt");
    }
}

int main()
{
    char opcao;
    SGestao Gestor;
    string ficheiro;
    do
    {   
        srand((unsigned int)time(NULL));
        opcao = menu();
        switch (opcao)
        {
        case 'A':
            system("CLS");
            Gestor.Load("ficha.txt");
            Gestor.mostrarListaPessoas();
            //Adiciona e Mostra Pessoas e o Nº Total de pessoas
            break;
        case 'B':
            system("CLS");
            // Load do txt com dados do Virus
            Gestor.LoadVirus("virustipos.txt");
            Gestor.mostrarListaVirus(); 
            break;
        case 'C':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'D':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'E':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'F':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'G':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'H':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'I':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'J':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'L':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'M':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'N':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'O':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'P':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'Q':
            system("CLS");
            cout << "123 123" << endl;
            break;
        case 'R':
            system("CLS");
            cout << "123" << endl;
            break;
        case 'S':
            system("CLS");
            Gestor.~SGestao();
            cout << "Memoria libertada";
            break;
        case 'T':
            cout << "\nVolte Sempre!\n";
            return 0;
        default:
            system("CLS");
            cout << "\n----->ATENCAO<-----" << endl;;
            cout << "\nOpcao Invalida" << endl;;
            cout << "\nEscolha uma da opcoes disponiveis abaixo\n" << endl;;
            main();
        } 
    } while (!(opcao == 'T'));
} 