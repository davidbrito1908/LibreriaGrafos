#ifndef GRAFONODIRIGIDO_H_
#define GRAFONODIRIGIDO_H_

#include <list>
#include <vector>
#include "grafo.hpp"
using namespace std;

template <typename Tipo>
class GrafoNoDirigido: public Grafo<Tipo>{
    public:
        void copiar(Grafo<Tipo> *A);
        list<Tipo> vecinos(Vertice<Tipo> *v); //FUNCIONAL
        list<Tipo> vecinos(Tipo v); //FUNCIONAL

        //ARCOS
        void modificarPesoArcoND(Tipo v, Tipo w, float nuevo); //FUNCIONAL
        void agregarArcoND(Tipo v, Tipo w, float peso = 0); //FUNCIONAL
        void eliminarArcoND(Tipo v, Tipo w); //FUNCIONAL
        //VERTICES

        GrafoNoDirigido<int> mapear(vector<Tipo> *mapeo);
        //RECORRIDOS

        //COMPONENTES CONEXAS (SOLO GRAFOS MAPEADOS)
        int NComponentes(); //FUNCIONAL

        list<Tipo> caminoMenor(Tipo v, Tipo w);
        list<Tipo> caminoMenorConBloqueo(Tipo v, Tipo w, list<Tipo> bloqueados);
        list<Tipo> caminoMayor(Tipo v, Tipo w);
        void arbolExpandidoMinimo(GrafoNoDirigido<int> *g, float *peso);
        void arcoMinimo(list<int> activos, int *v, int *w, float *peso, vector<bool> visitados, bool *band);
        list<list<Tipo>> puentes();
        bool esConexo();
        list<list<Tipo>> caminosHamiltonianos();
        list<Tipo> caminoHamiltonianoMinimo();
        list<list<Tipo>> ciclosHamiltonianos();
        void eulerianos(list<int> *cam, int v, list<list<int>> *caminos);
        list<list<Tipo>> getCaminosEulerianos();


        //PARA GRAFOS QUE YA ESTEN MAPEADOS
        list<list<int>> caminosEulerianos();
        bool esConexoM();
        list<list<Tipo>> puentesM();
};



template<typename Tipo>
void GrafoNoDirigido<Tipo>::copiar(Grafo<Tipo> *A){
    Vertice<Tipo> *aux;
    Arco<Tipo> *arco;
    float pesoAux;
    aux = A->getPrimero();
    while(aux != nullptr){
        this->agregarVertice(aux->getInfo());
        aux = aux->getSig();
    }
    aux = A->getPrimero();
    while(aux != nullptr){
        arco = aux->getArcos();
        while(arco != nullptr){
            pesoAux = arco->getPeso();
            this->agregarArcoND(aux->getInfo(), arco->getInfo()->getInfo(), pesoAux);
            arco = arco->getSig();
        }
        aux = aux->getSig();
    }
}


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
            grafo.agregarArcoND(i,v, arco->getPeso());
            arco=arco->getSig();
        }
        actual=actual->getSig();
        i++;
    }

    return grafo;

}

//COMPONENTES CONEXAS
template<>
int GrafoNoDirigido<int>::NComponentes(){
    int nComponentes=1, i=0;
    vector<bool> visitados;
    //Inicializar vector de visitados
    for(i=0;i<this->getNVertices();i++){
        visitados.emplace_back(false);
    }

    this->BFS(0,&visitados);

    for(i=0;i<this->getNVertices();i++){
        if (!visitados.at(i)){
            this->BFS(i,&visitados);
            cout << i << " No habia sido visitado"<<endl;
            nComponentes++;
        }
    }
    return nComponentes;
}
template <typename Tipo>
list<Tipo> GrafoNoDirigido<Tipo>::caminoMenor(Tipo v, Tipo w){
    vector<Tipo> mapeo;
    GrafoNoDirigido<int> aux = this->mapear(&mapeo);
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
list<Tipo> GrafoNoDirigido<Tipo>::caminoMenorConBloqueo(Tipo v, Tipo w, list<Tipo> bloqueados){ 
    vector<Tipo> mapeo;
    GrafoNoDirigido<int> aux = this->mapear(&mapeo);
    int inicio = this->buscarMapeo(mapeo, v, this->getNVertices()), fin = this->buscarMapeo(mapeo, w, this->getNVertices()), i;
    list<int> camino;
    vector<bool> bloqueos;
    for (i=0;i<this->nVertices;i++){
        bloqueos.emplace_back(false);
    }
    while(!bloqueados.empty()){
        bloqueos.at(this->buscarMapeo(mapeo, bloqueados.front(), this->getNVertices())) = true;
        bloqueados.pop_front();
    }
    camino = aux.caminoObstaculos(inicio, fin, bloqueos);

    list<Tipo> resultado;
    while(!camino.empty()){
        resultado.push_back(mapeo[camino.front()]);
        camino.pop_front();
    }
    return resultado;
}
template <typename Tipo>
list<Tipo> GrafoNoDirigido<Tipo>::caminoMayor(Tipo v, Tipo w){
    vector<Tipo> mapeo;
    GrafoNoDirigido<int> aux = this->mapear(&mapeo);
    int inicio = this->buscarMapeo(mapeo, v, this->getNVertices()), fin = this->buscarMapeo(mapeo, w, this->getNVertices());
    list<int> camino, caminoMayor;
    vector<bool> visitados;
    float peso=0, pesoMayor = -1;
    bool primero = true;

    int i;
    for(i = 0; i<this->getNVertices(); i++){
        visitados.emplace_back(false);
    }

    camino.push_back(inicio);
    aux.mayorCamino(inicio, fin, peso, &visitados, &camino, &pesoMayor, &caminoMayor, &primero);

    list<Tipo> resultado;
    while(!caminoMayor.empty()){
        resultado.push_back(mapeo[caminoMayor.front()]);
        caminoMayor.pop_front();
    }
    return resultado;
}

template<typename Tipo>
void GrafoNoDirigido<Tipo>::arbolExpandidoMinimo(GrafoNoDirigido<int> *g, float *peso){
    vector<bool> visitados;
    int i,v,w;
    bool fin, band=false;
    list<int> vertices, activos;
    float p;

    for(i=0;i<this->getNVertices();i++){
        g->agregarVertice(i);
        visitados.emplace_back(false);
    }

    activos.push_back(0);
    visitados.at(0) = true;
    fin = false;
    p=0;
    *peso=0;
    while(!fin){
        this->arcoMinimo(activos,&v,&w,&p,visitados, &band);
        g->agregarArcoND(v,w, p);
        *peso = *peso + p;
        activos.push_back(w);
        visitados.at(w) = true;

        fin = true;
        if(!band){
            for ( i = 0; i< this->getNVertices(); i++){
                fin = fin && visitados.at(i);
            }
        }else{
            *peso = 0;
        }
    }

}
template<typename Tipo>
void GrafoNoDirigido<Tipo>::arcoMinimo(list<int> activos, int *v, int *w, float *peso, vector<bool> visitados, bool *band){
    int actual, act;
    list<int> vecinos;
    float pesoArco;
    bool prim=false;

    while(!activos.empty()){
        actual = activos.front();
        vecinos = this->vecinos(actual);
        while(!vecinos.empty()){
            act = vecinos.front();
            if (!visitados.at(act)){
                pesoArco = this->getPesoArco(actual, act);
                if((pesoArco<*peso) || (!prim)){
                    *peso = pesoArco;
                    *v = actual;
                    *w = act;
                    prim=true;
                }
            }
            vecinos.pop_front();
        }
        activos.pop_front();
    }
    //Si no se pudo procesar ni un solo arco, se activa la bandera band para finalizar el proceso
    if(!prim){
        *band = true;
    }
}
template <typename Tipo>
bool GrafoNoDirigido<Tipo>::esConexo(){ //METODO PARA GRAFOS YA MAPEADOS
    vector<Tipo> mapeo;
    vector<bool> visitados;
    int i;
    //MAPEAR GRAFO
    GrafoNoDirigido<int> g = this->mapear(&mapeo);
    //INICIALIZAR VECTOR DE VISITADOS
    for(i=0;i<this->nVertices;i++){
        visitados.emplace_back(false);
    }
    //REALIZAR RECORRIDO BFS
    g.BFS(0, &visitados);
    //VERIFICAR QUE SE HAYAN VISITADOS TODOS LOS VERTICES
    for(i=0;i<this->nVertices;i++){
        if(!visitados.at(i)) return false;
    }

    return true;
}
template <typename Tipo>
bool GrafoNoDirigido<Tipo>::esConexoM(){
    vector<bool> visitados;
    int i;
    //INICIALIZAR VECTOR DE VISITADOS
    for(i=0;i<this->nVertices;i++){
        visitados.emplace_back(false);
    }
    //REALIZAR RECORRIDO BFS
    this->BFS(0, &visitados);
    //VERIFICAR QUE SE HAYAN VISITADOS TODOS LOS VERTICES
    for(i=0;i<this->nVertices;i++){
        if(!visitados.at(i)) return false;
    }

    return true;
}
template<typename Tipo>
list<list<Tipo>> GrafoNoDirigido<Tipo>::puentes(){
    list<list<Tipo>> arcosPuente;
    list<Tipo> arco;
    list<int> vecinos;
    int i,w;
    vector<Tipo> m;
    GrafoNoDirigido<int> aux = this->mapear(&m);//MAPEAR GRAFO O(N+M)

    for (i=0; i<this->nVertices; i++){ //RECORRER VERTICES 
        vecinos = aux.vecinos(i);
        //RECORRER ARCOS
        while(!vecinos.empty()){
            w = vecinos.front();
            //ELIMINAR ARCO
            aux.eliminarArcoND(i,w);
            //VERIFICAR QUE EL GRAFO SIGA CONEXO (Si no es conexo, el arco es un arco puente)
            if((!aux.esConexo()) && (i<w)){
                //Agregar arco a la lista de arcos puente
                arco.clear();
                arco.push_back(m.at(i));
                arco.push_back(m.at(w));
                arcosPuente.push_back(arco);
            }
            //VOLVER A AGREGAR EL ARCO ELIMINADO
            aux.agregarArcoND(i,w);
            vecinos.pop_front();
        }

    }
    return arcosPuente;
}
template<typename Tipo>
list<list<Tipo>> GrafoNoDirigido<Tipo>::puentesM(){
    list<list<Tipo>> arcosPuente;
    list<Tipo> arco;
    list<int> vecinos;
    int i,w;

    for (i=0; i<this->nVertices; i++){ //RECORRER VERTICES 
        vecinos = this->vecinos(i);
        //RECORRER ARCOS
        while(!vecinos.empty()){
            w = vecinos.front();
            //ELIMINAR ARCO
            this->eliminarArcoND(i,w);
            //VERIFICAR QUE EL GRAFO SIGA CONEXO (Si no es conexo, el arco es un arco puente)
            if((!this->esConexoM()) && (i<w)){
                //Agregar arco a la lista de arcos puente
                arco.clear();
                arco.push_back(i);
                arco.push_back(w);
                arcosPuente.push_back(arco);
            }
            //VOLVER A AGREGAR EL ARCO ELIMINADO
            this->agregarArcoND(i,w);
            vecinos.pop_front();
        }

    }
    return arcosPuente;
}

template <typename Tipo>
list<list<Tipo>> GrafoNoDirigido<Tipo>::caminosHamiltonianos(){
    int i,j, nVisitados = 1;
    list<list<int>> result;
    list<list<Tipo>> hamiltonianos;
    list<int> camAux;
    list<Tipo> cam;
    vector<bool> visitados;
    float peso=0;
    vector<Tipo> m;
    GrafoNoDirigido<int> aux = this->mapear(&m); 
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
        cam.clear();
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
list<Tipo> GrafoNoDirigido<Tipo>::caminoHamiltonianoMinimo(){
    int i,j, nVisitados = 1;
    list<int> resultAux;
    list<Tipo> result;
    list<int> camAux;
    list<Tipo> cam;
    vector<bool> visitados;
    float peso=0, menor=0;
    bool prim = true;
    vector<Tipo> m;
    GrafoNoDirigido<int> aux = this->mapear(&m); 
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

template <typename Tipo>
list<list<Tipo>> GrafoNoDirigido<Tipo>::ciclosHamiltonianos(){
    int i,j, nVisitados = 1;
    list<list<int>> result;
    list<list<Tipo>> hamiltonianos;
    list<int> camAux;
    list<Tipo> cam;
    vector<bool> visitados;
    float peso=0;
    vector<Tipo> m;
    GrafoNoDirigido<int> aux = this->mapear(&m); 
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
void GrafoNoDirigido<int>::eulerianos(list<int> *cam, int v, list<list<int>> *caminos){
    list<int> vecinos = this->vecinos(v);
    int w;
    while(!vecinos.empty()){
        w = vecinos.front();
        cam->push_back(w);
        this->eliminarArcoND(v,w);
        if(this->nArcos == 0){
            caminos->push_back(*cam);
        }   
        this->eulerianos(cam, w, caminos);

        this->agregarArcoND(v,w);
        cam->pop_back();
        vecinos.pop_front();
    }
}
template<>
list<list<int>> GrafoNoDirigido<int>::caminosEulerianos(){
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
list<list<Tipo>> GrafoNoDirigido<Tipo>::getCaminosEulerianos(){
    vector<Tipo> m;
    GrafoNoDirigido<int> grafoM = this->mapear(&m);
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