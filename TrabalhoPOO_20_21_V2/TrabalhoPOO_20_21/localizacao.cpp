
/*#include "localizacao.h"
#include "Pessoa.h"
#include <stdlib.h>
#include "simulador.h"
#include <math.h>

#define CHEGOU 0.05


localizacao::localizacao()
{
	x = rand() % X_LIMIT + 1;
	y = rand() % Y_LIMIT + 1; 
}

double localizacao::getX() { return x; }

double localizacao::getY() { return y; }

void localizacao::setX(double nx) { x = nx; }

void localizacao::setY(double ny) { y = ny; }

double localizacao::get_distancia(localizacao outra_localizacao)
{
	double dx = outra_localizacao.x - x;
	double dy = outra_localizacao.y - y;
	return sqrt((dx * dx) + (dy * dy));
}

bool localizacao::mov_avancar(localizacao destino, double longe)
{
	double dx = destino.x - x;
	double dy = destino.y - y;
	double theta = atan2(dy, dx);

	double distancia = sqrt((dx * dx) + (dy * dy));

	if (distancia < longe)
	{
		x = destino.x;
		y = destino.y;
		return true;
	}
	else {
		x = x + (longe * cos(theta));
		y = y + (longe * sin(theta));
		return false;
	}
	return false;
}

bool localizacao::no_local(localizacao destino)
{
	return (get_distancia(destino) < CHEGOU);
}
*/