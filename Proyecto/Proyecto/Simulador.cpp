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
	//cout << "f: "<<f << endl;
	//Se llena la matriz primero con la proporcion de infectados correspondiente
	/*for(int iter = 0; iter <num_personas; ++iter)
	{
		fila = rand() % dimension;
		colum = rand() % dimension;
		matriz[fila][colum].push_back(Persona(iter));
	}*/
#pragma omp parallel for
		for (int iter = 0; iter < f; ++iter)
		{
			fila = rand() % dimension;
			colum = rand() % dimension;
			matriz[fila][colum].push_back(Persona(3));
		}
		this->enfermos = f;
		int nn= num_personas - num_personas * num_infectadas;
#pragma omp parallel for
		for (int iter = 0; iter < nn; ++iter)
		{
			fila = rand() % dimension;
			colum = rand() % dimension;
			n = rand() % 2 + 1;
			//cout << "f " << fila << " c " << colum <<" n "<<n<< endl;
			matriz[fila][colum].push_back(Persona(n));
			if (n == 2)
				this->sanos= this->sanos+1;
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

void Simulador::obtenerCantidades(int dimension, int& totalinfectados, int& totalsanos)
{
#pragma omp parallel for
	for (int fila = 0; fila < dimension /*&& chequeados < num_personas*/; ++fila)
	{
#pragma omp parallel for
		for (int col = 0; col < dimension /*&& chequeados < num_personas*/; ++col)
		{
			int contaenfermos = 0;
			for (auto &it : matriz[fila][col])
			{
				if (it.estado==2)
					++totalsanos;
				else
					if (it.estado == 3)
						++totalinfectados;
			}
		}
	}
}

//void Simulador::verificarInfectado(int num_personas, int dimension, double potencia)
void Simulador::verificarEstado(int num_personas, int dimension, double& potencia, int muerte, double recuperacion, int dias)
{
	/* 0-Muerto		1-Inmune		2-Sano		3-Infectado */
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0, 1);
	double f;
	int chequeados = 0;
	int totalinfectados = 0, totalsanos=0, totalcurados = 0, totalmuertos=0, infectados=0;
	obtenerCantidades(dimension, totalinfectados, totalsanos);
#pragma omp parallel for

	for (int fila = 0; fila < dimension /*&& chequeados < num_personas*/; ++fila)
	{
#pragma omp parallel for
		for (int col = 0; col < dimension /*&& chequeados < num_personas*/; ++col)
		{
			int contaenfermos = 0;
			for (auto &it: matriz[fila][col])
			{
				contaenfermos = 0;
				//if (it.estado == 2)		//Si está sano
				//	++totalsanos;
				if (it.estado == 3 )		//Si está infectado
				{

					//++totalinfectados;
					contaenfermos = 0;
					
					for (auto &it2 : matriz[fila][col])		//Ciclo para contar los enfermos en una celda
					{
						if (it2.estado == 3)
						{
							++contaenfermos;
						}
					}
					//contaenfermos = contaenfermos - 1;
			//		cout << "\n\nNueva potencia: " << potencia * contaenfermos <<" Conta: "<< contaenfermos<<" [ "<<fila<<"] ["<<col<<"] "<< endl << endl;
					for (auto &it2 : matriz[fila][col])		//Ciclo para infectar los sanos
					{
						//double f = (rand() % 100)/ potencia;
						f = distribution(generator);
						//cout << "rand: " << f<<endl;
						if (it2.estado == 2 && f < potencia*contaenfermos)		//Si está sano y el número generado es mayor igual al porcentaje
						{
							it2.set_estado(3);		//Se actualiza el estado de la persona a "INFECTADO"
							++infectados;
							cout << " se infecta ";
							
						}
					}
					//cout << "t: " << it.tiempo << endl;
					if (it.tiempo== muerte)		//Si la probabildad de muerte se cumple, entonces el enfermo se muere
					{
						f = distribution(generator);
						if (f < recuperacion /*&& it.tiempo != 0*/)		//Si la probabildad de recuperación se cumple, entonces el enfermo se hace inmune
						{
							it.set_estado(1);		//Se actualiza el estado de la persona a "INMUNE"
							++totalcurados;
							this->curados= this->curados+1;
							cout << " se curo ";
						}
						else
						{
							it.set_estado(0);		//Se actualiza el estado de la persona a "MUERTO"
							this->muertos = this->muertos + 1;
							++totalmuertos;
							cout << " se muere ";
							//this->muertos=this->muertos+1;
						}
						
					}
					it.tiempo = it.tiempo + 1;
					//it.set_tiempo(it.tiempo + 1);
				}

			}
		}
	}
	this->enfermos = this->enfermos + infectados;
	totalinfectados += infectados;
	totalsanos -= infectados;

	/*cout << "\n this->curados " << this->curados;
	cout << "\n this->sanos " << this->sanos;
	cout << "\n this->muertos " << this->muertos;
	cout << "\n this->enfermos " << this->enfermos;*/
	Estadisticas(num_personas, totalmuertos, totalcurados, totalsanos, totalinfectados, infectados, dias);
}


void Simulador::Estadisticas(int num_personas, int totalmuertos, int curados, int totalsanos, int totalinfectados, int infectados, int dias)
{
	cout << endl << endl << "\t------------------------------ Dia " << dias << " ------------------------------" << endl << endl;
	cout	<< "\t\t\t\t Personas infectadas \n\t Porcentaje: " << 1.0*infectados / num_personas	<< "\t\t\t Cantidad actual: " << infectados << endl
			<< "\n\t\t\t\t Total infectadas \n\t Porcentaje: " << 1.0*totalinfectados / num_personas << "\t\t\t Cantidad actual: " << totalinfectados << endl
			<< "\n\t\t\t\t Personas sanos \n\t Porcentaje : "	<< 1.0*totalsanos / num_personas		<< "\t\t\t Cantidad actual: " << totalsanos << endl
			<< "\n\t\t\t\t Personas curados \n\t Porcentaje : " << 1.0*curados / num_personas			<< "\t\t\t Cantidad actual: " << curados << endl
			<< "\n\t\t\t\t Personas muertas \n\t Porcentaje : " << 1.0*totalmuertos / num_personas		<< "\t\t\t Cantidad actual: " << totalmuertos << endl << endl;

	ofstream archivo;
	archivo.open("Estadisticas.txt", std::fstream::app);
	archivo << endl << endl
			<< "\t------------------------------ Dia " << dias << " ------------------------------" << endl << endl
			<< "\t\t\t\t Total infectadas \n\t Porcentaje: " << 1.0*totalinfectados / num_personas << "\t\t\t Cantidad actual: " << totalinfectados << endl
			<< "\n\t\t\t\t Personas infectadas \n\t Porcentaje: " << 1.0*totalinfectados / num_personas	<< "\t\t\t Cantidad actual: " << totalinfectados << endl
			<< "\n\t\t\t\t Personas sanos \n\t Porcentaje : "	<< 1.0*totalsanos / num_personas		<< "\t\t\t Cantidad actual: " << totalsanos << endl
			<< "\n\t\t\t\t Personas curados \n\t Porcentaje : " << 1.0*curados / num_personas			<< "\t\t\t Cantidad actual: " << curados << endl
			<< "\n\t\t\t\t Personas muertas \n\t Porcentaje : " << 1.0*totalmuertos / num_personas		<< "\t\t\t Cantidad actual: " << totalmuertos << endl << endl;
	archivo.close();

}


//metodo para imprimir las estadisticas finales, este metodo lo que hace es decir cuantas personas infectadas, sanas, curadas y muertas han habido en total en todos los tics
void Simulador::EstadisticasFinales(int num_personas)
{
	cout << "\t-------------------------------------------------------------------" << endl << endl;
	cout << "\n\n\n\t\t\t\t ESTADISTICAS FINALES" << endl << endl;
	cout << "\t\t\t\t Personas infectadas \n\t Porcentaje: " << 1.0*this->enfermos / num_personas << "\t\t\t Cantidad total: " << this->enfermos << endl
		<< "\n\t\t\t\t Personas sanos \n\t Porcentaje : " << 1.0*this->sanos / num_personas << "\t\t\t Cantidad total: " << this->sanos << endl
		<< "\n\t\t\t\t Personas curados \n\t Porcentaje : " << 1.0*this->curados / num_personas << "\t\t\t Cantidad total: " << this->curados<< endl
		<< "\n\t\t\t\t Personas muertas \n\t Porcentaje : " << 1.0*this->muertos / num_personas << "\t\t\t Cantidad total: " << this->muertos << endl << endl;

	ofstream archivo;
	archivo.open("Estadisticas.txt", std::fstream::app);
	archivo << "\t-------------------------------------------------------------------" << endl << endl
		<< "\n\n\t\t\t\t ESTADISTICAS FINALES" << endl << endl
		<< "\t\t\t\t Personas infectadas \n\t Porcentaje: " << 1.0*this->enfermos / num_personas << "\t\t\t Cantidad total: " << this->enfermos << endl
		<< "\n\t\t\t\t Personas sanos \n\t Porcentaje : " << 1.0*this->sanos / num_personas << "\t\t\t Cantidad total: " << this->sanos << endl
		<< "\n\t\t\t\t Personas curados \n\t Porcentaje : " << 1.0*this->curados / num_personas << "\t\t\t Cantidad total: " << this->curados << endl
		<< "\n\t\t\t\t Personas muertas \n\t Porcentaje : " << 1.0*this->muertos / num_personas << "\t\t\t Cantidad total: " << this->muertos << endl << endl;
	archivo.close();
}

//void Simulador::mover(int num_personas, int dimension, vector<vector<list<Persona>>>& m2)
void Simulador::mover(int num_personas, int dimension, Simulador* m2)
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,1);
	m2->curados = this->curados;
	//cout << "\n m2->curados " << m2->curados;
	m2->sanos = this->sanos;
	//cout << "\n m2->sanos " << m2->sanos;
	m2->muertos = this->muertos;
	//cout << "\n m2->muertos " << m2->muertos;
	m2->enfermos = this->enfermos;
	//cout <<  "\n m2->enfermos " << m2->enfermos;
	int rfila, rcolumna;
	int chequeados = 0;
#pragma omp parallel for
	for (int fila = 0; fila < dimension /*&& chequeados < num_personas*/; ++fila)
	{
#pragma omp parallel for
		for (int col = 0; col < dimension /*&& chequeados < num_personas*/; ++col)
		{
		
			for (auto &it : matriz[fila][col])
			{
				
					rfila =  distribution(generator);
					rcolumna =  distribution(generator);
					rfila ? 0 : rfila =-1;
					rcolumna ? 0 : rcolumna =-1;
					//cout << "x " << rcolumna << " y " << rfila << endl;
					
					/*if (rfila + fila < 0)
						rfila = dimension - 1;
					if (fila + rfila >= dimension)
						rfila = 0;
					if (rcolumna + col < 0)
						rcolumna = dimension - 1;
					if (col + rcolumna >= dimension)
						rcolumna = 0;

					if (it.estado != 0)
						m2[fila + rfila][col + rcolumna].push_back(Persona(it.estado));
					else
						m2[fila][col].push_back(Persona(0));*/

					if (it.estado != 0)
						m2->matriz[(dimension+fila+rfila)%dimension][(dimension+col + rcolumna)%dimension].push_back(Persona(it.estado, it.tiempo));
					else
						m2->matriz[fila][col].push_back(Persona(0));
			}
		}
	}
}

