#ifndef SIMULACION_H
#define SIMULACION_H

#include "Util.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class Simulacion
{
private:
	int Reloj;
	Evento* EventoActual;
	Util* ManejadorDeEventos;
public:
	Simulacion();
	void run(int tiempo);
	void evento_LlegaAComputadoraC();
};

#endif // SIMULACION_H
