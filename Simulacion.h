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
    int archivosEnviados;
    int tieneElToken;
	double tiempoArchivos;
	double tiempoArchivos1;
	double tiempoArchivos2;
	double NumeroDeArchivos;
	double NumeroDeArchivos1;
	double NumeroDeArchivos2;
	Evento* EventoActual;
	Util* ManejadorDeEventos;
	Computadora* ComputadoraA;
	Computadora* ComputadoraB;
	Computadora* ComputadoraC;

    bool Linea1_Disponible = true;
    bool Linea2_Disponible = true;
    std::list<Evento*>* ColaDeEnvios;           // La cola sigue el orden FIFO
    int tamColaEnvios;
    double tamPromedioColaEnvios;
    int cantRevisionesColaEnvios;
    int totalArchivosRevisados;
    int acumuladoRevisionesVirus;
    double promedioRevisionesVirus;

    double proms[5];

    inline int generarTamanoDelArchivo(){return rand() % 64 + 1;}
    void evento_LiberaTokenA();
    void evento_LiberaTokenB();
    void evento_LiberaTokenC();
    int generaPrioridad();
    void evento_LlegaAComputadoraA();
    void evento_LlegaAComputadoraB();
    void evento_LlegaAComputadoraC();
    void evento_TerminaDePonerEnLinea();
    void evento_FinalizaRevision(int M);
    void evento_SeLiberaLinea1Router(int M);
    void evento_SeLiberaLinea2Router(int M);
    void PrimedioColaEnvios();
    void evento_LlegaAServidorAntivirus();
    /**
     * @brief impresionEstadoActual muestra informacion basica del estado de la simulacion
     * @param evento actual corriendo
     * Nota: este evento debe ser llamado despues de actualizado el Reloj en cada evento
     */
    void impresionEstadoActual();
	void impresionTerminoSimulacion();
public:
	Simulacion();
	~Simulacion();
	double* run(int tiempoReloj, int tiempoToken, int modoLento);

};

#endif // SIMULACION_H
