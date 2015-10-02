/* 
 * File:   main.cpp
 * Author: erick
 *
 * Created on September 19, 2015, 2:09 PM
 */

#include <cstdlib>
#include "Util.h"
#include <iostream>
#include "Simulacion.h"
using namespace std;

/*
 * 
 */

double promedios[5]= {0,0,0,0,0};

void impresionDePromedios()
{
	printf("\nTodas las simulaicones terminaron! \n");
	printf("Tamano promedio de las colas de envios: %f \n", promedios[0]);
	printf("Tiempo promedio de los archivos en los sistemas en general: %f \n",promedios[1]);
	printf("Tiempo promedio en los sistemas de los archivos tipo 1: %f \n",promedios[2]);
	printf("Tiempo promedio en los sistemas de los archivos tipo 2: %f \n",promedios[3]);
  	printf("Numero promedio de las revisiones de antivirus por archivo: %d \n", promedios[4]);
}

int main(int argc, char** argv) {
    
	int tiempoPorSimulacion;
	int tiempoToken;
	int numeroDeVeces;
	int modoLento = 0;

    printf("¿Cuantas veces quiere correr la simulación? \n");
	scanf("%d",&numeroDeVeces);
    printf("¿Cuanto tiempo desea por simulación? \n");
	scanf("%d",&tiempoPorSimulacion);
    printf("¿Cuanto es el tiempo de token por computadora? \n");
	scanf("%d",&tiempoToken);
    printf("¿Desea activar el modo lento? 1 para Si \n");
	scanf("%d",&modoLento);

	//Corre la simulacion varias veces
	for(int i=0;i<numeroDeVeces;i++){
		Simulacion* Sim = new Simulacion();
		double* temp = Sim->run(tiempoPorSimulacion,tiempoToken,modoLento);
		for (int i = 0; i < 5; ++i){
			promedios[i] += temp[i];		
		}
		delete Sim;
	}
	
	for (int i = 0; i < 5; ++i){
		promedios[i] /= numeroDeVeces;		
	}

	impresionDePromedios();

    return 0;
}

