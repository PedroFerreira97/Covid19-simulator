#pragma once
#include "SGestao.h"
#include "main.h"

class virus
{
	private:
		string Nome_virus;
		double taxa_perigo;
		double taxa_contagio;
		double raio_contagio;
	public:
		virus(string nome, double taxaperigo, double taxacontagio, double raiocontagio);
		~virus();
		string GetNomevirus() { return Nome_virus;};
		double  GetTaxaperigo() { return taxa_perigo;};
		double  GetTaxacontagio() { return taxa_contagio;};
		double  GetRaiocontagio() { return raio_contagio;};
		void mostrarVirus();
		const string data_virus();
};

