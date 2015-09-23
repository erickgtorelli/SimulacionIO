#include "Simulacion.h"

Simulacion::Simulacion()
{
	Reloj = 0;
	srand (time(NULL));
	//Cambiar valor al default para el switch despues
	EventoActual = 0;
	ManejadorDeEventos = new Util();

	//Iniciarlizar primeros eventos para correr la simulacion
	Evento* LlegaAC = new Evento(0,LlegaAComputadoraC);
	ManejadorDeEventos->agregarEventoAlaCola(LlegaAC);
}

Simulacion::~Simulacion()
{

}


void Simulacion::run(int tiempo)
{
	while(Reloj < tiempo){
		if(!ManejadorDeEventos->colaVacia()){
			EventoActual = ManejadorDeEventos->sacarSiguienteEvento();
		}

		switch(EventoActual->evento){
		case LlegaAComputadoraA:
			break;

		case LlegaAComputadoraB:
			break;

		case LlegaAComputadoraC:
			evento_LlegaAComputadoraC(EventoActual);
			break;
		}
	}
}

void Simulacion::evento_LlegaAComputadoraC(Evento* evento)
{
	//Crear archivo y meterlo en la cola de archivos correspondiente
	//---generar tipo y meterlo en la cola ---//

	Archivos* archivo = new Archivos(generarTamanoDelArchivo());
	//Generar siguiente Arribo
	double z = 0;
	double n = 0;
	//Generacion del Z
	for(int i =0;i<12;i++)
	n += ((double) rand() / (RAND_MAX));

	z = n - 6;
	//Calculamos el X
	double x = 5 + 0.1*z;

	//Actualizo el siguiente arribo y lo vuelvo a encolar
	evento->reloj = Reloj + x;
	ManejadorDeEventos->agregarEventoAlaCola(evento);
}


