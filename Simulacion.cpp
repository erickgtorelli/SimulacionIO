#include "Simulacion.h"

Simulacion::Simulacion()
{
	Reloj = 0;
	//Cambiar valor al default para el switch despues
	EventoActual = 0;
	ManejadorDeEventos = new Util();

	//Iniciarlizar primeros eventos para correr la simulacion
}

void Simulacion::run(int tiempo)
{
	while(Reloj < tiempo){
		if(!ManejadorDeEventos->colaVacia()){
			EventoActual = ManejadorDeEventos->sacarSiguienteEvento();
		}

		switch(EventoActual){
		case LlegaAComputadoraA:
			break;

		case LlegaAComputadoraB:
			break;

		case LlegaAComputadoraC:
			evento_LlegaAComputadoraC();
			break;
		}
	}
}

void Simulacion::evento_LlegaAComputadoraC()
{

}


