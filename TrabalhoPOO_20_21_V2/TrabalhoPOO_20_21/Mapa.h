#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>
#include "Uteis.h"
#include "Pessoa.h"

using namespace std;

#define PercInfetados 15
#define CHAR_0 '-'          // caracter para as posicoes 
#define CHAR_1 'X'          // caracter para as posicoes pess normais saudavel
#define CHAR_2 '*'          // caracter para as posicoes pess infetadas
#define CHAR_3 'Q'          // caracter para as posicoes pess quarentena
#define CHAR_4 'M'          // caracter para as posicoes pess mortas
//-> Varius Virus
class Pessoa;
class virus;

class Mapa
{
    int NL, NC, Npes;
    int* mapa;
    static int Nmortes;
    static int NPQuarentena;
    static int NInfetados;
    vector<pair<int, int>> LMov; // lista de movimentos possíveis   
    vector<Pessoa* >lista_Pessoas;
    

public:
    Mapa();
    virtual ~Mapa();
    int Get(int i, int j) { return mapa[i * NC + j]; };
    int Get(int pos) { return mapa[pos]; };
    int NumeroInfetados() { return NInfetados; }
    int NumeroQuarenta() { return NPQuarentena; }
    int NumeroMortes() { return Nmortes; }
    void Set(int i, int j, int x) { mapa[i * NC + j] = x; };
    void Set(int pos, int x) { mapa[pos] = x; }; // x-> + Virus
    bool Mover();
    bool posValida(int pos);
    bool posValida(int i, int j);
    void Mostrar();
    bool Gravar(string nf);
    static int Quarentena() { return NPQuarentena; }
    static int DeterminarMortes() { return Nmortes; }
    bool Probabilidade_morte = (rand() % 100) < 75; ///-> Taxa de perigo usar
    bool PessoasQuarentena = (rand() % 100) < 85; ///-> 85% Fazem quarentena ?
     // bool ColocarPessoas(); // Meter as Pessoas no Mapa
     //Pessoa find(string nome) const;
     //void AddPessoas(Pessoa& lista_Pessoas);
};

