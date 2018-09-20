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
	cout << "  \nProbabilidad de muerte: ";
	cin >> muerte; 
	cout << "\n  Porcentaje original infectados: ";
	cin >> num_infectadas;
	cout << "\n  Elija la dimension del espacio: "
		<< "\n   1) 100x100 " << "\n   2) 500x500 " << "\n   3) 1000x1000 "
		<< "\n   Opcion: ";
	cin >> dimension;
	switch (dimension) 
	{
	//case 1: dimension = 100; break;
	case 1: dimension = 6; break;
	case 2: dimension = 500; break;
	case 3: dimension = 1000; break;

	}
	//cout << "\n  Duracion de la simulacion: ";
	//cin >> tics;

	Simulador s = Simulador(dimension, num_personas, num_infectadas);
	vector<vector<list<Persona>>> m2;
	cout << "S" << endl;
	s.Imprimir(s.matriz, dimension);
	cout <<endl<<endl<< "M2" << endl;
	m2 = s.matriz;
	s.Imprimir(m2, dimension);

	cin >> tics;

	return 0;
}