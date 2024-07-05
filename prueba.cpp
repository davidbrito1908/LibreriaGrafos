#include <iostream>
#include <string>
#include "grafoDirigido.hpp"
#include "grafoNoDirigido.hpp"
#include <list>
using namespace std;

int main(){

    /*GrafoDirigido<int> g;
    //g.agregarVertice(1);
    g.construir();
    //g.setPrimero(1);
    //float f = g.getPesoArco(8,8);
    g.modificarPesoArco(2,4, 5);
    g.eliminarVertice(2);
    g.agregarVertice(1);
    g.agregarVertice(2);
    g.agregarVertice(2);
    g.agregarVertice(2);
    g.agregarVertice(3);
    g.agregarVertice(4);
    //g.agregarArco(2,3);
    //g.agregarArco(2,4);
    g.agregarArco(3,4);
    g.agregarArco(2,4, -8.6);
    g.agregarArco(2,1);
    g.agregarArco(3,1);
    g.agregarArco(4,1, 7.3);
    g.agregarArco(4,2, 5);
    g.agregarArco(4,76);
    //g.eliminarArco(4,1); 
    //g.eliminarVertice(7);    
    g.modificarPesoArco(56,4,49);
    //g.eliminarArco(8,5);     
    /*if (g.existeArco(4,2)){ 
        cout<<"SI HAY";
    }*/

    /*Vertice<int> *v = g.getPrimero();  
    while(v != nullptr){
        cout<< v->getInfo()<<" = ";
        Arco<int> *a = v->getArcos();
        while(a != nullptr){
            cout<< a->getInfo()->getInfo() << "(PESO = " << g.getPesoArco(v->getInfo(),a->getInfo()->getInfo())<<")";
            a=a->getSig();
        }
        v=v->getSig();
        cout<<endl;    
    }

    cout<<endl<<g.getNVertices() << "   "<<g.getNArcos()<<endl;
    list<int> L = g.sucesores(1);
    if (L.empty()){
        cout<<"No  hay";
    }else{
        while(!L.empty()){
            cout<<L.front()<<", ";
            L.pop_front();
        }
    }*/


    GrafoNoDirigido<string> N;
    N.agregarVertice("Uno");
    N.agregarVertice("Dos");
    N.agregarVertice("Tres");
    N.agregarArcoND("Uno", "Dos", 5);
    N.agregarArcoND("Tres", "Dos", 5);

    N.modificarPesoArcoND("Dos", "Uno", 16);
    N.eliminarArcoND("Dos", "Uno");
    
    list<string> L = N.vecinos("Dos");
    if (L.empty()){
        cout<<"No  hay";
    }else{
        while(!L.empty()){
            cout<<L.front()<<", ";
            L.pop_front();
        }
    }

    Vertice<string> *v = N.getPrimero();  
    while(v != nullptr){
        cout<< v->getInfo()<<" = ";
        Arco<string> *a = v->getArcos();
        while(a != nullptr){
            cout<< a->getInfo()->getInfo() << "(PESO = " << N.getPesoArco(v->getInfo(),a->getInfo()->getInfo())<<")";
            a=a->getSig();
        }
        v=v->getSig();
        cout<<endl;    
    }
    return 0;
}