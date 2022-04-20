#include "Mapa.h"
int Mapa::Nmortes = 0;
int Mapa::NPQuarentena = 0;
int Mapa::NInfetados = 0;

Mapa::Mapa()
{
    cout << "INICIO " << endl;
    NL = 40;
    NC = 30;
    Npes = 20;
    mapa = new int[NC * NL];


    for (int i = 0; i < NC * NL; ++i)
        mapa[i] = 0;

    double NInf = (double)Npes * PercInfetados / 100.0;
    int pos;

    for (int i = 0; i < Npes; ++i)
    {
        do {
            pos = Uteis::Aleatorio(NC * NL);

        } while (Get(pos));
        Set(pos, 1);
    }

    for (int i = 0; i < NInf; ++i) // distribui pessoas infetadas pelo mapa
    {
        do {
            pos = Uteis::Aleatorio(NC * NL);
        } while (Get(pos));
        Set(pos, 2); ///-> + virus
        Mapa::NInfetados++;

        if (PessoasQuarentena == true) // Fazer quarentena
        {
            Set(pos, 3);
            Mapa::NPQuarentena++;
            //cout << "\nA pessoa X está fazer 14 dias de quarentena" << endl;
        }
        else
        {
            cout << "------Mensagem Urgente-------" << endl;
            cout << "\nA pessoa X(N_bi) tem que fazer 14 dias de quarentena" << endl;
            cout << "\nObrigado" << endl;
            cout << "---------------------------" << endl;
        }

        if (Probabilidade_morte == false) //25% probabilidade de morrerem
        {
            Set(pos, 4);
            Mapa::Nmortes++;
            //bool dead = true
        }
        //If bool dead = true 
        //Tirar do mapa
    }

    //LMov // movimentos possíveis
    LMov.push_back(make_pair(0, 1));
    LMov.push_back(make_pair(0, -1));
    LMov.push_back(make_pair(1, 0));
    LMov.push_back(make_pair(-1, 0));
    LMov.push_back(make_pair(0, 0));
    LMov.push_back(make_pair(0, 0));

    cout << " --- Criado mapa com " << NL << " linhas e " << NC << " colunas." << endl;
    cout << " --- Foram colocadas " << Npes << " pessoas no Mapa " << NInf << " infetadas e " << Npes - NInf << " limpinhas)!" << endl;
    cout << " --- numero de movimentos possiveis = " << LMov.size() << endl;
    cout << "FIM" << endl;
}

Mapa::~Mapa()
{
    cout << "Passou em" << endl;
    delete[]mapa;
}

bool Mapa::Mover()
{
    int* mapaNew;
    int iNew, jNew;
    pair<int, int> mov;
    mapaNew = new int[NC * NL];
    for (int i = 0; i < NC * NL; ++i)
        mapaNew[i] = 0;
    // move todas as pessoas...
    for (int i = 0; i < NL; ++i)
        for (int j = 0; j < NC; ++j)
            if (Get(i, j))// se existe pessoa nesta posição
            {
                //cout << "estou na posicao ( " << i << " , " << j << " ) = " << Get(i,j) << endl;
                do {
                    mov = LMov[Uteis::Aleatorio(LMov.size() - 1)];
                    iNew = i + mov.first;
                    jNew = j + mov.second;
                } while (!posValida(iNew, jNew) || (mapaNew[iNew * NC + jNew]));
                mapaNew[iNew * NC + jNew] = Get(i, j);
            }
    delete[]mapa;
    mapa = mapaNew;
    return true;

}

void Mapa::Mostrar()
{
    cout << "MAPA ATUAL:" << endl;
    for (int i = 0; i < NL; ++i)
    {
        cout << "\t\t";
        for (int j = 0; j < NC; ++j)
            cout << " " << Get(i, j);
        cout << endl;
    }
    cout << "FIM " << endl;
}

bool Mapa::posValida(int pos)
{
    if (pos < 0)
        return false;
    if (pos >= NL * NC)
        return false;
    return true;
    return (pos >= 0) && (pos < NL* NC);
}

bool Mapa::posValida(int i, int j)
{
    if ((i < 0) || (i >= NL))
        return false;
    if ((j < 0) || (i >= NC))
        return false;
    return true;
    return (i >= 0) && (i < NL) && (j >= 0) && (j < NC);
}

bool Mapa::Gravar(string nf)
{
    cout << "estou no metodo X" << endl;
    char Char_[5];
    Char_[0] = CHAR_0;  //Espaço
    Char_[1] = CHAR_1;  //Pessoa
    Char_[2] = CHAR_2;  //Infetados
    Char_[3] = CHAR_3;  //Quanrenta
    Char_[4] = CHAR_4;  //Mortos

    ofstream Fic(nf.c_str());
    if (!Fic.is_open())
    {
        cout << "Erro ao abrir ficheiro" << endl;
        return false;
    };
    Fic << NL << " " << NC << endl;
    for (int i = 0; i < NL; ++i)
    {
        for (int j = 0; j < NC; ++j)
            Fic << Char_[Get(i, j)];
        Fic << endl;
    }
    Fic.close();
    return true;
}



