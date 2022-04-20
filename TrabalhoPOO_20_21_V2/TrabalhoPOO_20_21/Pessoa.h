#pragma once
#include "SGestao.h"
#include "main.h"
#include "localizacao.h"
#include "Mapa.h"

class Pessoa
{

private:
	string nome;
	int n_Bi;
	int idade;
	string cidade;
	static int NPessoas;
	bool Infetada;

public:
	Pessoa(string Nome,int Bi, int Idade, string Cidade);
	~Pessoa();
	void SetTodos(string Nome, int Bi, int Idade, string Cidade);
	string getNome() { return nome; };
	int getBi() { return n_Bi; };
	int getIdade() { return idade; };
	string getCidade() { return cidade; };
	void mostrarPessoa();
	static int GetNPessoas() {
		cout << "\nNPessoas: " << NPessoas << endl;
		return NPessoas;
	}
	//int PessoaMaisContagios();
	//bool e_viva();


	/*
	bool TemVirus();
	bool TemMaisDeUmVirus();
	bool FoiContagiada();
	bool TeveContacto();
	void QueVirusTem();
	void Pessoas_Contagiadas();
	void EnviarAlerta();
	void VirusMaisActivo();
	void CidadeMaisCasos();
	*/
};

