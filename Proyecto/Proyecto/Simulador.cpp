#include "Simulador.h"


using namespace std;

Simulador::Simulador()
{
}

Simulador::Simulador(int dimension)
{
	this->resizeVec(dimension);
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
		n = rand() % 2+1;
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

	//for (int i = 0; i<dimension; ++i)
	//{
	//	for (int j = 0; j<dimension; ++j)
	//	{
	//		cout << "c " << i << " f " << j << ": ";
	//			for (auto &it : m[i][j])
	//			{
	//				cout<< it.estado << " ";
	//				//cout << m[i][j].size() << " ";
	//			}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}

	int impresos;
	for (int i = 0; i<dimension; ++i)
	{
		for (int j = 0; j<dimension; ++j)
		{
			impresos = 0;
			//cout << "c " << i << " f " << j << ": ";
			for (auto &it : m[i][j])
			{
				cout << it.estado <<" ";
				++impresos;
				//cout << m[i][j].size() << " ";
			}
			for (int p = 0; p < 7- impresos; ++p)
				cout << "  ";
			cout << "\|";
		}
		cout << endl;
		for (int p = 0; p < 15*dimension; ++p)
			cout << "_";
		cout << endl;
	}


}
//void Simulador::verificarInfectado(int num_personas, int dimension, double potencia)
void Simulador::verificarEstado(int num_personas, int dimension, double potencia, double muerte, double recuperacion)
{
	/* 0-Muerto		1-Inmune		2-Sano		3-Infectado */
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0, 1);
	double f;
	int chequeados = 0;
	for (int fila = 0; fila < dimension && chequeados < num_personas; ++fila)
	{
		for (int col = 0; col < dimension && chequeados < num_personas; ++col)
		{
			for (auto &it: matriz[fila][col])
			{
				if (it.estado == 3)		//Si está infectado
				{
					for (auto &it2 : matriz[fila][col])		//Ciclo para infectar los sanos
					{
						//double f = (rand() % 100)/ potencia;
						f = distribution(generator);
						//cout << "rand: " << f<<endl;
						if (it2.estado == 2 && f < potencia)		//Si está sano y el número generado es mayor igual al porcentaje
						{
							it2.set_estado(3);		//Se actualiza el estado de la persona a "INFECTADO"
						}
					}
					f = distribution(generator);
					if (f < muerte)		//Si la probabildad de muerte se cumple, entonces el enfermo se muere
					{
						it.set_estado(0);		//Se actualiza el estado de la persona a "MUERTO"
					}
					f = distribution(generator);
					if (f < recuperacion && it.estado==3)		//Si la probabildad de recuperación se cumple, entonces el enfermo se muere
					{
						it.set_estado(1);		//Se actualiza el estado de la persona a "INMUNE"
					}
				}
			}
		}
	}
}

void Simulador::mover(int num_personas, int dimension, vector<vector<list<Persona>>>& m2)
{
	srand(time(NULL));
	int rfila, rcolumna;
	int chequeados = 0;
	for (int fila = 0; fila < dimension && chequeados < num_personas; ++fila)
	{
		for (int col = 0; col < dimension && chequeados < num_personas; ++col)
		{
			for (auto &it : matriz[fila][col])
			{
				
					rfila = rand() % 3 - 1;
					rcolumna = rand() % 3 - 1;
					if (rfila - fila < 0)
						rfila = dimension - 1;
					if (fila + rfila >= dimension)
						rfila = 0;
					if (rcolumna - col < 0)
						rcolumna = dimension - 1;
					if (col + rcolumna >= dimension)
						rcolumna = 0;
					if (it.estado != 0)
					m2[fila + rfila][col + rcolumna].push_back(Persona(it.estado));
					else
						m2[fila][col].push_back(Persona(0));
			}
		}
	}
}

