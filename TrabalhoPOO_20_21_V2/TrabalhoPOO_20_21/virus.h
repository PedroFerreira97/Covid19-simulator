#pragma once
#include "main.h"

class virus
{
	private:
		string Nome_virus;
		double taxa_perigo;
		double taxa_contagio;
		double raio_contagio;
		int tipo;
		int NumeroDeInfetados;
	public:
		virus(string nome, double taxaperigo, double taxacontagio, double raiocontagio, int tipo_V);
		~virus();
		string GetNomevirus() { return Nome_virus;};
		double  GetTaxaperigo() { return taxa_perigo;};
		double  GetTaxacontagio() { return taxa_contagio;};
		double  GetRaiocontagio() { return raio_contagio;};
		int  GetTipovirus() { return tipo; };
		int GetNumeroDeInfetados() { return NumeroDeInfetados; };
		void MostarNumInfetados();
		void AumentarInfetados() { NumeroDeInfetados++; }
		void Infetados_Mortos() { NumeroDeInfetados--; }
		void mostrarVirus();
		const string data_virus();
};

