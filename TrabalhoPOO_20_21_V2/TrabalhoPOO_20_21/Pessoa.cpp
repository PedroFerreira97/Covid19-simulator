#include "Pessoa.h"
int Pessoa::NPessoas = 0;

Pessoa::Pessoa(string nome, int n_Bi, int idade, string cidade, int posX, int posY)
{
	NumVirus = 0;
	this->cidade = cidade;
	this->nome = nome;
	this->n_Bi = n_Bi;
	this->idade = idade;
	this->posX = posX;
	this->posY = posY;
	infetada = false;
	viva = true;
	avisada = false;
	QuantasContagiou = 0;
	NumVirus = 0;
	tipo;
	Pessoa::NPessoas++;
}

Pessoa::~Pessoa()
{
	nome.clear();
	cidade.clear();
}

void Pessoa::mostrarPessoa()
{
	cout << "\nNome: " << nome << "\tIdade: " << idade << "\tCidade: " << cidade << "\tBi: " << n_Bi << endl;
}

int Pessoa::GetNPessoas()
{
	cout << "\nNPessoas: " << NPessoas << endl;
	return NPessoas;
}

void Pessoa::MostrarQuantasContagiou()
{
	cout << "\nContagiou: " << QuantasContagiou << endl;
}

void Pessoa::AumentarQuantasContagiou()
{
	QuantasContagiou++;
};

bool Pessoa::SeEstaInfetada()
{
	if (infetada == true)
	{
		return true;
	}
	else {
		return false;
	}
}

bool Pessoa::SeEstaAvisada()
{
	if (avisada == true)
	{
		return true;
	}
	else {
		return false;
	}
}

bool Pessoa::EstaViva()
{
	if (viva == true)
	{
		return true;
	}
	else {
		return false;
	}
}




