#include "Persona.h"



Persona::Persona()
{
}

Persona::Persona(int estado)
{
	this->estado = estado;
	this->tiempo = 0;
}

Persona::Persona(int estado,int tiempo)
{
	this->estado = estado;
	this->tiempo = tiempo;
}

void Persona::set_estado(int estado)
{
	this->estado = estado;
}

Persona::~Persona()
{
}


void Persona::set_tiempo(int tiempo)
{
	this->tiempo= tiempo;
}

