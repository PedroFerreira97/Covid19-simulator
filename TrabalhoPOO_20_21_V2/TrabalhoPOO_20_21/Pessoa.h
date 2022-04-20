#pragma once
#include "main.h"
class virus;

class Pessoa
{
private:
	string nome;
	int n_Bi;
	int idade;
	string cidade;
	static int NPessoas;
	int posX;
	int posY;
	bool infetada;
	bool avisada;
	bool viva;
	int QuantasContagiou;
	int NumVirus;
	vector<virus* > tipo;

public:
	Pessoa(string Nome, int Bi, int Idade, string Cidade, int posX, int posY);
	~Pessoa();
	string getNome() { return nome; };
	int getBi() { return n_Bi; };
	int getIdade() { return idade; };
	string getCidade() { return cidade; };
	void mostrarCidade() { cout << "Cidade\t" << cidade << endl; }
	void Infetar() { infetada = true; };
	void Avisada() { avisada = true; };
	bool SeEstaInfetada();
	bool SeEstaAvisada();
	void Morrer() { viva = false; };
	bool EstaViva();
	int ReturnarQTContagiou() { return QuantasContagiou;};
	void AumentarQuantasContagiou();
	void MostrarQuantasContagiou();
	void mostrarPessoa();
	static int GetNPessoas();
	int getX() { return posX; };
	int getY() { return posY; };
	void setX(int x) { posX = x; };
	void setY(int y) { posY = y; };
	void setTipo(virus* viruss) { tipo.push_back(viruss); NumVirus++; };
	virus* getVirus() { return tipo[0]; };
	int getNumVirus() { return NumVirus; };
	virus* getNVirus(int n) { return tipo[n]; };
};

