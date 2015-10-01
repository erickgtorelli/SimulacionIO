#ifndef COMPUTADORA_H
#define COMPUTADORA_H
#include "Util.h"

class Archivos{
public:
    int tamano;
	double entradaAlSistema;
	Archivos(int tamano,double entradaAlSistema);
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

    int Tipo1Size();
    int Tipo2Size();
    /**
     * @brief sacarArchivoTipo1
     * @param Max es el tamano maximo que se puede trasmitir
     * @return copia del archivo que estaba en la cola, si retorna null quiere decir que no se puede mandar ningun archivo
     */
    Archivos* sacarArchivoTipo1(int Max);
    Archivos* sacarArchivoTipo2(int Max);
};

#endif // COMPUTADORA_H
