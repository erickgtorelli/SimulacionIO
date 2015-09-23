#ifndef SIMULACION_H
#define SIMULACION_H

#include "Util.h"
class Simulacion
{
private:
	int Reloj;
	int EventoActual;
	Util* ManejadorDeEventos;
public:
	Simulacion();
	void run(int tiempo);
	void evento_LlegaAComputadoraC();
};

#endif // SIMULACION_H
