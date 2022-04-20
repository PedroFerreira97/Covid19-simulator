#include "Cidade.h"

Cidade::Cidade(string NomeCidade)
{
	this->nome = NomeCidade;
}

Cidade::~Cidade()
{
	nome.clear();
}
