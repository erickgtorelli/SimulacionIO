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
enum Nombre{LlegaAComputadoraA,LlegaAComputadoraB,LlegaAComputadoraC};

class Evento {
public:
    int reloj;
    Nombre evento;
    
    Evento();
    Evento(int reloj,Nombre evento);
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

