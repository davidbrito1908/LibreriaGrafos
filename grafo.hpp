#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <vector>
#include "nodoVertice.hpp"
#include "nodoArco.hpp"
using namespace std;

template <typename Tipo>
class Grafo{
    protected:
        int nVertices, nArcos;
        Vertice<Tipo> *primero;

    public:
        void construir(){
            this->primero = nullptr;
            this->nVertices=0;
            this->nArcos = 0;
        }
        //GETTERS
        int getNVertices();
        int getNArcos();
        Vertice<Tipo> * getPrimero();
        //SETTERS
        void setNVertices(int cant);
        void setNArcos(int cant);
        void setPrimero(Vertice<Tipo> *primero);
        void setPrimero(Tipo primero);

        Vertice<Tipo> * getVertice(Tipo v); //FUNCIONAL

        list<Tipo> sucesores(Vertice<Tipo> *v); //FUNCIONAL
        list<Tipo> sucesores(Tipo v); //FUNCIONAL

        list<Tipo> predecesores(Vertice<Tipo> *v); //FUNCIONAL
        list<Tipo> predecesores(Tipo v); //FUNCIONAL

        //ARCOS
        bool existeArco(Tipo v, Tipo w); //FUNCIONAL
        float getPesoArco(Tipo v, Tipo w); //FUNCIONAL
        void modificarPesoArco(Tipo v, Tipo w, float nuevo); //FUNCIONAL
        void agregarArco(Tipo v, Tipo w, float peso = 0); //FUNCIONAL
        void eliminarArco (Tipo v, Tipo w); //FUNCIONAL
        //VERTICES
        void agregarVertice (Tipo v); //FUNCIONAL
        void eliminarVertice (Tipo v); //FUNCIONAL

        int buscarMapeo(vector<Tipo> arreglo, Tipo elem, int dim);

        void escribirGrafo();
};


//GETTERS ==================================================================
template<typename Tipo>
int Grafo<Tipo>::getNVertices(){
    return this->nVertices;
}
template<typename Tipo>
int Grafo<Tipo>::getNArcos(){
    return this->nArcos;
}
template<typename Tipo>
Vertice<Tipo> * Grafo<Tipo>::getPrimero(){
    return this->primero;
}
template<typename Tipo>
Vertice<Tipo> * Grafo<Tipo>::getVertice(Tipo v){
    Vertice<Tipo> *actual = this->primero;
    while(actual != nullptr){
        if(actual->getInfo() == v){
            return actual;
        }else{
            actual = actual->getSig();
        }
    }
    return nullptr;
}





//SETTERS ===============================================================
template<typename Tipo>
void Grafo<Tipo>::setNVertices(int cant){
    this->nVertices=cant;
}
template<typename Tipo>
void Grafo<Tipo>::setNArcos(int cant){
    this->nArcos=cant;
}
template<typename Tipo>
void Grafo<Tipo>::setPrimero(Vertice<Tipo> *primero){
    this->primero = primero;
}
template<typename Tipo>
void Grafo<Tipo>::setPrimero(Tipo primero){
    Vertice<Tipo> *prim = new (Vertice<Tipo>);
    prim->setInfo(primero);
    prim->setArcos(nullptr);
    prim->setSig(nullptr);
    this->primero = prim;
    this->nVertices = this->nVertices +1;
}



template<typename Tipo>
list<Tipo> Grafo<Tipo>::sucesores(Vertice<Tipo> *v){
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
list<Tipo> Grafo<Tipo>::sucesores(Tipo v){
    return this->sucesores(this->getVertice(v));            
}
template<typename Tipo>
list<Tipo> Grafo<Tipo>::predecesores(Vertice<Tipo> *v){
    list<Tipo> lista;
    Vertice<Tipo> *inicio = this->primero;
    Arco<Tipo> *ady;
    if (v != nullptr){
        while (inicio != nullptr){
            if(inicio != v){
                ady = inicio->getArcos();
                while(ady != nullptr){
                    Vertice<Tipo> *conexion = ady->getInfo();
                    //Si el vertice adyacente es el nodo buscado, se añade a la lista
                    if(conexion == v){
                        lista.push_back(inicio->getInfo());
                    }
                    ady=ady->getSig();
                }
            }
            inicio=inicio->getSig();
        }
    }

    return lista;
}

template<typename Tipo>
list<Tipo> Grafo<Tipo>::predecesores(Tipo v){
    return this->predecesores(this->getVertice(v));            
}


//OPERACIONES CON ARCOS ============================================================
template <typename Tipo>
bool Grafo<Tipo>::existeArco(Tipo v, Tipo w){
    Vertice<Tipo> *inicio = this->primero;
    Arco<Tipo> *ady;
    bool band=false;
    if(inicio != nullptr){
        //ENCONTRAR VERTICE V
        while((inicio != nullptr) && (inicio->getInfo() != v)){
            inicio = inicio->getSig();
        }
        if (inicio == nullptr) return false;
        
        //RECORRER ARCOS DE V
        ady = inicio->getArcos();
        while (!band && ady != nullptr){
            Tipo info = ady->getInfo()->getInfo();
            band = info == w;
            ady=ady->getSig();
        }
        return band;
    }
    return band;
}
template<typename Tipo>
float Grafo<Tipo>::getPesoArco(Tipo v, Tipo w){
    Vertice<Tipo> *inicio = this->primero;
    Arco<Tipo> *ady;
    if (inicio != nullptr){
        //ENCONTRAR VERTICE V
        while((inicio != nullptr) && (inicio->getInfo() != v)){
            inicio = inicio->getSig();
        }
        if (inicio == nullptr){
            cout<<"No existe el vertice "<<v<< " (No se puede ver el peso del arco entre " << v << " y " << w<<") retornando  0"<<endl; //MENSAJE DE AVISO
            return 0;
        }
        
        //RECORRER ARCOS DE V HASTA ENCONTRAR ARCO CON W
        ady = inicio->getArcos();
        while ((ady != nullptr) && (ady->getInfo()->getInfo() != w)){
            ady=ady->getSig();
        }
        if (ady == nullptr){
            cout<<"No existe el arco entre "<<v<< " y "<< w << " (No se puede ver el peso del arco entre " << v << " y " << w<<") retornando 0"<<endl; // MENSAJE DE AVISO
            return 0;
        }

        return ady->getPeso();
    }
    cout<<"El grafo no tiene vertices (retornando 0)"<<endl; //MENSAJE DE AVISO
    return 0;
}

template <typename Tipo>
void Grafo<Tipo>::modificarPesoArco(Tipo v, Tipo w, float nuevo){
    Vertice<Tipo> *inicio = this->primero;
    Arco<Tipo> *ady;
    if(inicio != nullptr){
        //ENCONTRAR VERTICE V
        while((inicio != nullptr) && (inicio->getInfo() != v)){
            inicio = inicio->getSig();
        }
        if (inicio == nullptr) return; //SI V NO EXISTE -> SALIR DEL METODO

        //RECORRER ARCOS DE V HASTA ENCONTRAR ARCO CON W
        ady = inicio->getArcos();
        while ((ady != nullptr) && (ady->getInfo()->getInfo() != w)){
            ady=ady->getSig();
        }
        if (ady == nullptr) return; //SI NO EXISTE EL ARCO -> SALIR DEL METODO
        ady->setPeso(nuevo);

    }
}

template <typename Tipo>
void Grafo<Tipo>::agregarArco(Tipo v, Tipo w, float peso){
    Vertice<Tipo> *inicio = this->primero, *objetivo = nullptr, *verticeAux;
    Arco<Tipo> *ady, *nuevo;
    if (inicio != nullptr) {
        
        //ENCONTRAR VERTICE V
        while((inicio!=nullptr) && (inicio->getInfo() != v)){
            if (inicio->getInfo() == w){
                objetivo = inicio;
            }
            inicio = inicio->getSig();
        }

        if(inicio != nullptr){

            verticeAux = inicio;
            ady = inicio->getArcos();

            while ((objetivo == nullptr) && (inicio->getSig() != nullptr)){
                if(inicio->getSig()->getInfo() == w){
                    objetivo = inicio->getSig();
                }
                inicio=inicio->getSig();
            }
            if(objetivo == nullptr) return;

            //RECORRER ARCOS DE V HASTA ENCONTRAR ARCO CON W
            if (ady != nullptr){
                while (ady->getSig() != nullptr){
                    if(ady->getInfo()->getInfo() == w){
                        return;
                    }
                    ady=ady->getSig();
                }
                if(ady->getInfo()->getInfo() == w){
                    return;
                }
                nuevo = new Arco<Tipo>;
                nuevo->setInfo(objetivo);
                nuevo->setSig(nullptr);
                nuevo->setPeso(peso);
                ady->setSig(nuevo);
            }else{
                nuevo = new Arco<Tipo>;
                nuevo->setInfo(objetivo);
                nuevo->setSig(nullptr);
                nuevo->setPeso(peso);
                verticeAux->setArcos(nuevo);

            }
            this->nArcos = this-> nArcos + 1;
        }else{
            cout<< "El vertice " << v << " no existe" <<endl; 
        } 
    }
}

template <typename Tipo>
void Grafo<Tipo>::eliminarArco (Tipo v, Tipo w){
    Vertice<Tipo> *inicio = this->primero;
    Arco<Tipo> *ady, *objetivo;

    if(this->existeArco(v,w)){
        //ENCONTRAR VERTICE V
        while((inicio!=nullptr) && (inicio->getInfo() != v)){
            inicio = inicio->getSig();
        }
        
        //RECORRER ARCOS DE V HASTA ENCONTRAR ARCO CON W
        ady = inicio->getArcos();
        if(ady != nullptr){
            if(ady->getInfo()->getInfo() == w){
                inicio->setArcos(ady->getSig());
                delete ady;
                this->nArcos = this->nArcos - 1;
            }else{
                if (ady->getSig() != nullptr){
                    while (ady->getSig()->getInfo()->getInfo() != w){
                        ady=ady->getSig();
                    }
                    objetivo = ady->getSig();
                    ady->setSig(objetivo->getSig());
                    objetivo->setSig(nullptr);

                    delete objetivo;
                    this->nArcos = this->nArcos - 1;

                }
            }
        }
    }
    
}


//OPERACIONES CON VERTICES ================================================================
template <typename Tipo>
void Grafo<Tipo>::agregarVertice (Tipo v){
    Vertice<Tipo> *inicio = this->primero, *nuevo;
    if(inicio != nullptr){
        //VERIFICAR QUE NO ESTE REPETIDO
        while(inicio != nullptr){
            if(inicio->getInfo() == v) return; //Si el vertice ya se encuentra en el grafo se sale del metodo
            inicio=inicio->getSig();
        }
    }
    //INSERTAR AL INICIO
    inicio = this->primero;
    nuevo = new Vertice<Tipo>;
    nuevo->setInfo(v);
    nuevo->setSig(inicio);
    nuevo->setArcos(nullptr);
    this->setPrimero(nuevo);
    this->nVertices = this->nVertices + 1;
}
template <typename Tipo>
void Grafo<Tipo>::eliminarVertice (Tipo v){
    Vertice<Tipo> *inicio = this->primero, *objetivo = nullptr;
    list<Tipo> conexiones;
    if(inicio != nullptr){
        conexiones = this->sucesores(v);
        while(!conexiones.empty()){
            this->eliminarArco(v,conexiones.front());
            conexiones.pop_front();
        }
        conexiones = this->predecesores(v);
        while(!conexiones.empty()){
            this->eliminarArco(conexiones.front(),v);
            conexiones.pop_front();
        }
        
        if(inicio->getInfo() == v){
            objetivo = inicio;
            this->primero = objetivo->getSig();
            objetivo->setSig(nullptr);

        }else{
            //ENCONTRAR VERTICE V
            while((inicio->getSig() != nullptr) && (inicio->getSig()->getInfo() != v)){
                inicio = inicio->getSig();
            }

            objetivo = inicio->getSig();

            if(objetivo == nullptr) return; //SI NO EXISTE EL VERTICE SALE DEL METODO

            inicio->setSig(objetivo->getSig());
            objetivo->setSig(nullptr);
        }
        delete objetivo;
        this->nVertices = this->nVertices - 1;
    }
}


template<typename Tipo>
int Grafo<Tipo>::buscarMapeo(vector<Tipo> arreglo, Tipo elem, int dim){
    int i = 0;
    for(i=0;i<dim;i++){
        if(arreglo.at(i) == elem){
            return(i);
        }
    }
    return -1;
}

template<typename Tipo>
void Grafo<Tipo>::escribirGrafo(){
    Vertice<Tipo> *v = this->primero;  
    while(v != nullptr){
        cout<< v->getInfo()<<" = ";
        Arco<Tipo> *a = v->getArcos();
        while(a != nullptr){
            cout<< a->getInfo()->getInfo() << " (PESO = " << this->getPesoArco(v->getInfo(),a->getInfo()->getInfo())<<")";
            a=a->getSig();
        }
        v=v->getSig();
        cout<<endl;    
    }
}

#endif