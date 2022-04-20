#include "SGestao.h"

SGestao::SGestao()
{
}

SGestao::~SGestao()
{
}

bool SGestao::Load(const char* fich)
{
	string nome;
	int Bi;
	string cidade;
	int idade;
	string ficha = fich;
	ifstream in(ficha);
	if (!in.is_open())
	{
		cout << "Impossível abrir" << endl;
		return false;
	}

	char buffer[256];

	while (!in.eof())
	{
		//Obter linha n
		in.getline(buffer, 256);

		//Obter Bi
		char* token = strtok(buffer, "\t");
		Bi = atoi(token);

		//Obter nome
		token = strtok(NULL, "\t");
		nome = token;

		//Obter cidade
		token = strtok(NULL, "\t");
		cidade = token;

		//Obter idade
		token = strtok(NULL, "\t");
		idade = atoi(token);

		Pessoa* P = new Pessoa(nome, Bi, idade, cidade);
		lista_Pessoas.push_back(P);

	}
	in.close();
	return 0;
}

void SGestao::mostrarListaPessoas()
{
	for (Pessoa* P : lista_Pessoas)
	{
		P->mostrarPessoa();
	}
	Pessoa::GetNPessoas();
}

bool SGestao::LoadVirus(const char* fich)
{
	string Nome_virus;
	double taxa_perigo;
	double taxa_contagio;
	double raio_contagio;
	string virustipos = fich;
	ifstream in(virustipos);
	if (!in.is_open())
	{
		cout << "Impossivel abrir" << endl;
		return false;
	}

	char buffer[256];

	while (!in.eof())
	{
		//Obter linha n
		in.getline(buffer, 256);

		//Obter Nome virus
		char* token = strtok(buffer, "\t");
		Nome_virus = token;

		//Obter taxa_perigo
		token = strtok(NULL, "\t");
		taxa_perigo = atof(token);

		//Obter taxa_contagio
		token = strtok(NULL, "\t");
		taxa_contagio = atof(token);

		//Obter raio_contagio
		token = strtok(NULL, "\t");
		raio_contagio = atoi(token);

		virus* V = new virus(Nome_virus, taxa_perigo, taxa_contagio, raio_contagio);
		lista_Virus.push_back(V);

	}
	in.close();
	return 0;
}

void SGestao::mostrarListaVirus()
{
	for (virus* V : lista_Virus)
	{
		V->mostrarVirus();
	}
}




/*Pessoa* SGestao::PessoaMaisContagios()
{
	return nullptr;
}








int SGestao::Contar(Virus* X)


bool SGestao::PessoaFonteContagio(const string& BI)


//int SGestao::Memoria()




void SGestao::PessoasContagiadas(List<Pessoa *> &L)
{

}


void SGestao::PessoasMaisUmVirus(List<Pessoa *> &L)
{

}*/

//void SGestao::RemoverVirus(Virus* X)

//void SGestao::EscreverXML(const string& fich_xml)


//string SGestao::CidadeMaisCasos()


//bool SGestao::AlertasAsPessoasProximas(int N, double R)


//int SGestao::EscalaoIdadeMaisAfectado()


/*List<Ponto *>* SGestao::PossivelIr_A_B(Ponto &A, Ponto &B)
{

}

List<Ponto *>* SGestao::Possivel_Zona_Ir_A_B(Ponto &A, Ponto &B)
{

}*/




