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
	Evento* EventoActual;
	Util* ManejadorDeEventos;
	Computadora* ComputadoraA;
	Computadora* ComputadoraB;
	Computadora* ComputadoraC;

    bool Linea1_Disponible = true;
    bool Linea2_Disponible = true;
    std::list<Evento*>* ColaDeEnvios;           // La cola sigue el orden FIFO

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
    void evento_LlegaAServidorAntivirus();
    /**
     * @brief impresionEstadoActual muestra informacion basica del estado de la simulacion
     * @param evento actual corriendo
     * Nota: este evento debe ser llamado despues de actualizado el Reloj en cada evento
     */
    void impresionEstadoActual();
public:
	Simulacion();
	~Simulacion();
	void run(int tiempoReloj, int tiempoToken, int modoLento);

};

#endif // SIMULACION_H
