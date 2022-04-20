#include <iostream>
#include "SGestao.h"
#include "virus.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#define DEBUG 1
#define delayBetweenMoves 501

#define _CRT_SECURE_NO_WARNINGS


int menu()
{
    char opcao{};
    do {
        cout << "\n--------------------->MENU<---------------------\n" << endl;
        cout << "\tA -> Carregar dados" << endl;
        cout << "\tB -> Mostrar dados" << endl;
        cout << "\tC -> Gravar dados no ficheiro XML" << endl;
        cout << "\tD -> Lancar Virus aleatorio em Pessoa aleatoria" << endl;
        cout << "\tE -> Mostrar Virus ativos e respetivos dados" << endl;
        cout << "\tF -> Ver se algum Virus foi extinto" << endl;
        cout << "\tG -> Mostrar Pessoas que faleceram" << endl;
        cout << "\tH -> Determinar a pessoa que mais contagios provocou" << endl;
        cout << "\tI -> Determinar a cidade mais infetada" << endl; // falta
        cout << "\tJ -> Mostrar Pessoas infetadas" << endl;
        cout << "\tL -> Determinar a idade que mais infencoes sofreu" << endl;
        cout << "\tM -> Determinar Pessoas com mais de um Virus" << endl;
        cout << "\tN -> Verificar se uma Pessoa teve contagio ( Na base de contagio)" << endl;
        cout << "\tO -> Se N ou mais pessoas estiverem muito juntas (num raio inferior a R) as pessoas devem ser alertadas" << endl;
        cout << "\tP -> Memoria Ocupada" << endl;
        cout << "\tQ -> Possivel Ir Ponto A ate Ponto B sem passar por pessoas infetadas " << endl;
        cout << "\tR -> Possivel Ir Ponto A ate Ponto B sem passar por dentro de qualquer zona de contágio" << endl;
        cout << "\tS -> Destruidor de Memoria" << endl;
        cout << "\tT -> Sair do Progama" << endl;
        cout << "\tEscolha uma opcao: ";
        cin >> opcao;
        system("cls");
    } while ((opcao == 'Z'));
    cout << "Opcao: ";
    cout << opcao;
    return opcao;
}

int main()
{
    srand(time(NULL));
    SGestao Gestor;
    char opcao;
    string nBi;
    int Raio;
    string ficheiro;
    string xml;
    int nIteracoes = 1;
    Gestor.Load("ficha.txt");
    Gestor.LoadVirus("virustipos.txt");
    Gestor.LoadCidades("fichaCidades.txt");
    Gestor.InfetarPessoas();
    do
    {   
        opcao = menu();
        switch (opcao)
        {
        case 'A':
            system("CLS");
            // Carregar os ficheiros com dados das pessoas e virus
            Gestor.Load("ficha.txt");
            Gestor.LoadVirus("virustipos.txt");
            Gestor.LoadCidades("fichaCidades.txt");
            cout << "Dados carregados com sucesso" << endl;
            break;
        case 'B':
            system("CLS");
            // Mostra Lista de Pessoas e Virus
            Gestor.mostrarListaPessoas();
            Gestor.mostrarListaVirus(); 
            break;
        case 'C':
            system("CLS");
            // Gravar XML
            cout << "\n\nQual o nome do ficheiro: " << endl;
            cin.ignore();
            getline(cin, ficheiro);
            cout << "\n\nQual o nome do xml: " << endl;
            cin.ignore();
            getline(cin, xml);
            Gestor.EscreverXML(ficheiro, xml);
            break;
        case 'D':
            system("CLS");
            // Infetar uma pessoa aleatoria com virus aleatorio
            Gestor.InfetarUmaPessoa();
            break;
        case 'E':
            system("CLS");
            cout << "Numero infetados totais desde o comeco das pandemias" << endl;
            Gestor.ContarNumeroInfetadosVirusX();
            break;
        case 'F':
            system("CLS");
            // Remover virus se nao houver infetados com virus
            Gestor.RemoverVirus();
            break;
        case 'G':
            system("CLS");
            cout << "Mostrar numero de falecimentos" << endl;
            Gestor.getMortes();
            Gestor.MostrarPessoasMortas();
            break;
        case 'H':
            system("CLS");
            //determinar a pessoa que mais infetou
            Gestor.DeterminarPessoaQmaisInfetou();
            break;
        case 'I':
            system("CLS");
            //determinar a cidade com mais casos
            Gestor.DeterminarCidadeComMaisCasos();
            break;
        case 'J':
            system("CLS");
            // Mostra infetados
            Gestor.getInfetados();
            Gestor.MostrarPessoasInfetadas();
            break;
        case 'L':
            system("CLS");
            // Idade mais Afetada
            Gestor.DeterminarIdadeMaisAfetada();
            break;
        case 'M':
            system("CLS");
            // Mostra Pessoas com mais de um virus
            Gestor.PessoaTemMaisdeUmVirus();
            break;
        case 'N':
            system("CLS");
            // ver se x pessoa tem virus
            cout << "\n\nQual o Bi da Pessoa: " << endl;
            cin.ignore();
            getline(cin, nBi);
            Gestor.PessoaFonteContagio(nBi);
            break;
        case 'O':
            system("CLS");
            cout << "\n\nVer as pessoas que estao dentro de um raio pedido tiveram em contacto com infetados" << endl;
            cout << "\n\nQual o Raio: " << endl;
            cin.ignore();
            cin >> Raio;
            Gestor.AlertasAsPessoasProximas(Raio);
            break;
        case 'P':
            system("CLS");
            Gestor.Memoria();
            Gestor.MemoriaComputador();
            break;
        case 'Q':
            system("CLS");
            Gestor.PossivelIr_A_B();
            break;
        case 'R':
            system("CLS");
            Gestor.Possivel_Zona_Ir_A_B();
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
            cout << "\nEscolha uma da opcoes disponiveis abaixo\n" << endl;
            menu();
        }
        while (nIteracoes<2)
        {
            Gestor.Mover_Atualizar();
            nIteracoes++;
        }
        Gestor.Mover_Atualizar();
        Gestor.AtualizarMortes();
        nIteracoes = 1;
    } while (!(opcao == 'U'))
    ;
} 