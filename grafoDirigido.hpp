#ifndef GRAFODDIRIGIDO_H_
#define GRAFODDIRIGIDO_H_

#include <list>
#include <vector>
#include "grafo.hpp"
using namespace std;

template <typename Tipo>
class GrafoDirigido: public Grafo<Tipo>{
    public:
        GrafoDirigido<int> mapear(vector<Tipo> *mapeo);
        //Tipos
        bool esSumidero(Tipo v);
        bool esFuente(Tipo v);
};


template<typename Tipo>
GrafoDirigido<int> GrafoDirigido<Tipo>::mapear(vector<Tipo> *mapeo){
    Vertice<Tipo> *actual = this->primero;
    int i=0, dim=this->getNVertices();
    GrafoDirigido<int> grafo;
    Arco<Tipo> *arco;
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
            grafo.agregarArco(i,v);
        }

        arco=arco->getSig();
        i++;
    }

    return grafo;

}
template <typename Tipo>
bool GrafoDirigido<Tipo>::esSumidero(Tipo v){
    list<Tipo> L = this->sucesores(v);
    return L.empty();
}
template <typename Tipo>
bool GrafoDirigido<Tipo>::esFuente(Tipo v){
    list<Tipo> L = this->predecesores(v);
    return L.empty();
}
#endif