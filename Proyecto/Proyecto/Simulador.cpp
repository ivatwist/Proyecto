#include "Simulador.h"
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

Simulador::Simulador()
{
}

Simulador::Simulador(int dimension, int num_personas, int num_infectadas)
{
	llenar_Matriz( dimension,  num_personas,  num_infectadas);
	//Imprimir(dimension);
}


Simulador::~Simulador()
{
}

void Simulador::llenar_Matriz(int dimension, int num_personas, int num_infectadas)
{
	this->resizeVec(dimension);		//Se redimensiona la matriz
	srand(time(NULL));
	int fila, colum, n;
	for (int iter = 0; iter < num_personas; ++iter)
	{
		fila = rand() % dimension;
		colum = rand() % dimension;
		n = rand() % 4;
		//cout << "f " << fila << " c " << colum <<" n "<<n<< endl;
		matriz[fila][colum].push_back(Persona(n));
	}
	
}

/*

*/
void Simulador::resizeVec(int dimension)
{
	matriz.resize(dimension);
	for (auto &it : matriz)
	{
		it.resize(dimension);
	}
}

void Simulador::Imprimir(vector<vector<list<Persona>>> m, int dimension)
{
	//for (int i=0; i<dimension; ++i)
	//{
	//	for (int j = 0; j<dimension; ++j)
	//	{
	//		if (m[i][j].size() == 0)
	//			cout << " - ";
	//		else
	//		for (auto &it: m[i][j])
	//		{
	//			//cout << it.estado << " ";
	//			cout<<m[i][j].size()<<" ";
	//		}
	//	}
	//	cout << endl;
	//}

	for (int i = 0; i<dimension; ++i)
	{
		for (int j = 0; j<dimension; ++j)
		{
			cout << "c " << i << " f " << j << ": ";
				for (auto &it : m[i][j])
				{
					cout<< it.estado << " ";
					//cout << m[i][j].size() << " ";
				}
			cout << endl;
		}
		cout << endl;
	}
}

