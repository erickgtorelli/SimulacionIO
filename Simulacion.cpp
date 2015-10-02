#include "Simulacion.h"
#include "math.h"
#include <unistd.h>
Simulacion::Simulacion()
{
	Reloj = 0;
	srand (time(NULL));
	NumeroDeArchivos = 0;
	NumeroDeArchivos1 = 0;
	NumeroDeArchivos2 = 0;
	//Cambiar valor al default para el switch despues
	EventoActual = 0;
	ManejadorDeEventos = new Util();
	ComputadoraA = new Computadora();
	ComputadoraB = new Computadora();
	ComputadoraC = new Computadora();
        ColaDeEnvios = new std::list<Evento*>;
	//Iniciarlizar primeros eventos para correr la simulacion
	Evento* LlegaAC = new Evento(0,LlegaAComputadoraC);
  Evento* LlegaAB = new Evento(0,LlegaAComputadoraB);
  Evento* LlegaAA = new Evento(0,LlegaAComputadoraA);
  Evento* LiberaToken = new Evento(1.5,LiberaTokenA);
  ManejadorDeEventos->agregarEventoAlaCola(LiberaToken);
  ManejadorDeEventos->agregarEventoAlaCola(LlegaAC);
  ManejadorDeEventos->agregarEventoAlaCola(LlegaAB);
  ManejadorDeEventos->agregarEventoAlaCola(LlegaAA);

}

Simulacion::~Simulacion()
{

}


double* Simulacion::run(int tiempoReloj, int tiempoToken, int modoLento)
{


    this->tiempoToken = tiempoToken;

    while(Reloj < tiempoReloj){
  		if(!ManejadorDeEventos->colaVacia()){
  			EventoActual = ManejadorDeEventos->sacarSiguienteEvento();

		if(modoLento == 1)
			sleep(1);

  		switch(EventoActual->evento){
			case LlegaAComputadoraA:
                evento_LlegaAComputadoraA();
                break;
    		case LlegaAComputadoraB:
                evento_LlegaAComputadoraB();
    			break;
    		case LlegaAComputadoraC:
                evento_LlegaAComputadoraC();
    			break;
            case LiberaTokenA:
                evento_LiberaTokenA();
                break;
            case LiberaTokenB:
                evento_LiberaTokenB();
                break;
            case LiberaTokenC:
                evento_LiberaTokenC();
                break;
            case TerminaDePonerEnLinea:
                evento_TerminaDePonerEnLinea();
                break;
            case LlegaAServidorAntivirus:
                  evento_LlegaAServidorAntivirus();
                break;
            case FinalizaRevisionDeVirus:
                  evento_FinalizaRevision(EventoActual->tamano);
                break;
            case SeLiberaLineaRouter1:
                  evento_SeLiberaLinea1Router(EventoActual->tamano);
                break;
            case SeLiberaLineaRouter2:
                  evento_SeLiberaLinea1Router(EventoActual->tamano);
                break;
  		}
	 }
    }
    
  impresionTerminoSimulacion();

  return proms;

}

void Simulacion::evento_LlegaAComputadoraA()
{
    Reloj = EventoActual->reloj;
	printf("Evento: LlegaAComputadoraA \n");
    impresionEstadoActual();
	//Crear archivo y meterlo en la cola de archivos correspondiente
	Archivos* archivo = new Archivos(generarTamanoDelArchivo(),Reloj);
    if(generaPrioridad() == 1){
		ComputadoraA->agregarArchivoTipo1(archivo);
    }
    else{
		ComputadoraA->agregarArchivoTipo2(archivo);
    }

	//Generar siguiente Arribo - exponencial
    double r;
    r = ((double) rand() / (RAND_MAX)); //valor aleatorio entre 0 y 1
	 
    double x = -( (log (r) ) / 5) ; //x es una v.a. para la exponencial

	//Actualizo el siguiente arribo y lo vuelvo a encolar
    EventoActual->reloj = Reloj + x;
    ManejadorDeEventos->agregarEventoAlaCola(EventoActual);
}

void Simulacion::evento_LlegaAComputadoraB()
{
    Reloj = EventoActual->reloj;
	printf("Evento: LlegaAComputadoraB \n");
    impresionEstadoActual();

    //Crear archivo y meterlo en la cola de archivos correspondiente
	Archivos* archivo = new Archivos(generarTamanoDelArchivo(),Reloj);
    if(generaPrioridad() == 1){
		ComputadoraB->agregarArchivoTipo1(archivo);
    }
    else{
		ComputadoraB->agregarArchivoTipo2(archivo);
    }

    //Generar siguiente Arribo
    double r = ((double) rand() / (RAND_MAX)); //valor aleatorio entre 0 y 1
     
    double x = sqrt(80*(r+(4/5))) ; //x es una v.a.
    //Actualizo el siguiente arribo y lo vuelvo a encolar
    EventoActual->reloj = Reloj + x;
    ManejadorDeEventos->agregarEventoAlaCola(EventoActual);
}

void Simulacion::evento_LlegaAComputadoraC()
{
    Reloj = EventoActual->reloj;
	printf("Evento: LlegaAComputadoraC \n");
    impresionEstadoActual();
    double z = 0;
    double n = 0;
    //Crear archivo y meterlo en la cola de archivos correspondiente
  Archivos* archivo = new Archivos(generarTamanoDelArchivo(),Reloj);
    if(generaPrioridad() == 1){
		ComputadoraC->agregarArchivoTipo1(archivo);
    }
    else{
		ComputadoraC->agregarArchivoTipo2(archivo);
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

void Simulacion::evento_LiberaTokenA(){
	printf("Evento: LiberaTokenA \n");
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    int t = tiempoToken;
    tieneElToken++;
	bool archivos = true;
    Archivos* archivo;
	int tipo = 0;
    while (t > 0 && archivos) {

    if (ComputadoraA->Tipo1Vacia()){
			if (ComputadoraA->Tipo2Vacia()){
				archivos = false;
                        }
                        else { //hay minimo 1 archivo de tipo 2
				
			  				archivo = ComputadoraA->sacarArchivoTipo2(t/0.5);
			  				archivosEnviados++;
							tipo = 2;
                        }
    } 
    else { //hay minimo 1 archivo de tipo 1
			
			 archivo =  ComputadoraA->sacarArchivoTipo1(t/0.5);
			 archivosEnviados++;
			 tipo = 1;
			 if(archivo == nullptr && !ComputadoraA->Tipo2Vacia()){
				 archivo = ComputadoraA->sacarArchivoTipo2(t/0.5);
				tipo = 2;
			 }
    }
       if(archivos && archivo != nullptr){
           int tamano = archivo->tamano;
           //Actualiza tiempo y programa terminaDePonerEnLinea
		   double entrada = archivo->entradaAlSistema;
            t = t - tamano  * 0.5;
            Evento* terminaPonerLinea =
					new Evento(Reloj + (tamano * 0.5),TerminaDePonerEnLinea,tamano,tipo,entrada);
            ManejadorDeEventos->agregarEventoAlaCola(terminaPonerLinea);
            delete archivo;
            archivo = nullptr;
       }
       else{
           archivos = false;
       }
       
  }
    //Se programa el siguiente libera token

	Evento* liberaTokenB = new Evento(Reloj + tiempoToken-t,LiberaTokenB);
    ManejadorDeEventos->agregarEventoAlaCola(liberaTokenB);
  
  delete EventoActual;

}

void Simulacion::evento_LiberaTokenB(){
	printf("Evento: LiberaTokenB \n");
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    int t = tiempoToken;
    tieneElToken++;
  bool archivos = true;
    Archivos* archivo;
	int tipo = 0;
    while (t > 0 && archivos) {
		if (ComputadoraB->Tipo1Vacia()){
			if (ComputadoraB->Tipo2Vacia()){
        archivos = false;
      }
      else { //hay minimo 1 archivo de tipo 2
			  archivo = ComputadoraB->sacarArchivoTipo2(t/0.5);
			  archivosEnviados++;
			  tipo = 2;
      }
    } 
    else { //hay minimo 1 archivo de tipo 1
			 archivo =  ComputadoraB->sacarArchivoTipo1(t/0.5);
			 archivosEnviados++;
			 tipo = 1;
			 if(archivo == nullptr && !ComputadoraA->Tipo2Vacia()){
				 archivo = ComputadoraA->sacarArchivoTipo2(t/0.5);
				tipo = 2;
			 }
    }

        if(archivos && archivo != nullptr){
           int tamano = archivo->tamano;
           //Actualiza tiempo y programa terminaDePonerEnLinea
		   int entrada = archivo->entradaAlSistema;
            t = t - tamano  * 0.5;
            Evento* terminaPonerLinea =
					new Evento(Reloj + (tamano * 0.5),TerminaDePonerEnLinea,tamano,tipo,entrada);
            ManejadorDeEventos->agregarEventoAlaCola(terminaPonerLinea);
            delete archivo;
            archivo = nullptr;
       }
       else{
		   archivos = false;
       }
  }
    //Se programa el siguiente libera token
	Evento* liberaTokenC = new Evento(Reloj + tiempoToken-t,LiberaTokenC);
    ManejadorDeEventos->agregarEventoAlaCola(liberaTokenC);
  
  delete EventoActual;

}

void Simulacion::evento_LiberaTokenC(){
	printf("Evento: LiberaTokenC \n");
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
    int t = tiempoToken;
    tieneElToken++;
  bool archivos = true;
    Archivos* archivo;
	int tipo = 0;
    while (t > 0 && archivos) {
		if (ComputadoraC->Tipo1Vacia()){
			if (ComputadoraC->Tipo2Vacia()){
        archivos = false;
      }
      else { //hay minimo 1 archivo de tipo 2
			  archivo = ComputadoraC->sacarArchivoTipo2(t/0.5);
			  archivosEnviados++;
			  tipo = 2;
        
      }
    } 
    else { //hay minimo 1 archivo de tipo 1
			 archivo =  ComputadoraC->sacarArchivoTipo1(t/0.5);
			 archivosEnviados++;
			 tipo = 1;
			 if(archivo == nullptr && !ComputadoraA->Tipo2Vacia()){
				 archivo = ComputadoraA->sacarArchivoTipo2(t/0.5);
				tipo = 2;
			 }
    }

       if(archivos && archivo != nullptr){
           int tamano = archivo->tamano;
           //Actualiza tiempo y programa terminaDePonerEnLinea
			int entrada = archivo->entradaAlSistema;
            t = t - tamano  * 0.5;
            Evento* terminaPonerLinea =
					new Evento(Reloj + (tamano * 0.5),TerminaDePonerEnLinea,tamano,tipo,entrada);
            ManejadorDeEventos->agregarEventoAlaCola(terminaPonerLinea);
            delete archivo;
            archivo = nullptr;
       }
       else{
           archivos = false;
       }
  }
    //Se programa el siguiente libera token
	Evento* liberaTokenA = new Evento(Reloj + tiempoToken-t,LiberaTokenA);
    ManejadorDeEventos->agregarEventoAlaCola(liberaTokenA);
  
  delete EventoActual;

}

void Simulacion::evento_TerminaDePonerEnLinea()
{
    Reloj = EventoActual->reloj;
	printf("Evento: TerminaDePonerEnLinea \n");
	impresionEstadoActual();

	Evento* llegaAServidor = new Evento(Reloj + 1,LlegaAServidorAntivirus,EventoActual->tamano,EventoActual->tipoArchivo,
										EventoActual->entradaAlSistema);
    ManejadorDeEventos->agregarEventoAlaCola(llegaAServidor);
    
    delete EventoActual;
    
}

void Simulacion::evento_FinalizaRevision(int M){
	printf("Evento: FinalizaRevision");
  Reloj = EventoActual->reloj;
  impresionEstadoActual();

  srand(time(NULL));          // Semilla para el random
  bool tieneVirus = false;    // Dice si el archivo tiene virus o no
  int revisiones = 0;         // Cantidad de veces que la revisión de virus dio positiva
  int random = rand() % 100;  // Numero aleatorio que representa si tiene virus o no con respecto al rango de probabilidad
  int  max = 4;               // Límite superior del intervalo [0,4] que representa la propabilidad de tener virus
  int max_revisiones = 3;     // Maximo de revisiones antes de descartar el archivo
  double tiempo_revision = 0; // Tiempo de revision del archivo en busca de virus

  /* Por medio de variables aleatorias se calcula si el archivo tiene virus */
  if(random <= max){
    tieneVirus = true;
    ++revisiones;
  }

  while( tieneVirus && revisiones <= max_revisiones ){
    random = rand() % 100;
    if(random > max){
      tieneVirus = false;
    }
    else{
      ++revisiones;
    }
  }

  ++totalArchivosRevisados;
  acumuladoRevisionesVirus += revisiones;
  promedioRevisionesVirus = acumuladoRevisionesVirus / totalArchivosRevisados;

  /* Se crea un evento para enviar archivo
   * Se encola el evento en la cola de envios
   * Severifica que haya linea disponible
   * Si hay linea disponible, se desencola evento
   * Se programa el envio 
   */
 
  if( revisiones <= max_revisiones ){

    /* Averiguar cuanto dura la revision */
    for(int i = 1; i <= revisiones; ++i){
      tiempo_revision += M/(8*i);
    }

	Evento* paraEnviar = new Evento(Reloj + tiempo_revision, SeEncolaParaEnvio, M,EventoActual->tipoArchivo,
									EventoActual->entradaAlSistema);

    ColaDeEnvios->push_back(paraEnviar);
    PrimedioColaEnvios();

    if (Linea1_Disponible && !ColaDeEnvios->empty() ){
      paraEnviar = ColaDeEnvios->front();
      ColaDeEnvios->pop_front();
      PrimedioColaEnvios();
      paraEnviar->evento = SeLiberaLineaRouter1;

      ManejadorDeEventos->agregarEventoAlaCola(paraEnviar);
      Linea1_Disponible = false;
    }
    else if( Linea2_Disponible && !ColaDeEnvios->empty() ){
      paraEnviar = ColaDeEnvios->front();
      ColaDeEnvios->pop_front();
      PrimedioColaEnvios();
      paraEnviar->evento = SeLiberaLineaRouter2;
      
      ManejadorDeEventos->agregarEventoAlaCola(paraEnviar);
      Linea2_Disponible = false;
    }
  }

  delete EventoActual;

}

void Simulacion::evento_SeLiberaLinea1Router(int M){
	printf("Evento: SeLiberaLineaRouter1 \n");
  Reloj = EventoActual->reloj;
  impresionEstadoActual();
  tiempoArchivos = Reloj - EventoActual->entradaAlSistema;
  NumeroDeArchivos++;
	if(EventoActual->tipoArchivo == 1){
		NumeroDeArchivos1++;
		tiempoArchivos1 = Reloj - EventoActual->entradaAlSistema;
	}
	else{
		NumeroDeArchivos2++;
		tiempoArchivos2 = Reloj - EventoActual->entradaAlSistema;

	}
  if( !ColaDeEnvios->empty() ){
    Evento* paraEnviar = ColaDeEnvios->front();
    ColaDeEnvios->pop_front();
    PrimedioColaEnvios();
    paraEnviar->evento = SeLiberaLineaRouter1;
    paraEnviar->reloj += M/64;
    ManejadorDeEventos->agregarEventoAlaCola(paraEnviar);
    Linea1_Disponible = false;
  }
  else{
    Linea1_Disponible = true;
  }
  
  delete EventoActual;

}

void Simulacion::evento_SeLiberaLinea2Router(int M){
	printf("Evento: SeLiberaLineaRouter2 \n");
  Reloj = EventoActual->reloj;
  tiempoArchivos = Reloj - EventoActual->entradaAlSistema;
  NumeroDeArchivos++;
  if(EventoActual->tipoArchivo == 1){
	  NumeroDeArchivos1++;
	  tiempoArchivos1 = Reloj - EventoActual->entradaAlSistema;
  }
  else{

	  NumeroDeArchivos2++;
	  tiempoArchivos2 = Reloj - EventoActual->entradaAlSistema;

  }
  impresionEstadoActual();
  if( !ColaDeEnvios->empty() ){
    Evento* paraEnviar = ColaDeEnvios->front();
    ColaDeEnvios->pop_front();
    PrimedioColaEnvios();
    paraEnviar->evento = SeLiberaLineaRouter2;
    paraEnviar->reloj += M/64;
    ManejadorDeEventos->agregarEventoAlaCola(paraEnviar);
    Linea2_Disponible = false;
  }
  else{
    Linea2_Disponible = true;
  }

  delete EventoActual;

}

void Simulacion::PrimedioColaEnvios(){
  ++cantRevisionesColaEnvios;
  tamColaEnvios = ColaDeEnvios->size();
  tamPromedioColaEnvios = tamColaEnvios / cantRevisionesColaEnvios;

}

void Simulacion::evento_LlegaAServidorAntivirus()
{
	printf("Evento:LlegaAServidorAntivirus \n");
    Reloj = EventoActual->reloj;
    impresionEstadoActual();
	Evento* Finaliza = new Evento(Reloj,FinalizaRevisionDeVirus,EventoActual->tamano,EventoActual->tipoArchivo,
								  EventoActual->entradaAlSistema);
    ManejadorDeEventos->agregarEventoAlaCola(Finaliza);
    delete EventoActual;
}

void Simulacion::impresionEstadoActual()
{
    printf("Reloj: %f \n",Reloj);
	//printf("Evento actual: %d \n",EventoActual->evento);
    printf("Tiempo T del token: %d \n", tiempoToken);
    printf("Cola 1 Computadora A: %d \n Cola 2 Computadora A: %d \n",
		   ComputadoraA->Tipo1Size(),
		   ComputadoraA->Tipo2Size());
    printf("Cola 1 Computadora B: %d \n Cola 2 Computadora B: %d \n",
		   ComputadoraB->Tipo1Size(),
		   ComputadoraB->Tipo2Size());
    printf("Cola 1 Computadora C: %d \n Cola 2 Computadora C: %d \n",
		   ComputadoraC->Tipo1Size(),
		   ComputadoraC->Tipo2Size());
	printf("Linea 1 para envios desocupada: %s \n", Linea1_Disponible ? "si" : "no");
	printf("Linea 1 para envios desocupada: %s \n", Linea2_Disponible ? "si" : "no");
	printf("Cola de archivos esperando ser pasados al router para envio: %d \n", ColaDeEnvios->size() );
	/**
	 * if(ColaDeEnvios->size() > 0){
		sleep(1);
	}
	*/


}

void Simulacion::impresionTerminoSimulacion()
{
	printf("\nSimulacion Termino! \n");
	printf("Tamano promedio de la cola de envios: %f \n", tamPromedioColaEnvios);
	printf("Tiempo promedio de los archivos en el sistema en general: %f \n",tiempoArchivos / NumeroDeArchivos);
	printf("Tiempo promedio en el sistema de los archivos tipo 1: %f \n",tiempoArchivos1/NumeroDeArchivos1);
	printf("Tiempo promedio en el sistema de los archivos tipo 2: %f \n",tiempoArchivos2/NumeroDeArchivos2);
  printf("Numero promedio de revisiones del antivirus por archivo: %d \n", promedioRevisionesVirus);
  
  proms[0] = tamPromedioColaEnvios;
  proms[1] = tiempoArchivos / NumeroDeArchivos;
  proms[2] = tiempoArchivos1 / NumeroDeArchivos1;
  proms[3] = tiempoArchivos2 / NumeroDeArchivos2;
  proms[4] = promedioRevisionesVirus;

}