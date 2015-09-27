#ifndef SIMULACION_H
#define SIMULACION_H

#include "Util.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Computadora.h"

class Simulacion
{
private:
	double Reloj;
    int tiempoToken;
	Evento* EventoActual;
	Util* ManejadorDeEventos;
	Computadora ComputadoraA;
	Computadora ComputadoraB;
	Computadora ComputadoraC;

    inline int generarTamanoDelArchivo(){return rand() % 64 + 1;}
    int generaPrioridad();
    void evento_LiberaTokenA(Evento* evento);
    void evento_LlegaAComputadoraA(Evento *evento);
public:
	Simulacion();
	~Simulacion();
    void run(int tiempoReloj,int tiempoToken);
	void evento_LlegaAComputadoraC(Evento *evento);
};

#endif // SIMULACION_H
