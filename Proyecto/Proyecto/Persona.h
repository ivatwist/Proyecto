#pragma once
class Persona
{
public:

	int estado;
	int tiempo;
	Persona();
	Persona(int estado);
	Persona(int estado, int tiempo);
	void set_estado(int estado);
	void set_tiempo(int tiempo);
	~Persona();
};

