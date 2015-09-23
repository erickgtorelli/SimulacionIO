/* 
 * File:   Util.cpp
 * Author: Erick
 * 
 * Created on September 19, 2015, 2:11 PM
 */

#include "Util.h"
Evento::Evento(){
    
}
Evento::Evento(double reloj, Nombre evento){
    this->reloj = reloj;
    this->evento = evento;
    
}
Evento::~Evento(){
    
}
Util::Util() {
    ColaDeEventos = new std::list<Evento*>;
    
}

Util::Util(const Util& orig) {
}

Util::~Util() {
    delete ColaDeEventos;
}

bool Util::agregarEventoAlaCola(Evento* event){
    std::list<Evento*>::iterator current = ColaDeEventos->begin();
    bool done = false;
    
    //En caso de que sea el primer elemento a insertar
    if(current == ColaDeEventos->end()){
        ColaDeEventos->insert(current,event);
        done = true;
    }
    
    //En caso de que ya haya elementos
    while(current != ColaDeEventos->end() && !done ){
        if(event->reloj >= (*current)->reloj){
            ColaDeEventos->insert(current,event);
            done = true;
        }
        current++;
    }
    //Caso de agregar al final
     if(current == ColaDeEventos->end() && !done){
        ColaDeEventos->push_back(event);
        done = true;
    }
    
    return done;
            
}
bool Util::colaVacia(){
    return ColaDeEventos->empty();
}
Evento* Util::sacarSiguienteEvento(){
    
    if(!colaVacia()){
    Evento* element = ColaDeEventos->back();
    ColaDeEventos->pop_back();
    return element;
    
    }
}
