#include "Persona.h"



Persona::Persona()
{
}

Persona::Persona(int estado)
{
	this->estado = estado;
}

void Persona::set_estado(int estado)
{
	this->estado = estado;
}

Persona::~Persona()
{
}
