#ifndef SIMULACION_H
#define SIMULACION_H

#include "Util.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Computadora.h"
#include <string>
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
    void evento_LiberaTokenA();
    void evento_LlegaAComputadoraA();
    void evento_LlegaAComputadoraB();
    void evento_TerminaDePonerEnLinea();
    void evento_LlegaAComputadoraC();
    /**
     * @brief impresionEstadoActual muestra informacion basica del estado de la simulacion
     * @param evento actual corriendo
     * Nota: este evento debe ser llamado despues de actualizado el Reloj en cada evento
     */
    void impresionEstadoActual();
public:
	Simulacion();
	~Simulacion();
    void run(int tiempoReloj,int tiempoToken);

};

#endif // SIMULACION_H
