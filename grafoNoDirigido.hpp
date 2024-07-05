#ifndef GRAFONODIRIGIDO_H_
#define GRAFONODIRIGIDO_H_

#include <list>
#include <vector>
#include "grafo.hpp"
using namespace std;

template <typename Tipo>
class GrafoNoDirigido: public Grafo<Tipo>{
    public:
        list<Tipo> vecinos(Vertice<Tipo> *v); //FUNCIONAL
        list<Tipo> vecinos(Tipo v); //FUNCIONAL

        //ARCOS
        void modificarPesoArcoND(Tipo v, Tipo w, float nuevo); //FUNCIONAL
        void agregarArcoND(Tipo v, Tipo w, float peso = 0); //FUNCIONAL
        void eliminarArcoND(Tipo v, Tipo w); //FUNCIONAL
        //VERTICES

        GrafoNoDirigido<int> mapear(vector<Tipo> *mapeo);
};


template<typename Tipo>
list<Tipo> GrafoNoDirigido<Tipo>::vecinos(Vertice<Tipo> *v){
    list<Tipo> lista;

    Arco<Tipo> *arco;
    if(v!=nullptr){
        arco = v->getArcos();

        while (arco!=nullptr){
            lista.push_back(arco->getInfo()->getInfo());
            arco = arco->getSig();
        }
    }

    return lista;            
}
template<typename Tipo>
list<Tipo> GrafoNoDirigido<Tipo>::vecinos(Tipo v){
    return this->vecinos(this->getVertice(v));            
}
//OPERACIONES CON ARCOS ============================================================

template <typename Tipo>
void GrafoNoDirigido<Tipo>::modificarPesoArcoND(Tipo v, Tipo w, float nuevo){
    this->modificarPesoArco(v,w,nuevo);
    this->modificarPesoArco(w,v,nuevo);
}

template <typename Tipo>
void GrafoNoDirigido<Tipo>::agregarArcoND(Tipo v, Tipo w, float peso){
    this->agregarArco(v,w,peso);
    this->agregarArco(w,v,peso);
}

template <typename Tipo>
void GrafoNoDirigido<Tipo>::eliminarArcoND(Tipo v, Tipo w){
    this->eliminarArco(v,w);
    this->eliminarArco(w,v);
}


//OPERACIONES CON VERTICES ================================================================



template<typename Tipo>
GrafoNoDirigido<int> GrafoNoDirigido<Tipo>::mapear(vector<Tipo> *mapeo){
    Vertice<Tipo> *actual = this->primero;
    int i=0, dim=this->getNVertices();
    GrafoNoDirigido<int> grafo;
    Arco<Tipo> *arco;
    grafo.construir();
    //MAPEAR Y AGREGAR VERTICES AL GRAFO MAPEADO
    while(actual!=nullptr){
        mapeo->emplace_back(actual->getInfo());
        grafo.agregarVertice(i);
        actual=actual->getSig();
        i++;
    }

    //AGREGAR ARCOS AL GRAFO MAPEADO
    actual = this->primero;
    i=0;
    while(actual != nullptr){
        arco = actual->getArcos();
        while(arco != nullptr){
            int v = this->buscarMapeo(*mapeo, arco->getInfo()->getInfo(), dim);
            grafo.agregarArco(i,v, arco->getPeso());
            arco=arco->getSig();
        }
        actual=actual->getSig();
        i++;
    }

    return grafo;

}
#endif