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


void Simulacion::run(int tiempoReloj,int tiempoToken)
{
    this->tiempoToken = tiempoToken;

    while(Reloj < tiempoReloj){
		if(!ManejadorDeEventos->colaVacia()){
			EventoActual = ManejadorDeEventos->sacarSiguienteEvento();
		}

		switch(EventoActual->evento){
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

void Simulacion::evento_LlegaAComputadoraA()
{
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
	//Crear archivo y meterlo en la cola de archivos correspondiente
	Archivos* archivo = new Archivos(generarTamanoDelArchivo());
    if(generaPrioridad() == 1){
        ComputadoraA.agregarArchivoTipo1(archivo);
    }
    else{
        ComputadoraA.agregarArchivoTipo2(archivo);
    }

	//Generar siguiente Arribo - exponencial
    double r;
    r += ((double) rand() / (RAND_MAX)); //valor aleatorio entre 0 y 1
	 
	double x = -( (log (r) ) / 5) ; //x es una v.a. para la exponencial

	//Actualizo el siguiente arribo y lo vuelvo a encolar
    EventoActual->reloj = Reloj + x;
    ManejadorDeEventos->agregarEventoAlaCola(EventoActual);
}

void Simulacion::evento_TerminaDePonerEnLinea()
{
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    
    Evento* llegaAServidor = new Evento(Reloj + 1,LlegaAServidorAntivirus,EventoActual->tamano);
    ManejadorDeEventos->agregarEventoAlaCola(llegaAServidor);
    
    delete EventoActual;
    
}

void Simulacion::impresionEstadoActual()
{
    printf("Reloj: %f \n",Reloj);
    printf("Evento actual: %d \n",EventoActual->evento);
    printf("Cola 1 Computadora A: %d \n Cola 2 Computadora A: %d \n",
           ComputadoraA.Tipo1Size(),
           ComputadoraA.Tipo2Size());
    printf("Cola 1 Computadora B: %d \n Cola 2 Computadora B: %d \n",
           ComputadoraB.Tipo1Size(),
           ComputadoraB.Tipo2Size());
    printf("Cola 1 Computadora C: %d \n Cola 2 Computadora C: %d \n",
           ComputadoraC.Tipo1Size(),
           ComputadoraC.Tipo2Size());
}


void Simulacion::evento_LlegaAComputadoraC()
{
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    double z = 0;
    double n = 0;
    //Crear archivo y meterlo en la cola de archivos correspondiente
	Archivos* archivo = new Archivos(generarTamanoDelArchivo());
    if(generaPrioridad() == 1){
        ComputadoraC.agregarArchivoTipo1(archivo);
    }
    else{
        ComputadoraC.agregarArchivoTipo2(archivo);
    }
	//Generar siguiente Arribo
	//Generacion del Z
	for(int i =0;i<12;i++)
	n += ((double) rand() / (RAND_MAX));
	z = n - 6;
	//Calculamos el X
	double x = 5 + 0.1*z;
	//Actualizo el siguiente arribo y lo vuelvo a encolar
    EventoActual->reloj = Reloj + x;
    ManejadorDeEventos->agregarEventoAlaCola(EventoActual);
}

void Simulacion::evento_LiberaTokenA(){

    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    int t = tiempoToken;
	bool archivos = true;
    Archivos* archivo;

    while (t > 0 && archivos) {
        if (ComputadoraA.Tipo1Vacia()){
            if (ComputadoraA.Tipo2Vacia()){
				archivos = false;
			}
			else { //hay minimo 1 archivo de tipo 2
              archivo = ComputadoraA.sacarArchivoTipo2(t/0.5);
				
			}
		} 
		else { //hay minimo 1 archivo de tipo 1
             archivo =  ComputadoraA.sacarArchivoTipo1(t/0.5);
		}

       if(archivos){
           //Actualiza tiempo y programa terminaDePonerEnLinea
           t = t - archivo->tamano * 0.5;
            Evento* terminaPonerLinea =
                    new Evento(Reloj + (archivo->tamano * 0.5),TerminaDePonerEnLinea,archivo->tamano);
            ManejadorDeEventos->agregarEventoAlaCola(terminaPonerLinea);
        }
	}
    //Se programa el siguiente libera token
    Evento* liberaTokenB = new Evento(Reloj + tiempoToken-t,LiberaTokenB);
    ManejadorDeEventos->agregarEventoAlaCola(liberaTokenB);
	
	delete EventoActual;

}

void Simulacion::evento_LiberaTokenB(){

    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    int t = tiempoToken;
	bool archivos = true;
    Archivos* archivo;

    while (t > 0 && archivos) {
        if (ComputadoraB.Tipo1Vacia()){
            if (ComputadoraB.Tipo2Vacia()){
				archivos = false;
			}
			else { //hay minimo 1 archivo de tipo 2
              archivo = ComputadoraB.sacarArchivoTipo2(t/0.5);
				
			}
		} 
		else { //hay minimo 1 archivo de tipo 1
             archivo =  ComputadoraB.sacarArchivoTipo1(t/0.5);
		}

       if(archivos){
           //Actualiza tiempo y programa terminaDePonerEnLinea
           t = t - archivo->tamano * 0.5;
            Evento* terminaPonerLinea =
                    new Evento(Reloj + (archivo->tamano * 0.5),TerminaDePonerEnLinea,archivo->tamano);
            ManejadorDeEventos->agregarEventoAlaCola(terminaPonerLinea);
        }
	}
    //Se programa el siguiente libera token
    Evento* liberaTokenC = new Evento(Reloj + tiempoToken-t,LiberaTokenC);
    ManejadorDeEventos->agregarEventoAlaCola(liberaTokenC);
	
	delete EventoActual;

}

void Simulacion::evento_LiberaTokenC(){

    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    int t = tiempoToken;
	bool archivos = true;
    Archivos* archivo;

    while (t > 0 && archivos) {
        if (ComputadoraC.Tipo1Vacia()){
            if (ComputadoraC.Tipo2Vacia()){
				archivos = false;
			}
			else { //hay minimo 1 archivo de tipo 2
              archivo = ComputadoraC.sacarArchivoTipo2(t/0.5);
				
			}
		} 
		else { //hay minimo 1 archivo de tipo 1
             archivo =  ComputadoraC.sacarArchivoTipo1(t/0.5);
		}

       if(archivos){
           //Actualiza tiempo y programa terminaDePonerEnLinea
           t = t - archivo->tamano * 0.5;
            Evento* terminaPonerLinea =
                    new Evento(Reloj + (archivo->tamano * 0.5),TerminaDePonerEnLinea,archivo->tamano);
            ManejadorDeEventos->agregarEventoAlaCola(terminaPonerLinea);
        }
	}
    //Se programa el siguiente libera token
    Evento* liberaTokenA = new Evento(Reloj + tiempoToken-t,LiberaTokenA);
    ManejadorDeEventos->agregarEventoAlaCola(liberaTokenA);
	
	delete EventoActual;

}

int Simulacion::generaPrioridad(){
    int w = rand() % 100;
    //generación de número aleatorio entre 0-99
	if (w < 24) { //tipo 1
		return 1;
	}
	else { //tipo 2
		return 2;
	}
}


