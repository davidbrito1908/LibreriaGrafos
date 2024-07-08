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
        list<list<Tipo>> caminosHamiltonianos();
        list<Tipo> caminoHamiltonianoMinimo();
        list<list<Tipo>> ciclosHamiltonianos();
        list<list<int>> caminosEulerianos();
        void eulerianos(list<int> *cam, int v, list<list<int>> *caminos);
        list<list<Tipo>> getCaminosEulerianos();

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
template <typename Tipo>
list<list<Tipo>> GrafoDirigido<Tipo>::caminosHamiltonianos(){
    int i,j, nVisitados = 1;
    list<list<int>> result;
    list<list<Tipo>> hamiltonianos;
    list<int> camAux;
    list<Tipo> cam;
    vector<bool> visitados;
    float peso=0;
    vector<Tipo> m;
    GrafoDirigido<int> aux = this->mapear(&m); 
    for(i=0;i<this->nVertices;i++){
        visitados.emplace_back(false);
    }

    for(i=0;i<this->nVertices;i++){
        peso = 0;
        nVisitados=1;
        for(j=0;j<this->nVertices;j++){
            visitados.at(j) = false;
        }
        visitados.at(i) = true;
        camAux.clear();
        camAux.push_back(i);
        aux.hamiltonianos(i,&visitados, &nVisitados, &peso, &result, &camAux);

    }
    //DESMAPEAR CAMINOS
    while(!result.empty()){
        cam.clear();
        camAux = result.front();
        while(!camAux.empty()){
            cam.push_back(m.at(camAux.front()));
            camAux.pop_front();
        }
        //AGREGAR CAMINO DESMAPEADO
        hamiltonianos.push_back(cam);
        result.pop_front();
    }
    return hamiltonianos;
}
template <typename Tipo>
list<Tipo> GrafoDirigido<Tipo>::caminoHamiltonianoMinimo(){
    int i,j, nVisitados = 1;
    list<int> resultAux;
    list<Tipo> result;
    list<int> camAux;
    list<Tipo> cam;
    vector<bool> visitados;
    float peso=0, menor=0;
    bool prim = true;
    vector<Tipo> m;
    GrafoDirigido<int> aux = this->mapear(&m); 
    for(i=0;i<this->nVertices;i++){
        visitados.emplace_back(false);
    }

    for(i=0;i<this->nVertices;i++){
        peso = 0;
        nVisitados=1;
        for(j=0;j<this->nVertices;j++){
            visitados.at(j) = false;
        }
        visitados.at(i) = true;
        camAux.clear();
        camAux.push_back(i);
        aux.hamiltonianoMinimo(i,&visitados, &nVisitados, &peso,&menor, &resultAux, &camAux, &prim);

    }
    //DESMAPEAR CAMINO
    while(!resultAux.empty()){
        result.push_back(m.at(resultAux.front()));
        resultAux.pop_front();
    }
    return result;
}
template<typename Tipo>
list<list<Tipo>> GrafoDirigido<Tipo>::ciclosHamiltonianos(){
    int i,j, nVisitados = 1;
    list<list<int>> result;
    list<list<Tipo>> hamiltonianos;
    list<int> camAux;
    list<Tipo> cam;
    vector<bool> visitados;
    float peso=0;
    vector<Tipo> m;
    GrafoDirigido<int> aux = this->mapear(&m); 
    for(i=0;i<this->nVertices;i++){
        visitados.emplace_back(false);
    }

    for(i=0;i<this->nVertices;i++){
        peso = 0;
        nVisitados=1;
        for(j=0;j<this->nVertices;j++){
            visitados.at(j) = false;
        }
        camAux.clear();
        cam.clear();
        camAux.push_back(i);
        aux.cHamiltonianos(i, i, &visitados, &nVisitados, &peso, &result, &camAux);

    }
    //DESMAPEAR CAMINOS
    while(!result.empty()){
        cam.clear();
        camAux = result.front();
        while(!camAux.empty()){
            cam.push_back(m.at(camAux.front()));
            camAux.pop_front();
        }
        //AGREGAR CAMINO DESMAPEADO
        hamiltonianos.push_back(cam);
        result.pop_front();
    }
    return hamiltonianos;
}
template<>
void GrafoDirigido<int>::eulerianos(list<int> *cam, int v, list<list<int>> *caminos){
    list<int> sucesores = this->sucesores(v);
    int w;
    while(!sucesores.empty()){
        w = sucesores.front();
        cam->push_back(w);
        this->eliminarArco(v,w);
        if(this->nArcos == 0){
            caminos->push_back(*cam);

        }   
        this->eulerianos(cam, w, caminos);

        this->agregarArco(v,w);
        cam->pop_back();
        sucesores.pop_front();
    }
}

template<>
list<list<int>> GrafoDirigido<int>::caminosEulerianos(){
    list<int> caminoAux;
    list<list<int>> caminos;
    vector<int> in, out;
    int v=-1;
    this->contarGrados(&in, &out);
    if(this->existeEuleriano(in, out, &v)){
        for(int i=0; i<this->nVertices;i++){
            caminoAux.push_back(i);
            this->eulerianos(&caminoAux,i, &caminos);
            caminoAux.clear();
        }
    }
    return caminos;
}


template<typename Tipo>
list<list<Tipo>> GrafoDirigido<Tipo>::getCaminosEulerianos(){
    vector<Tipo> m;
    GrafoDirigido<int> grafoM = this->mapear(&m);
    list<list<int>> resultM = grafoM.caminosEulerianos();
    list<list<Tipo>> result;
    list<int> aux;
    list<Tipo> cam;
    //DESMAPEAR CAMINOS EULERIANOS
    while(!resultM.empty()){
        aux=resultM.front();
        while(!aux.empty()){
            cam.push_back(m.at(aux.front()));
            aux.pop_front();
        }
        result.push_back(cam);
        cam.clear();
        resultM.pop_front();
    }
    return result;
}

#endif