#include "Simulador.h"
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

Simulador::Simulador()
{
}

Simulador::Simulador(int dimension, int num_personas, double num_infectadas)
{
	llenar_Matriz( dimension,  num_personas,  num_infectadas);
	//Imprimir(dimension);
}


Simulador::~Simulador()
{
}

void Simulador::llenar_Matriz(int dimension, int num_personas, double num_infectadas)
{
	this->resizeVec(dimension);		//Se redimensiona la matriz
	srand(time(NULL));
	int fila, colum, n;
	int f = (num_personas*num_infectadas);
	cout << "f: "<<f << endl;
	//Se llena la matriz primero con la proporcion de infectados correspondiente
	for (int iter = 0; iter <f; ++iter)
	{
		fila = rand() % dimension;
		colum = rand() % dimension;
		matriz[fila][colum].push_back(Persona(3));
	}
	for (int iter = 0; iter < num_personas-num_personas*num_infectadas; ++iter)
	{
		fila = rand() % dimension;
		colum = rand() % dimension;
		n = rand() % 3;
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

void Simulador::imprimir(vector<vector<list<Persona>>> m, int dimension)
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

void Simulador::verificarInfectado(int num_personas, int dimension, double potencia)
{
	/* 0-Muerto		1-Inmune		2-Sano		3-Infectado */
	srand(time(NULL));
	int chequeados = 0;
	for (int fila = 0; fila < dimension && chequeados < num_personas; ++fila)
	{
		for (int col = 0; col < dimension && chequeados < num_personas; ++col)
		{
			for (auto &it: matriz[fila][col])
			{
				if (it.estado == 3)		//Si está infectado
				{
					for (auto &it2 : matriz[fila][col])
					{
						double f = (rand() % 100)/ potencia;
						cout << "rand: " << f<<endl;
						if (it2.estado == 2 && f >= potencia)		//Si está sano y el número generado es mayor igual al porcentaje
						{
							it2.set_estado(3);		//Se actualiza el estado de la persona a "INFECTADO"
						}
					}
				}
			}
		}
	}
}

