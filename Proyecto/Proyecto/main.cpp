#include "Persona.h"
#include "Simulador.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream archivo;
	archivo.open("Estadisticas.txt");
	archivo.close();

	int num_personas, dimension, tics, muerte;
	double potencia, recuperacion, num_infectadas;
	cout << "\t\t INFEKTION" << endl << endl;
	cout << "  Digite la cantidad de personas: ";
	cin >> num_personas;
	cout << "\n  Digite potencia infecciosa de virus: ";
	cin >> potencia;
	cout << "\n  Probabilidad de recuperacion: ";
	cin >> recuperacion;
	cout << "\n  Dias antes de morir: ";
	cin >> muerte;
	cout << "\n  Porcentaje original infectados: ";
	cin >> num_infectadas;
	cout << "\n  Elija la dimension del espacio: "
		<< "\n   0) 35x35 \n   1) 100x100 " << "\n   2) 500x500 " << "\n   3) 1000x1000 "
		<< "\n   Opcion: ";
	cin >> dimension;
	cout << "\n  Digite la cantidad de dias: ";
	cin >> tics;
	switch (dimension)
	{
		//case 1: dimension = 100; break;
		case 0: dimension = 35; break;
		case 1: dimension = 100; break;
		case 2: dimension = 500; break;
		case 3: dimension = 1000; break;
	}
	//cout << "\n  Duracion de la simulacion: ";
	//cin >> tics;

	Simulador m1 = Simulador(dimension, num_personas, num_infectadas);

	//cout << endl << "\t\t\t\tM1" << endl;

	m1.Estadisticas(num_personas, m1.muertos, m1.curados, m1.sanos, m1.enfermos, m1.enfermos, 0);
	//#pragma omp parallel for
	for (int dias = 1; dias <= tics; ++dias)
	{
//#pragma omp  critical
		//cout << endl << endl << "\t------------------------------ Dia " << dias <<"------------------------------"<< endl << endl;
		//cout << endl << "\tM1" << endl;
		//m1.imprimir(m1.matriz, dimension);
		//m1.verificarEstado(num_personas, dimension, potencia, muerte, recuperacion);
		//cout << endl << endl << "Verificacion:" << endl << endl;
		//m1.imprimir(m1.matriz, dimension);
//#pragma omp  critical
		//m1.imprimir(m1.matriz, dimension);
		Simulador *m2 = new Simulador(dimension);
		//m1.mover(num_personas, dimension, m2->matriz);
		m1.mover(num_personas, dimension, m2 );
//#pragma omp  critical
	//	{
			//cout << endl << "\t\t\t\tM2" << endl;
			//cout << "Movimiento:\n\n";
			//m2->imprimir(m2->matriz, dimension); }

		m2->verificarEstado(num_personas, dimension, potencia, muerte, recuperacion, dias); 
//#pragma omp  critical
		//{
			//cout << "Verificacion:\n\n";
			//m2->imprimir(m2->matriz, dimension); }
		m1.matriz = m2->matriz;
		m1.curados = m2->curados;
		m1.sanos = m2->sanos;
		m1.enfermos = m2->enfermos;
		m1.muertos = m2->muertos;
		delete m2;
	}
	if(m1.enfermos)
		m1.verificarEstado(num_personas, dimension, potencia, muerte, recuperacion, tics+1);

	/**Imprimir estadisticas finales y matar a todos los infectados*/
	
	
	m1.EstadisticasFinales(num_personas);
	cin >> tics;

	return 0;
}