#include "SGestao.h"
#define WIDTH 7
#define DIV 1048576
#define MAX_SIZE 16382
#include<windows.h>
#include<stdio.h>   
#include<tchar.h>
#include <queue>
int arr[MaxLinhas][MaxColunas];

SGestao::SGestao()
{
	for (int i = 0; i < MaxLinhas; i++)
	{
		for (int j = 0; j < MaxColunas; j++)
		{
			mapa[i][j] = NULL;
		}
	}

	LMov.push_back(make_pair(0, 1));
	LMov.push_back(make_pair(0, -1));
	LMov.push_back(make_pair(1, 0));
	LMov.push_back(make_pair(-1, 0));
	LMov.push_back(make_pair(0, 0));
	LMov.push_back(make_pair(0, 0));
}

SGestao::~SGestao()
{
	for (Pessoa* P : lista_Pessoas)
	{
		P->~Pessoa();
	}
	for (Pessoa* P : lista_PessoasInfetadas)
	{
		P->~Pessoa();
	}
	for (Pessoa* P : listaPessoasComMaisdeUmVirus)
	{
		P->~Pessoa();
	}
	for (Pessoa* P : lista_PessoasMortas)
	{
		P->~Pessoa();
	}
	for (Cidade* C : lista_Cidades)
	{
		C->~Cidade();
	}
	for (virus* V : lista_Virus)
	{
		V->~virus();
	}
	lista_Virus.clear();
	lista_Pessoas.clear();
	lista_PessoasInfetadas.clear();
	lista_PessoasMortas.clear();
	listaPessoasComMaisdeUmVirus.clear();
	lista_Cidades.clear();
	ListaPontos.clear();
	LMov.clear();
}

bool SGestao::Load(const char* fich)
{
	string nome;
	int Bi;
	string cidade;
	int idade;
	string ficha = fich;
	srand(time_t(NULL));
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

		Pessoa* P = new Pessoa(nome, Bi, idade, cidade, rand() % MaxLinhas, rand() % MaxColunas);
		lista_Pessoas.push_back(P);

	}
	in.close();

	for (Pessoa* P : lista_Pessoas)
	{
		mapa[P->getX()][P->getY()] = P;
	}

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

void SGestao::mostrarListaCidades()
{
	for (Cidade* C : lista_Cidades)
	{
		C->mostrarCidade();
	}
}

bool SGestao::LoadCidades(const char* fich)
{
	string nome;
	int Bi;
	string cidade;
	int idade;
	string ficha = fich;
	srand(time_t(NULL));
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

		Cidade* C = new Cidade(cidade);
		lista_Cidades.push_back(C);

	}
	in.close();

	return 0;
}

void SGestao::desenhaMapa()
{
	for (int i = 0; i < MaxLinhas; i++)
	{
		for (int j = 0; j < MaxColunas; j++)
		{
			if (mapa[i][j] != NULL)
				cout << "P";
			//Lista -> "I"
			else
				cout << "0";
		}
		cout << endl;
	}
}

bool SGestao::LoadVirus(const char* fich)
{
	string Nome_virus;
	double taxa_perigo;
	double taxa_contagio;
	double raio_contagio;
	int tipo;
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

		token = strtok(NULL, "\t");
		tipo = atoi(token);

		virus* V = new virus(Nome_virus, taxa_perigo, taxa_contagio, raio_contagio, tipo);
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

bool SGestao::AtualizarMortes()
{
	// Probabilidade das Pessoas Infetadas Morrer (Aumenta dependete da Idade) ( Estatiticas retiradas da internet [x + %dependenteIdade])
	for (int i = 0; i < lista_PessoasInfetadas.size(); i++)
	{
		double x;
		Pessoa* P = lista_PessoasInfetadas[i];
		x = P->getVirus()->GetTaxaperigo();

		if (P->getIdade() < 60)
		{
			bool Morte = (rand() % 100) < x * 100;

			if (Morte == false)
			{
				P->Morrer();
				mapa[P->getX()][P->getY()] = NULL;
				lista_PessoasMortas.push_back(P);
				P->getVirus()->Infetados_Mortos();
				lista_PessoasInfetadas.erase(lista_PessoasInfetadas.begin() + i);
			}
		}
		if (P->getIdade() >= 60 && P->getIdade() < 69)
		{
			bool Morte = (rand() % 100) < (x + 0.02) * 100;

			if (Morte == false)
			{
				P->Morrer();
				mapa[P->getX()][P->getY()] = NULL;
				lista_PessoasMortas.push_back(P);
				P->getVirus()->Infetados_Mortos();
				lista_PessoasInfetadas.erase(lista_PessoasInfetadas.begin() + i);
			}
		}
		if (P->getIdade() >= 70 && P->getIdade() < 79)
		{
			bool Morte = (rand() % 100) < (x + 0.08) * 100;

			if (Morte == false)
			{
				P->Morrer();
				mapa[P->getX()][P->getY()] = NULL;
				lista_PessoasMortas.push_back(P);
				P->getVirus()->Infetados_Mortos();
				lista_PessoasInfetadas.erase(lista_PessoasInfetadas.begin() + i);
			}
		}
		if (P->getIdade() > 80)
		{
			bool Morte = (rand() % 100) < (x + 0.15) * 100;

			if (Morte == false)
			{
				P->Morrer();
				mapa[P->getX()][P->getY()] = NULL;
				lista_PessoasMortas.push_back(P);
				P->getVirus()->Infetados_Mortos();
				lista_PessoasInfetadas.erase(lista_PessoasInfetadas.begin() + i);
			}
		}
	}
	return true;
}

bool SGestao::Mover_Atualizar()
{
	pair<int, int> mov;
	int iNew, jNew;
	int x;
	int y;

			for (Pessoa* P : lista_Pessoas)  // Mover Pessoas
			{
				do {
					mov = LMov[Uteis::Aleatorio(LMov.size() - 1)];
					iNew = P->getX() + mov.first;
					jNew = P->getY() + mov.second;
				} while (!posValida(iNew, jNew));
				x = P->getX();
				y = P->getY();
				P->setX(iNew);
				P->setY(jNew);
				mapa[x][y] = NULL;
				mapa[iNew][jNew] = P;
			}
			
			for (Pessoa* P : lista_Pessoas)
			{
				if (P->SeEstaInfetada() == true && P->EstaViva() == true )
				{
					int x, y;
					x = P->getX();
					y = P->getY();
					int c = 0;
					int n;
					n = P->getNumVirus();
					if (x + 1 < (MaxLinhas - 2) && y < (MaxColunas - 2) && x > 0 && y > 0 && mapa[x + 1][y] != NULL)
					{
						while (n > 0) // A pessoa a infetar pode ter mais que um virus
						{
							c = P->getNVirus(n - 1)->GetTaxacontagio();
							P->getNVirus(n - 1)->AumentarInfetados();
							bool Infetar = (rand() % 100) < (c * 100);
							if (mapa[x + 1][y]->SeEstaInfetada() == false && mapa[x + 1][y]->EstaViva() == true) // Se nao tem virus -> infetar 
							{
								if (Infetar == false)
								{
									P->getNVirus(n - 1)->AumentarInfetados();
									P->AumentarQuantasContagiou();
									mapa[x + 1][y]->Infetar();
									mapa[x + 1][y]->setTipo(P->getNVirus(n - 1));
									lista_PessoasInfetadas.push_back(mapa[x + 1][y]);
								}
							}
							if (mapa[x + 1][y]->SeEstaInfetada() == true) // Se  tem virus -> infetar 
							{
								if (mapa[x + 1][y]->getVirus()->GetTipovirus() != P->getNVirus(n - 1)->GetTipovirus() && mapa[x + 1][y]->EstaViva() == true)
								{
									if (Infetar == false)
									{
										P->getNVirus(n - 1)->AumentarInfetados();
										P->AumentarQuantasContagiou();
										mapa[x + 1][y]->setTipo(P->getNVirus(n - 1));
										listaPessoasComMaisdeUmVirus.push_back(mapa[x + 1][y]);
									}
								}
							}
							n--;
						}
						n = P->getNumVirus();
					}
					if (x < (MaxLinhas -1) && y + 1 < (MaxColunas - 1) && x > 0 && y > 0 && mapa[x][y + 1] != NULL)
					{
						while (n > 0) // A pessoa a infetar pode ter mais que um virus
						{
							c = P->getNVirus(n - 1)->GetTaxacontagio();
							P->getNVirus(n - 1)->AumentarInfetados();
							bool Infetar = (rand() % 100) < (c * 100);
							if (mapa[x][y + 1]->SeEstaInfetada() == false && mapa[x][y + 1]->EstaViva() == true) // Se nao tem virus -> infetar 
							{
								if (Infetar == false)
								{
									P->getNVirus(n - 1)->AumentarInfetados();
									P->AumentarQuantasContagiou();
									mapa[x][y + 1]->Infetar();
									mapa[x][y + 1]->setTipo(P->getNVirus(n - 1));
									lista_PessoasInfetadas.push_back(mapa[x][y + 1]);
								}
							}
							if (mapa[x][y + 1]->SeEstaInfetada() == true) // Se  tem virus -> infetar 
							{
								if (mapa[x][y + 1]->getVirus()->GetTipovirus() != P->getNVirus(n - 1)->GetTipovirus() && mapa[x][y + 1]->EstaViva() == true)
								{
									if (Infetar == false)
									{
										P->getNVirus(n - 1)->AumentarInfetados();
										P->AumentarQuantasContagiou();
										mapa[x][y + 1]->setTipo(P->getNVirus(n - 1));
										listaPessoasComMaisdeUmVirus.push_back(mapa[x][y + 1]);
									}
								}
							}
							n--;
						}
						n = P->getNumVirus();
					}
					if (x < (MaxLinhas -1 ) && y < (MaxColunas - 1) && x > 0 && y - 1 > 0 && mapa[x][y - 1] != NULL)
					{
						while (n > 0) // A pessoa a infetar pode ter mais que um virus
						{
							c = P->getNVirus(n - 1)->GetTaxacontagio();
							P->getNVirus(n - 1)->AumentarInfetados();
							bool Infetar = (rand() % 100) < (c * 100);
							if (mapa[x][y - 1]->SeEstaInfetada() == false && mapa[x][y - 1]->EstaViva() == true) // Se nao tem virus -> infetar 
							{
								if (Infetar == false)
								{
									P->getNVirus(n - 1)->AumentarInfetados();
									P->AumentarQuantasContagiou();
									mapa[x][y - 1]->Infetar();
									mapa[x][y - 1]->setTipo(P->getNVirus(n - 1));
									lista_PessoasInfetadas.push_back(mapa[x][y - 1]);
								}
							}
							if (mapa[x][y - 1]->SeEstaInfetada() == true) // Se  tem virus -> infetar 
							{
								if (mapa[x][y - 1]->getVirus()->GetTipovirus() != P->getNVirus(n - 1)->GetTipovirus() && mapa[x][y - 1]->EstaViva() == true)
								{
									if (Infetar == false)
									{
										P->getNVirus(n - 1)->AumentarInfetados();
										P->AumentarQuantasContagiou();
										mapa[x][y - 1]->setTipo(P->getNVirus(n - 1));
										listaPessoasComMaisdeUmVirus.push_back(mapa[x][y - 1]);
									}
								}
							}
							n--;
						}
						n = P->getNumVirus();
					}
					
					if (x < (MaxLinhas - 1) && y < (MaxColunas - 1) && x - 1 > 0 && y > 0 && mapa[x - 1][y] != NULL)
					{
						while (n > 0) // A pessoa a infetar pode ter mais que um virus
						{
							c = P->getNVirus(n - 1)->GetTaxacontagio();
							P->getNVirus(n - 1)->AumentarInfetados();
							bool Infetar = (rand() % 100) < (c * 100);
							if (mapa[x - 1][y]->SeEstaInfetada() == false && mapa[x - 1][y]->EstaViva() == true) // Se nao tem virus -> infetar 
							{
								if (Infetar == false)
								{
									P->getNVirus(n - 1)->AumentarInfetados();
									P->AumentarQuantasContagiou();
									mapa[x - 1][y]->Infetar();
									mapa[x - 1][y]->setTipo(P->getNVirus(n - 1));
									lista_PessoasInfetadas.push_back(mapa[x - 1][y]);
								}
							}
							if (mapa[x - 1][y]->SeEstaInfetada() == true) // Se  tem virus -> infetar 
							{
								if (mapa[x - 1][y]->getVirus()->GetTipovirus() != P->getNVirus(n - 1)->GetTipovirus() && mapa[x - 1][y]->EstaViva() == true)
								{
									if (Infetar == false)
									{
										P->getNVirus(n - 1)->AumentarInfetados();
										P->AumentarQuantasContagiou();
										mapa[x - 1][y]->setTipo(P->getNVirus(n - 1));
										listaPessoasComMaisdeUmVirus.push_back(mapa[x - 1][y]);
									}
								}
							}
							n--;
						}
						n = P->getNumVirus();
					}
				}
			}
	return true;
}

bool SGestao::InfetarPessoas()
{
	double NInf = (double)lista_Pessoas.size() * PercInfetados / 100.0;
	srand(time(NULL));
	for (int i = 0; i < NInf; ++i)
	{
		int x;
		int y;
		//y = Uteis::Aleatorio(0, 4);
		//x = Uteis::Aleatorio(lista_Pessoas.size());
		y = rand() % 4;
		x = rand() % lista_Pessoas.size();//+1?
		lista_Pessoas[x]->Infetar();
		lista_PessoasInfetadas.push_back(lista_Pessoas[x]);
		lista_Pessoas[x]->setTipo(lista_Virus[y]);
		lista_Virus[y]->AumentarInfetados();
	}
	return true;
}

bool SGestao::InfetarUmaPessoa()
{
	srand(time(NULL));
	int x;
	int y;	
	y = rand() % 4;
	x = rand() % lista_Pessoas.size();
	lista_Pessoas[x]->Infetar();
	lista_PessoasInfetadas.push_back(lista_Pessoas[x]);
	lista_Pessoas[x]->setTipo(lista_Virus[y]);
	lista_Virus[y]->AumentarInfetados();
	cout << "Foi infetada a Pessoa: " << lista_Pessoas[x]->getNome() << "." << endl;
	cout << "Com o virus: " << lista_Virus[y]->GetNomevirus() << "." << endl;
	return true;
}

void SGestao::ContarNumeroInfetadosVirusX()
{
	int Maior = 0 ;
	string nome;

	for (virus* V : lista_Virus)
	{
		V->mostrarVirus();
		V->MostarNumInfetados();
	}

	for (int unsigned i = 0; i < unsigned(lista_Virus.size()); i++)
	{
		if (lista_Virus[i]->GetNumeroDeInfetados() > Maior)
		{
			Maior = lista_Virus[i]->GetNumeroDeInfetados();
			nome = lista_Virus[i]->GetNomevirus();
		}
	}
	cout << "\nO virus com mais infetados e:" << nome << endl;
	cout << "Tem\t" << Maior << "\tinfetados" << endl;
}

void SGestao::DeterminarIdadeMaisAfetada()
{
	int Maior = 0;
	int IdadeMaisAfetada[11] = { 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int Menorque10 = 0;
	int Idade10_19 = 0;
	int Idade20_29 = 0;
	int Idade30_39 = 0;
	int Idade40_49 = 0;
	int Idade50_59 = 0;
	int Idade60_69 = 0;
	int Idade70_79 = 0;
	int Idade80_89 = 0;
	int Idade90oumais = 0;

	for (Pessoa* P : lista_PessoasInfetadas)
	{
		if (P->getIdade() < 10)
		{
			Menorque10++;
		}
		if (P->getIdade() >= 10 && P->getIdade() < 20)
		{
			Idade10_19++;
		}
		if (P->getIdade() >= 20 && P->getIdade() < 30)
		{
			Idade20_29++;
		}
		if (P->getIdade() >= 30 && P->getIdade() < 40)
		{
			Idade30_39++;
		}
		if (P->getIdade() >= 40 && P->getIdade() < 50)
		{
			Idade40_49++;
		}
		if (P->getIdade() >= 50 && P->getIdade() < 60)
		{
			Idade50_59++;
		}
		if (P->getIdade() >= 60 && P->getIdade() < 70)
		{
			Idade60_69++;
		}
		if (P->getIdade() >= 70 && P->getIdade() < 80)
		{
			Idade70_79++;
		}
		if (P->getIdade() >= 80 && P->getIdade() < 90)
		{
			Idade80_89++;
		}
		if (P->getIdade() >= 90)
		{
			Idade90oumais++;
		}
		IdadeMaisAfetada[0] = Menorque10;
		IdadeMaisAfetada[1] = Idade10_19;
		IdadeMaisAfetada[3] = Idade20_29;
		IdadeMaisAfetada[4] = Idade30_39;
		IdadeMaisAfetada[5] = Idade40_49;
		IdadeMaisAfetada[6] = Idade50_59;
		IdadeMaisAfetada[7] = Idade60_69;
		IdadeMaisAfetada[8] = Idade70_79;
		IdadeMaisAfetada[9] = Idade80_89;
		IdadeMaisAfetada[10] = Idade90oumais;
	}

	for (int i = 0; i < 11; i++)
	{
		if (IdadeMaisAfetada[i] > Maior)
		{
			Maior = IdadeMaisAfetada[i];
		}	
	}
	if (Maior == Menorque10)
	{
		cout << "O escalao de idade mais afetada e 0 aos 9 anos" << endl;
	}
	if (Maior == Idade10_19)
	{
		cout << "O escalao de idade mais afetada e 10 aos 19 anos" << endl;
	}
	if (Maior == Idade20_29)
	{
		cout << "O escalao de idade mais afetada e 20 aos 29 anos" << endl;
	}
	if (Maior == Idade30_39)
	{
		cout << "O escalao de idade mais afetada e 30 aos 39 anos" << endl;
	}
	if (Maior == Idade40_49)
	{
		cout << "O escalao de idade mais afetada e 40 aos 49 anos" << endl;
	}
	if (Maior == Idade50_59)
	{
		cout << "O escalao de idade mais afetada e 50 aos 59 anos" << endl;
	}
	if (Maior == Idade60_69)
	{
		cout << "O escalao de idade mais afetada e 60 aos 69 anos" << endl;
	}
	if (Maior == Idade70_79)
	{
		cout << "O escalao de idade mais afetada e 70 aos 79 anos" << endl;
	}
	if (Maior == Idade80_89)
	{
		cout << "O escalao de idade mais afetada e 80 aos 89 anos" << endl;
	}
	if (Maior == Idade90oumais)
	{
		cout << "O escalao de idade mais afetada e 90 ou mais anos" << endl;
	}
	cout << "Com o numero de Infedos para essa idade de:" << Maior << endl;
}

void SGestao::DeterminarPessoaQmaisInfetou()
{
	int Maior=0;
	string nome;
	int bi=0;
	string cidade;
	int idade=0;

	for (int  i = 0 ; i < lista_PessoasInfetadas.size() ; i++)
	{
		if (lista_PessoasInfetadas[i]->ReturnarQTContagiou() > Maior)
		{
			Maior = lista_PessoasInfetadas[i]->ReturnarQTContagiou();
			nome = lista_PessoasInfetadas[i]->getNome();
			bi = lista_PessoasInfetadas[i]->getBi();
			cidade  = lista_PessoasInfetadas[i]->getCidade() ;
			idade = lista_PessoasInfetadas[i]->getIdade();
		}
	}
	if (Maior > 0)
	{
		cout << "A pessoa que mais contagiou foi" << endl;
		cout << "Nome: " << nome << "\tBi:" << bi << "\tCidade:" << cidade << "\tIdade:" << idade << endl;
		cout << "\tcontagiou:\t" << Maior << "\tpessoas." << endl;
	}
	else
	{
		cout << "Ainda ninguem infetou ninguem" << endl;
	}
}

void SGestao::DeterminarCidadeComMaisCasos()
{
	string maisInfetados;
	for (Cidade* C : lista_Cidades)
	{
		string NomeCidade;
		NomeCidade = C->getNome();
		for (Pessoa* P : lista_PessoasInfetadas)
		{
			if (P->getCidade() == NomeCidade)
			{
				C->AumentarInfetados();
			}
		}
	}
	for (int i = 0; i < lista_Cidades.size() ; i++)
	{
		int num = 0;
		if (lista_Cidades[i]->getInfetados() > num)
		{
			maisInfetados = lista_Cidades[i]->getNome();
			num = lista_Cidades[i]->getInfetados();
		}
	}
	cout << "Cidade com mais casos e: " << maisInfetados << " ." << endl;
}

void SGestao::RemoverVirus()
{
	for (int i = 0 ; i < lista_Virus.size() ; i++)
	{
		if (lista_Virus[i]->GetNumeroDeInfetados() == 0)
		{
			cout << "O virus: " << lista_Virus[i]->GetNomevirus() << "\tfoi extinto pois ja nao existem casos do mesmo" << endl;
			lista_Virus.erase(lista_Virus.begin() + i);
		}
		else
		{
			cout << "O virus: " << lista_Virus[i]->GetNomevirus() << "\testa ativo" << endl;
		}
	}
}

void SGestao::PessoaTemMaisdeUmVirus()
{
	for (Pessoa* P : listaPessoasComMaisdeUmVirus)
	{
		P->mostrarPessoa();
	}
	cout << "Numero de Pessoas com mais de um virus:" << listaPessoasComMaisdeUmVirus.size() << endl;
}

bool SGestao::posValida(int i, int j)
{
	return (i >= 0) && (i < MaxLinhas) && (j >= 0) && (j < MaxColunas);
}

void SGestao::MostrarPessoasInfetadas()
{
	for (Pessoa* P : lista_PessoasInfetadas)
	{
		P->mostrarPessoa();
	}
	cout << "Numero de Infetados:" << lista_PessoasInfetadas.size() << endl;
}

void SGestao::MostrarPessoasMortas()
{
	for (Pessoa* P : lista_PessoasMortas)
	{
		P->mostrarPessoa();
	}
	cout << "Numero de Mortes:" << lista_PessoasMortas.size() << endl;
}

void SGestao::MemoriaComputador()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	_tprintf(TEXT("Estou a usar %*ld percentagem de memoria.\n"), WIDTH, statex.dwMemoryLoad);
	_tprintf(TEXT("Tenho %*I64d total Mbytes de memoria fisica.\n"), WIDTH, statex.ullTotalPhys / DIV);
	_tprintf(TEXT("Tenho %*I64d livres Mbytes de memoria fisica.\n"), WIDTH, statex.ullAvailPhys / DIV);
	_tprintf(TEXT("Tenho %*I64d total Mbytes de memoria virtual.\n"), WIDTH, statex.ullTotalVirtual / DIV);
	_tprintf(TEXT("Tenho %*I64d livres Mbytes de memoria virtual.\n"), WIDTH, statex.ullAvailVirtual / DIV);
	_tprintf(TEXT("Tenho %*I64d livres Mbytes de memoria extendida.\n"), WIDTH, statex.ullAvailExtendedVirtual / DIV);
}

double SGestao::Memoria()
{
	double memoria = 0;
	memoria += double(sizeof(SGestao));
	memoria += double(sizeof(Pessoa)) * double(lista_Pessoas.size());
	memoria += double(sizeof(Pessoa)) * double(lista_PessoasInfetadas.size());
	memoria += double(sizeof(Pessoa)) * double(lista_PessoasMortas.size());
	memoria += double(sizeof(Pessoa)) * double(listaPessoasComMaisdeUmVirus.size());
	memoria += double(sizeof(virus)) * double(lista_Virus.size());
	memoria += double(sizeof(Cidade)) * double(lista_Cidades.size());
	cout <<"Memoria do progama : " << memoria << endl;
	return memoria;
}

bool SGestao::PessoaFonteContagio(const string& BI)
{
	int NumBi = stoi(BI);
	int x;
	int y;
	for (Pessoa* P : lista_Pessoas)
	{
		if (NumBi == P->getBi())
		{
			x = P->getX();
			y = P->getY();
			if (x + 1 < (MaxLinhas - 1) && y < (MaxColunas - 1) && x > 0 && y > 0 && mapa[x + 1][y] != NULL)
			{
				if (mapa[x + 1][y]->SeEstaInfetada() == true) // Se a Pessoa perto tiver virus
				{
					cout << "Sim! A pessoa com nome " << P->getNome() << " e Bi " << P->getBi() << endl;
					cout << "Esteve em contacto com " << mapa[x + 1][y]->getNome() << "que esta infetada" << endl;
					cout << "Devera fazer a quarentena" << endl;
					cout << "Sistema: ENVIAR MENSAGEM" << endl;
					return true;
				}
			}
			if (x < (MaxLinhas - 1) && y < (MaxColunas - 1) && x - 1 > 0 && y > 0 && mapa[x - 1][y] != NULL)
			{
				if (mapa[x - 1][y]->SeEstaInfetada() == true) // Se a Pessoa perto tiver virus
				{
					cout << "Sim! A pessoa com nome " << P->getNome() << " e Bi " << P->getBi() << endl;
					cout << "Esteve em contacto com " << mapa[x - 1][y]->getNome() << "que esta infetada" << endl;
					cout << "Devera fazer a quarentena" << endl;
					cout << "Sistema: ENVIAR MENSAGEM" << endl;
					return true;
				}
			}
			if (x < (MaxLinhas - 1) && y + 1 < (MaxColunas - 1) && x > 0 && y > 0 && mapa[x][y + 1] != NULL)
			{
				if (mapa[x][y + 1]->SeEstaInfetada() == true) // Se a Pessoa perto tiver virus
				{
					cout << "Sim! A pessoa com nome " << P->getNome() << " e Bi " << P->getBi() << endl;
					cout << "Esteve em contacto com " << mapa[x][y + 1]->getNome() << "que esta infetada" << endl;
					cout << "Devera fazer a quarentena" << endl;
					cout << "Sistema: ENVIAR MENSAGEM" << endl;
					return true;
				}
			}
			if (x < (MaxLinhas - 1) && y < (MaxColunas - 1) && x > 0 && y - 1 > 0 && mapa[x][y - 1] != NULL)
			{
				if (mapa[x][y -1]->SeEstaInfetada() == true) // Se a Pessoa perto tiver virus
				{
					cout << "Sim! A pessoa com nome " << P->getNome() << " e Bi " << P->getBi() << endl;
					cout << "Esteve em contacto com" << mapa[x][y - 1]->getNome() << "que esta infetada" << endl;
					cout << "Devera fazer a quarentena" << endl;
					cout << "Sistema: ENVIAR MENSAGEM" << endl;
					return true;
				}
			}
			else
			{
				cout << "Nao esteve em contacto com nenhuma pessoa infetada" << endl; 
				return false;
			}
		}
		else {
			cout << "Nao existe esse BI" << endl;
			return false;
		}
	}
	return true;
}

bool SGestao::AlertasAsPessoasProximas(double R)
{
	int x;
	int y, cont=0;
	int raio = (int)R;
	int raio2;
	raio2 = raio;
	for (Pessoa* P : lista_PessoasInfetadas)
	{
		x = P->getX();
		y = P->getY();
		for ( int i = x -raio ; i < x + raio ; i++)
			for (int j = y - raio; j < y + raio; j++)
			{
				if(i < (MaxLinhas - 1) && j < (MaxColunas - 1) && i > 0 && j > 0 && mapa[i][j] != NULL && (i != x || j != y))
				{
					if (mapa[i][j]->SeEstaInfetada() == false && mapa[i][j]->SeEstaAvisada() == false)
					{
						mapa[i][j]->Avisada();
					}
				}
			}	
	}
	cout << "As pessoas dentro raio defenido foram avisadas" << endl;
	cout << cont << endl;
	return true;
}

bool SGestao::Caminho(int arr[MaxLinhas][MaxColunas])
{
	int Xini;
	int Yini;
	int DestX;
	int DestY;
	cout << "Diga as coordenadas Partida" << endl;
	cout << "X:" << endl;
	cin >> Xini;
	if (Xini > MaxLinhas && Xini < 0)
	{
		cout << "Esse numero nao e legivel" << endl;
		return false;
	}
	cout << "Y:" << endl;
	cin >> Yini;
	if (Yini > MaxColunas && Yini < 0)
	{
		cout << "Esse numero nao e legivel" << endl;
		return false;
	}
	cout << "Diga as coordenadas da Chegada" << endl;
	cout << "X:" << endl;
	cin >> DestX;
	if (DestX > MaxLinhas && DestX < 0)
	{
		cout << "Esse numero nao e legivel" << endl;
		return false;
	}
	cout << "Y:" << endl;
	cin >> DestY;
	if (DestY > MaxColunas && DestY < 0)
	{
		cout << "Esse numero nao e legivel" << endl;
		return false;
	}

	//direçoes possiveis
	int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

	//queue 
	queue <pair<int, int> > q;
	
	q.push(make_pair(Xini, Yini)); // Ponto de Partida----------------

	//até queque estar vazia
	while (q.size() > 0)
	{
		pair<int, int> p = q.front();
		q.pop();

		//visitou -1 -> "valor" dos infetados e posiçoes ja visitadas
		arr[p.first][p.second] = -1;

		//Chegou Destino---------------------------
		if (p == make_pair(DestX - 1, DestY - 1))
			return true;

		//Verificar as direçoes
		for (int i = 0; i < 4; i++)
		{
			//usar os arrays das direçoes
			int a = p.first + dir[i][0];
			int b = p.second + dir[i][1];

			//se for valida ( Nao esta infetado)
			if (arr[a][b] != -1 && a >= 0 && b >= 0 && a < MaxLinhas && b < MaxLinhas)
			{
				q.push(make_pair(a, b));
				ListaPontos.push_back(make_pair(a, b));
			}
		}
	}
	return false;
}

int SGestao::PossivelIr_A_B()
{
	for (int i = 0; i < MaxLinhas; i++)
	{
		for (int j = 0; j < MaxColunas; j++)
		{
			if (mapa[i][j] != NULL)
			{
				if (mapa[i][j]->SeEstaInfetada() == true)
				{
					arr[i][j] = -1; // -1 esta infetado
				}
				if (mapa[i][j]->SeEstaInfetada() == false)
				{
					arr[i][j] = 0; // 0 esta infetado
				}
			}
			else
			{
				arr[i][j] = 0; // 0 esta infetado
			}
		}
	}

	// Ver se é possivel ir A  a B sem passar infetados
	if (Caminho(arr))
	{
		cout << "Sim e possivel" << endl;
		cout << "Coordenadas:" << endl;
		for (int i = 0; i < ListaPontos.size(); i++)
		{
			cout << ListaPontos[i].first << " "
				<< ListaPontos[i].second << endl;
		}
	}
	else
		cout << "Nao é possivel ir de A para B sem passar por infetados";

	return 0;
}

int SGestao::Possivel_Zona_Ir_A_B()
{
	//Buffer USAR
	for (int i = 0; i < MaxLinhas; i++)
	{
		for (int j = 0; j < MaxColunas; j++)
		{
			if (mapa[i][j] != NULL)
			{
				if (mapa[i][j]->SeEstaInfetada() == false)
				{
					if (arr[i][j] != -1)
					{
						arr[i][j] = 0;
					}
					continue;
				}
				if (mapa[i][j]->SeEstaInfetada() == true)
				{
					int zonaContagio = 0;
					zonaContagio = mapa[i][j]->getVirus()->GetRaiocontagio();
					arr[i][j] = -1; // -1 esta infetadoo
					arr[i + zonaContagio][j] = -1; // -1 esta infetado
					arr[i - zonaContagio][j] = -1; // Pessoa + Zona de Contagio= -1
					arr[i][j + zonaContagio] = -1;
					arr[i][j - zonaContagio] = -1;
				}
			}
			else
			{
				arr[i][j] = 0;
			}
		}
	}

	// Ver se é possivel ir A  a B sem passar infetados
	if (Caminho(arr))
	{
		cout << "Sim e possivel" << endl;
		cout << "Coordenadas:" << endl;
		for (int i = 0; i < ListaPontos.size(); i++)
		{
			cout << ListaPontos[i].first << " "
				<< ListaPontos[i].second << endl;
		}
	}
	else
		cout << "Nao é possivel ir de A para B sem passar por zonas de infetados";

	return 0;
}

void SGestao::EscreverXML(const string& fich, const string& fich_xml)
{
	ofstream ficheiro(fich_xml);
	if (ficheiro.is_open())
	{
		for (virus* V : lista_Virus)
		{
		ficheiro << "<Virus>" << endl;
		ficheiro << "<Nome>" << V->GetNomevirus() << "</Nome>" << endl;
		ficheiro << "<Raio de Contagio>" << V->GetRaiocontagio() << "</Raio de Contagio>" << endl;
		ficheiro << "<Taxa de Contagio>" << V->GetTaxacontagio() << "</Taxa de Contagio>" << endl;
		ficheiro << "<Taxa de Perigo>" << V->GetTaxaperigo() << "</Taxa de Perigo>" << endl;
		ficheiro << "<Numero de Infetados>" << V->GetNumeroDeInfetados() << "</Numero de Infetados>" << endl;
		ficheiro << "</Virus>" << endl;
		}
		for (Pessoa* P : lista_PessoasInfetadas)
		{
		ficheiro << "<Pessoa Infetadas>" << endl;
		ficheiro << "<Nome>" << P->getNome() << "</Nome>" << endl;
		ficheiro << "<Bi>" << P->getBi() << "</Bi>" << endl;
		ficheiro << "<Cidade>" << P->getCidade() << "</Cidade>" << endl;
		ficheiro << "<Idade>" << P->getIdade() << "</Idade>" << endl;
		ficheiro << "</Pessoa Infetadas>" << endl;
		}
		for (Pessoa* P : lista_PessoasMortas)
		{
		ficheiro << "<Pessoa Mortas>" << endl;
		ficheiro << "<Nome>" << P->getNome() << "</Nome>" << endl;
		ficheiro << "<Bi>" << P->getBi() << "</Bi>" << endl;
		ficheiro << "<Cidade>" << P->getCidade() << "</Cidade>" << endl;
		ficheiro << "<Idade>" << P->getIdade() << "</Idade>" << endl;
		ficheiro << "</Pessoa Mortas>" << endl;
		}
		for (Pessoa* P : lista_Pessoas)
		{
		ficheiro << "<Pessoa>" << endl;
		ficheiro << "<Nome>" << P->getNome()  << "</Nome>" << endl;
		ficheiro << "<Bi>" << P->getBi() << "</Bi>" << endl;
		ficheiro << "<Cidade>" << P->getCidade() << "</Cidade>" << endl;
		ficheiro << "<Idade>" << P->getIdade() << "</Idade>" << endl;
		ficheiro << "</Pessoa>" << endl;
		}
		ficheiro.close();
	}
}






