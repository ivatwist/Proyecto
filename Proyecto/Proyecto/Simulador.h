
#pragma once
#ifndef SIM
#define SIM

#include "Persona.h"
#include <vector>
#include <list>
#include <iterator>
#include <iostream>
#include <time.h>
#include <math.h>
#include <random>
#include <fstream>
#include <omp.h>

using namespace  std;


class Simulador
{
public:
	list<Persona> personas;
	vector<vector<list<Persona>>> matriz;
	int sanos=0, muertos = 0, curados = 0, enfermos = 0;


	Simulador();
	Simulador(int dimension);
	Simulador(int dimension, int num_personas, double num_infectadas);
	void llenar_Matriz(int dimension, int num_personas, double num_infectadas);
	void mover(int num_personas, int dimension, Simulador*);
	void resizeVec(int dimension);
	void imprimir(vector<vector<list<Persona>>> matriz, int dimension);
	//void verificarInfectado(int num_personas, int, double);
	void verificarEstado(int num_personas, int, double&, int, double, int);
	void Estadisticas(int, int, int, int, int, int);
	void EstadisticasFinales(int);

	~Simulador();
};

#endif