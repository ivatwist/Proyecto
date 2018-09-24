
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

using namespace  std;


class Simulador
{
public:
	list<Persona> personas;
	vector<vector<list<Persona>>> matriz;

	Simulador();
	Simulador(int dimension);
	Simulador(int dimension, int num_personas, double num_infectadas);
	void llenar_Matriz(int dimension, int num_personas, double num_infectadas);
	void mover(int num_personas, int dimension, vector<vector<list<Persona>>>&);
	void resizeVec(int dimension);
	void imprimir(vector<vector<list<Persona>>> matriz, int dimension);
	void verificarInfectado(int num_personas, int, double);
	~Simulador();
};

#endif