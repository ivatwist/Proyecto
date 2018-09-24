#include "Persona.h"
#include "Simulador.h"
#include <iostream>

using namespace std;

int main()
{
	int num_personas, dimension, tics;
	double potencia, recuperacion, muerte, num_infectadas;
	cout << "\t\t INFEKTION" << endl << endl;
	cout << "  Digite la cantidad de personas: ";
	cin >> num_personas;
	cout << "\n  Digite potencia infecciosa de virus: ";
	cin >> potencia;
	cout << "\n  Probabilidad de recuperacion: ";
	cin >> recuperacion;
	cout << "\n  Probabilidad de muerte: ";
	cin >> muerte;
	cout << "\n  Porcentaje original infectados: ";
	cin >> num_infectadas;
	cout << "\n  Elija la dimension del espacio: "
		<< "\n   1) 100x100 " << "\n   2) 500x500 " << "\n   3) 1000x1000 "
		<< "\n   Opcion: ";
	cin >> dimension;
	cout << "\n  Digite la cantidad de dias: ";
	cin >> tics;
	switch (dimension)
	{
		//case 1: dimension = 100; break;
		case 1: dimension = 6; break;
		case 2: dimension = 500; break;
		case 3: dimension = 1000; break;
	}
	//cout << "\n  Duracion de la simulacion: ";
	//cin >> tics;

	Simulador m1 = Simulador(dimension, num_personas, num_infectadas);

	for(int dias=0; dias<tics; ++dias)
	{
		cout << endl << endl << "\tM1" << endl;
		m1.imprimir(m1.matriz, dimension);
		m1.verificarInfectado(num_personas, dimension, potencia);
		cout << endl << endl << "Verificacion:" << endl << endl;
		m1.imprimir(m1.matriz, dimension);
		cout << "\t\t\t\t Dia "<<dias<<endl<<endl;
		Simulador *m2 = new Simulador(dimension);
		m1.mover(num_personas, dimension, m2->matriz);
		cout << endl << endl << "\tM2" << endl;
		m2->imprimir(m2->matriz, dimension);
		m2->verificarInfectado(num_personas, dimension, potencia);
		m1.matriz = m2->matriz;
		delete m2;
	}
	cin >> tics;

	return 0;
}