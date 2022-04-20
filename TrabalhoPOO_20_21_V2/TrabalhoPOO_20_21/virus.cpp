#include "virus.h"
#include <ctime>
#include <time.h>
#include "main.h"

virus::virus(string nome, double taxaperigo, double taxacontagio, double raiocontagio)
{
	this->Nome_virus = nome;
	this->taxa_perigo = taxaperigo;
	this->taxa_contagio = taxacontagio;
	this->raio_contagio = raiocontagio;
}

virus::~virus()
{
	Nome_virus.clear();
}


void virus::mostrarVirus()
{
	cout << "\nNome: " << Nome_virus << "\nTaxa de Perigo: " << taxa_perigo << "\nTaxa de Contagio: " << taxa_contagio << "\nRaio de Contagio: " << raio_contagio << endl;
	cout << "\n----- " << endl;
}

const string virus::data_virus()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}
