/* 
 * File:   Util.h
 * Author: Erick
 *
 * Created on September 19, 2015, 2:11 PM
 */

#ifndef UTIL_H
#define	UTIL_H
#include <list>

//Nombres respectivos de los eventos
enum Nombre{LlegaAComputadoraA,LlegaAComputadoraB,LlegaAComputadoraC,LiberaTokenA,LiberaTokenB,LiberaTokenC,
           TerminaDePonerEnLinea,LlegaAServidorAntivirus,
			FinalizaRevisionDeVirus,SeLiberaLineaRouter1,SeLiberaLineaRouter2,SeEncolaParaEnvio,};





class Evento {
public:
	double reloj;
    Nombre evento;
	int tamano;
    
    Evento();
    Evento(double reloj,Nombre evento,int tamano = 0);
    ~Evento();
};

class Util {
    
public:
    
  
    bool agregarEventoAlaCola(Evento* event);
    Evento* sacarSiguienteEvento();
    bool colaVacia();
    Util();
    Util(const Util& orig);
    virtual ~Util();
private:
    std::list<Evento*>* ColaDeEventos;

};

#endif	/* UTIL_H */

