#include "Simulacion.h"
#include "math.h"

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

void Simulacion::evento_LlegaAComputadoraA(Evento* evento)
{
	//Crear archivo y meterlo en la cola de archivos correspondiente
	//---generar tipo y meterlo en la cola ---//

	//Generar siguiente Arribo - exponencial
	r += ((double) rand() / (RAND_MAX)); //valor aleatorio entre 0 y 1
	 
	double x = -( (log (r) ) / 5) ; //x es una v.a. para la exponencial

	//Actualizo el siguiente arribo y lo vuelvo a encolar
	evento->reloj = Reloj + x;
	ManejadorDeEventos->agregarEventoAlaCola(evento);
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

void Simulacion::evento_LiberaTokenA(int ttoken){

	//int t = tiempotoken; (el tiempo que el usuario le asigna al token, no se donde esta)
	bool archivos = true;
	
	while (t != 0 && archivos) {
		if (Computadora.Tipo1Vacia()){
			if (Computadora.Tipo2Vacia()){
				archivos = false;
			}
			else { //hay minimo 1 archivo de tipo 2
				Computadora.sacarArchivoTipo2();
				
				t = t - Archivo.tamano() * 0.5;
			
				//termina de poner en linea				
				
			}
		} 
		else { //hay minimo 1 archivo de tipo 1
			Computadora.sacarArchivoTipo1();
			
			t = t - Archivo.tamano() * 0.5;
			
			//termina de poner en linea
		}
	
	}
	
	//programar libera token B
	
	delete EventoActual;

}

int Simulacion::generaPrioridad{
	w = rand() % 100; //generación de número aleatorio entre 0-99
	if (w < 24) { //tipo 1
		return 1;
	}
	else { //tipo 2
		return 2;
	}
}


