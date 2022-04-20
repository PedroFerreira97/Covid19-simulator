#pragma once
#include "SGestao.h"

class localizacao
{
private:
	double x, y;
public:
	localizacao();
	localizacao(double nx, double ny)
	{
		x = nx;
		y = ny;
	}

	double getX();
	double getY();
	void setX(double nx);
	void setY(double ny);

	double get_distancia(localizacao outra_localizacao);
	bool mov_avancar(localizacao destino, double longe);
	bool no_local(localizacao destino);
};

