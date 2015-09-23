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
		   TernimaDePonerEnLineaA,TernimaDePonerEnLineaB,TernimaDePonerEnLineaC,LlegaAServidorAntivirus,
			FinalizaRevisionDeVirus,SeLiberaLineaRouter1,SeLiberaLineaRouter2};

class Archivos{
public:
	int tamano;

	Archivos(int tamano);
};

class Computadora{
private:
	std::list<Archivos*>* ArchivosTipo1;
	std::list<Archivos*>* ArchivosTipo2;
public:
	Computadora();
	~Computadora();
	/**
	 * @brief agregarArchivoTipo1 la cola es ordenada del archivo mas grande al principio y el mas pequeno al final
	 * @return
	 */
	bool agregarArchivoTipo1(Archivos *archivo);
	bool agregarArchivoTipo2(Archivos *archivo);
	/**
	 * @brief Tipo1Vacia
	 * @return true si la cola esta vacia
	 */
	bool Tipo1Vacia();
	bool Tipo2Vacia();
	/**
	 * @brief sacarArchivoTipo1
	 * @param Max es el tamano maximo que se puede trasmitir
	 * @return copia del archivo que estaba en la cola, si retorna null quiere decir que no se puede mandar ningun archivo
	 */
	Archivos* sacarArchivoTipo1(int Max);
	Archivos* sacarArchivoTipo2(int Max);
};

class Evento {
public:
	double reloj;
    Nombre evento;
	int tamano;
    
    Evento();
	Evento(double reloj,Nombre evento);
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

