#ifndef NODOVERTICE_H_
#define NODOVERTICE_H_
//#include "nodoArco.hpp"


template <typename tipo>
class Arco;
template <typename tipo>
class Vertice{
    private:
        tipo info;
        Vertice<tipo> *sig;
        Arco<tipo> *listaAdy;
        int grado;
    public:
        tipo getInfo(){
            return this->info;
        }
        Vertice<tipo> * getSig(){
            return this->sig;
        }
        Arco<tipo> * getArcos(){
            return this->listaAdy;
        }
        int getGrado(){
            return this->grado;
        }
        void setInfo(tipo info){
            this->info = info;
        }
        void setSig(Vertice<tipo> *apuntador){
            this->sig = apuntador;
        }
        void setArcos(Arco<tipo> *adyacente){
            this->listaAdy = adyacente;
        }
        void setGrado(int nuevo){
            this->grado = nuevo;
        }
};
#endif