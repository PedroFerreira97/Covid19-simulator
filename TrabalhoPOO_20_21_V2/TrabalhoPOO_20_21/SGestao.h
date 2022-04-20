#pragma once
#include "main.h"
#include "Uteis.h"
#include "virus.h"
#include "Cidade.h"
#include "Pessoa.h"
#define MaxColunas 500
#define MaxLinhas 500
#define PercInfetados 15


class SGestao
{
private:
	vector<virus* > lista_Virus;
	vector<Pessoa* > lista_Pessoas;
	vector<Pessoa* > lista_PessoasInfetadas;
	vector<Pessoa* > lista_PessoasMortas;
	vector<Pessoa* > listaPessoasComMaisdeUmVirus;
	vector<Cidade* > lista_Cidades;
	vector<pair<int, int> > ListaPontos;
	Pessoa* mapa[MaxLinhas][MaxColunas];
	vector<pair<int, int>> LMov;
	int CidadeMaisCasosNumero = 0;
public:
	SGestao();
	~SGestao();
	void desenhaMapa();
	bool Load(const char* fich);
	void mostrarListaPessoas();
	bool LoadCidades(const char* fich);
	bool LoadVirus(const char* fich);
	void mostrarListaVirus();
	void mostrarListaCidades();
	bool Mover_Atualizar();
	bool AtualizarMortes();
	void PessoaTemMaisdeUmVirus();
	bool posValida(int i, int j);
	bool InfetarPessoas();
	bool InfetarUmaPessoa();
	void ContarNumeroInfetadosVirusX();
	void DeterminarIdadeMaisAfetada();
	void DeterminarPessoaQmaisInfetou();
	void DeterminarCidadeComMaisCasos();
	void RemoverVirus();
	void MostrarPessoasInfetadas();
	int getMortes() { return lista_PessoasMortas.size(); };
	void MostrarPessoasMortas();
	int getInfetados() { return lista_PessoasInfetadas.size(); };
	bool PessoaFonteContagio(const string& BI);
	bool AlertasAsPessoasProximas(double R);
	void EscreverXML(const string& fich, const string& fich_xml);
	void MemoriaComputador();
	double Memoria();
	int PossivelIr_A_B();
	int Possivel_Zona_Ir_A_B();
	bool Caminho(int arr[MaxLinhas][MaxColunas]);
};