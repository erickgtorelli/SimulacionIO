#include "Computadora.h"

Computadora::Computadora()
{
    ArchivosTipo1 = new std::list<Archivos*>;
    ArchivosTipo2 = new std::list<Archivos*>;
}

Computadora::~Computadora()
{
    std::list<Archivos*>::iterator current = ArchivosTipo1->begin();
    for(current;current != ArchivosTipo1->end();current++){
        delete *current;
    }
    delete ArchivosTipo1;
    std::list<Archivos*>::iterator current1 = ArchivosTipo2->begin();
    for(current1;current1 != ArchivosTipo2->end();current1++){
        delete *current1;
    }
    delete ArchivosTipo2;
}

bool Computadora::agregarArchivoTipo1(Archivos* archivo)
{
    std::list<Archivos*>::iterator current = ArchivosTipo1->begin();
    bool done = false;

    //En caso de que sea el primer elemento a insertar
    if(current == ArchivosTipo1->end()){
        ArchivosTipo1->insert(current,archivo);
        done = true;
    }

    //En caso de que ya haya elementos
    while(current != ArchivosTipo1->end() && !done ){
        if(archivo->tamano >= (*current)->tamano){
            ArchivosTipo1->insert(current,archivo);
            done = true;
        }
        current++;
    }
    //Caso de agregar al final
     if(current == ArchivosTipo1->end() && !done){
        ArchivosTipo1->push_back(archivo);
        done = true;
    }

    return done;

}

Archivos *Computadora::sacarArchivoTipo1(int Max)
{
    Archivos* archivo = nullptr;
    std::list<Archivos*>::iterator current = ArchivosTipo1->begin();
    bool done = false;
    if(*current != nullptr){
    while(current != ArchivosTipo1->end() && !done ){
        if((*current)->tamano <= Max){
            archivo = *(current);
            ArchivosTipo1->erase(current);
            done = true;
        }
        current++;
    }

    }
    return archivo;
}

Archivos *Computadora::sacarArchivoTipo2(int Max)
{
    Archivos* archivo = nullptr;
    std::list<Archivos*>::iterator current = ArchivosTipo2->begin();
    bool done = false;
    if(*current != nullptr){
    while(current != ArchivosTipo2->end() && !done ){
        if((*current)->tamano <= Max){
            archivo = *current;
            ArchivosTipo2->erase(current);
            done = true;
        }
        current++;
    }

    }
    return archivo;
}

bool Computadora::agregarArchivoTipo2(Archivos* archivo)
{
    std::list<Archivos*>::iterator current = ArchivosTipo2->begin();
    bool done = false;

    //En caso de que sea el primer elemento a insertar
    if(current == ArchivosTipo2->end()){
        ArchivosTipo1->insert(current,archivo);
        done = true;
    }

    //En caso de que ya haya elementos
    while(current != ArchivosTipo2->end() && !done ){
        if(archivo->tamano >= (**current).tamano){
            ArchivosTipo2->insert(current,archivo);
            done = true;
        }
        current++;
    }
    //Caso de agregar al final
     if(current == ArchivosTipo2->end() && !done){
        ArchivosTipo2->push_back(archivo);
        done = true;
    }

    return done;

}

bool Computadora::Tipo1Vacia()
{
    return ArchivosTipo1->empty();
}

bool Computadora::Tipo2Vacia()
{
    return ArchivosTipo2->empty();
}

int Computadora::Tipo1Size()
{
    return ArchivosTipo1->size();
}

int Computadora::Tipo2Size()
{
    return ArchivosTipo2->size();
}


Archivos::Archivos(int tamano)
{
    this->tamano = tamano;
}
