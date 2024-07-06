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

        int NComponentesFConexas(); //NO LISTO
        list<Tipo> caminoMenor(Tipo v, Tipo w);
};


template<typename Tipo>
GrafoDirigido<int> GrafoDirigido<Tipo>::mapear(vector<Tipo> *mapeo){
    Vertice<Tipo> *actual = this->primero;
    int i=0, dim=this->getNVertices();
    GrafoDirigido<int> grafo;
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

template<>
int GrafoDirigido<int>::NComponentesFConexas(){
    int nComponentes=1, i=0,j;
    vector<bool> visitados;
    for(i=0;i<this->getNVertices();i++){
        visitados.emplace_back(false);
    }
    for (j=0;j<this->getNVertices(); j++){
        cout<<j<<endl;
        //Inicializar vector de visitados
        if(j>0){
            for(i=0;i<this->getNVertices();i++){
                visitados.at(i) = false;
            }
        }

        this->BFS(j,&visitados);

        for(i=0;i<this->getNVertices();i++){
            if (!visitados.at(i)){
                this->BFS(i,&visitados);
                cout << i << " No habia sido visitado"<<endl;
                nComponentes++;
            }
        }
    }
    return nComponentes;
}

template <typename Tipo>
list<Tipo> GrafoDirigido<Tipo>::caminoMenor(Tipo v, Tipo w){
    vector<Tipo> mapeo;
    GrafoDirigido<int> aux = this->mapear(&mapeo);
    int inicio = this->buscarMapeo(mapeo, v, this->getNVertices()), fin = this->buscarMapeo(mapeo, w, this->getNVertices());
    list<int> camino = aux.caminoDijkstra(inicio, fin);

    list<Tipo> resultado;
    while(!camino.empty()){
        resultado.push_back(mapeo[camino.front()]);
        camino.pop_front();
    }
    return resultado;
}
#endif