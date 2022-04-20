#include "virus.h"

virus::virus(string Nome_virus, double taxa_perigo, double taxa_contagio, double raio_contagio, int tipo)
{
	this->Nome_virus = Nome_virus;
	this->taxa_perigo = taxa_perigo;
	this->taxa_contagio = taxa_contagio;
	this->raio_contagio = raio_contagio;
	this->tipo = tipo;
	NumeroDeInfetados = 0;
}

virus::~virus()
{
	Nome_virus.clear(); 
}


void virus::MostarNumInfetados()
{
	if (NumeroDeInfetados > 0) {
		cout << "Numero de infetados:" << NumeroDeInfetados << endl;
	}
	else
	{
		cout << "O virus esta extinto" << endl;
		cout << "\nNumero de infetados:" << NumeroDeInfetados << endl;
	};
}

void virus::mostrarVirus()
{
	cout << "\nNome: " << Nome_virus << "\nTaxa de Perigo: " << taxa_perigo << "\nTaxa de Contagio: " << taxa_contagio << "\nRaio de Contagio: " << raio_contagio << endl;
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
