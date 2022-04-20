#pragma once
#include "main.h"

class Cidade
{
private:
	string nome;
	int Ninfetados = 0;
public:
	Cidade(string Nome);
	~Cidade();
	string getNome() { return nome; };
	int getInfetados() { return Ninfetados; };
	void AumentarInfetados() { Ninfetados++; };
	void mostrarCidade() { cout << "Cidade\t" << nome << endl; }
};

