#include "Pessoa.h"

int Pessoa::NPessoas = 0;


Pessoa::Pessoa(string nome, int n_Bi, int idade, string cidade)
{
	this->cidade = cidade;
	this->nome = nome;
	this->n_Bi = n_Bi;
	this->idade = idade;
	Pessoa::NPessoas++;
}

void Pessoa::SetTodos(string nome, int n_Bi, int idade, string cidade)
{
	this->cidade = cidade;
	this->nome = nome;
	this->n_Bi = n_Bi;
	this->idade = idade;
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

/*
bool Pessoa::e_viva()
{
	//return status != DEAD;
	return true;
}

int Pessoa::PessoaMaisContagios()
{
	for (int i = 0; i < NPessoas; i++)
	{
		return 0;
	}
	return 0;
}



bool Pessoa::TemVirus()
{
	return true;
}

bool Pessoa::TemMaisDeUmVirus()
{
	bool TemVirus = true;
	return true;
}

bool Pessoa::TeveContacto()
{
	//if ->pessoa tem virus && teve contacto 
	return true;
}

void Pessoa::EnviarAlerta()
{
	if (bool TeveContacto = true) {
		cout << "Enviar Alerta a Pessoa" << endl;
		cout << "Terá que realizar quarentena" << endl;
	}
}
	

bool Pessoa::FoiContagiada()
{
	if (bool TeveContacto = true) {
		return true;//-> Depende Virus (Gerar random probabilidae?!)
	}
	else {
		return false;
	}
}

void Pessoa::Pessoas_Contagiadas()
{
	//-> Conta pessoas todas contagiadas
	int contador = 0;
}

void Pessoa::VirusMaisActivo()
{
	//-> Conta o Virus que tem mais pessoas
	int contador = 0;
	
}

void Pessoa::CidadeMaisCasos()
{
	//-> Conta o Ciadade que tem mais pessoas contagiadas
	int contador = 0;
}

void Pessoa::QueVirusTem()
{
	if (bool TemMaisDeUmVirus = true) {
		cout << "Esta pessoa tem 2 virus" << endl;
	}
	if (bool TemVirus = true) {
		cout << "tem X Virus" << endl;
	}
	else {
		cout << "Nao tem virus" << endl;
	}
}*/


