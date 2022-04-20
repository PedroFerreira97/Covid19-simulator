#pragma once
#include "main.h"
#include "virus.h"
#include "localizacao.h"
#include "Pessoa.h"
#include "Mapa.h"
class Pessoa;
class Virus;
class MapaP;

class SGestao
{
private:
	vector<virus* > lista_Virus;
	vector<Pessoa* > lista_Pessoas;
public:
	SGestao();
	~SGestao();
	bool Load(const char* fich);
	bool LoadVirus(const char* fich);
	void mostrarListaPessoas();
	void mostrarListaVirus();
	
	/*
	Pessoa* PessoaMaisContagios();
	int Contar(Virus *X);
	bool PessoaFonteContagio(const string& BI);
	int Memoria();
	void VirusMaisActivo();
	//void RemoverVirus(Virus* X);
	//void EscreverXML(const string& fich_xml);
	//string CidadeMaisCasos();
	//bool AlertasAsPessoasProximas(int N, double R);
	//int EscalaoIdadeMaisAfectado();
	void PessoasContagiadas(List<Pessoa*>& L);
	void PessoasMaisUmVirus(List<Pessoa*>& L);
	List<Ponto*>* PossivelIr_A_B(Ponto &A, Ponto &B);
	List<Ponto*>* Possivel_Zona_Ir_A_B(Ponto &A, Ponto &B);
	*/
};