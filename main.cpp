/* 
 * File:   main.cpp
 * Author: erick
 *
 * Created on September 19, 2015, 2:09 PM
 */

#include <cstdlib>
#include "Util.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Util* test = new Util();
    Evento* eve1 = new Evento(16,LlegaAComputadoraA);
    Evento* eve2 = new Evento(30,LlegaAComputadoraA);
    Evento* eve3 = new Evento(45,LlegaAComputadoraA);
    Evento* eve4 = new Evento(10,LlegaAComputadoraA);
    
    test->agregarEventoAlaCola(eve1);
    test->agregarEventoAlaCola(eve2);
    test->agregarEventoAlaCola(eve3);
    test->agregarEventoAlaCola(eve4);
    
    Evento* eventoSacado1 = test->sacarSiguienteEvento();
    Evento* eventoSacado2 = test->sacarSiguienteEvento();
      Evento* eventoSacado3 = test->sacarSiguienteEvento();
    Evento* eventoSacado4 = test->sacarSiguienteEvento();
    
    cout << eventoSacado1->reloj;
     cout << eventoSacado2->reloj;
       cout << eventoSacado3->reloj;
     cout << eventoSacado4->reloj;
    return 0;
}

