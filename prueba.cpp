#include <iostream>
#include <string>
#include "grafoDirigido.hpp"
#include "grafoNoDirigido.hpp"
#include <list>
#include <vector>
using namespace std;

void leer(GrafoDirigido<string> *g){
    string v,w;
    float peso;
    while(cin>>v){
        cin>>w;
        cin>>peso;

        g->agregarVertice(v);
        g->agregarVertice(w);
        g->agregarArco(v,w, peso);
    }

} 
void leerND(GrafoNoDirigido<string> *g){ 
    string v,w;
    float peso;
    while(cin>>v){
        cin>>w;
        cin>>peso;

        g->agregarVertice(v);
        g->agregarVertice(w);
        g->agregarArcoND(v,w, peso); 
    }

}


int main(){ 
    GrafoDirigido<string> G;
    leer(&G);  
    //G.escribirGrafo();
    vector<string> map;
    GrafoDirigido<int> A, M = G.mapear(&map);
    float p;
    /*M.arbolExpandidoMinimo(&A, &p);
*/ 
    cout<<endl;
    for(int i = 0; i<M.getNVertices();i++){
        cout<<endl<<i<<" Es igual a:" << map[i]<<endl;    

    } 
    M.escribirGrafo();
    //M.eliminarArco(0,1);
    //M.escribirGrafo();
    //A.escribirGrafo(); 
    //cout<<endl<<p;

    /*if(A.esConexo()){  
        cout<<"Es conexo";
    } else{
        cout << "No es conexo";  
    } 
    if(G.esCompleto()){  
        cout<<"Es completo";
    } else{
        cout << "No es completo";  
    }*/

    /*list<list<string>> puentes = G.puentes();
    while(!puentes.empty()){   
        list<string> a = puentes.front();
        cout <<endl<< "(" << a.front() <<", "<<a.back()<<")"<<endl;
        puentes.pop_front(); 
    }*/
    list<list<string>> c = G.caminosHamiltonianos();
    cout << "M = " << M.getNArcos()<<endl;
    list<list<string>> aux;
    list<string> a;
    //while(!c.empty()){    
        //aux = c.front(); 
        aux = G.getCaminosEulerianos();
        if (aux.empty()){
            cout<<"NO HAY"; 
        }
        while(!aux.empty()){
            a = aux.front();
            while(!a.empty()){
                cout << a.front() << "->";
                a.pop_front();
            }
            cout<<endl;
            aux.pop_front();
        }
        cout<<endl;
        //c.pop_front(); 
    //} 
    G.escribirGrafo();    

    return 0;   

}
 
  

void pruebas(){  
 

       //cout<<endl<<endl<<endl;

    GrafoNoDirigido<string> N;
    N.construir();
    N.agregarVertice("Uno");
    N.agregarVertice("Dos");
    N.agregarVertice("Tres");
    N.agregarVertice("Cuatro");
    N.agregarVertice("Cinco");
    N.agregarVertice("Seis");
    N.agregarArcoND("Uno", "Dos", 1);
    N.agregarArcoND("Uno", "Tres", 2);
    N.agregarArcoND("Tres", "Cuatro", 1);
    N.agregarArcoND("Tres", "Cinco", 4);  
    N.agregarArcoND("Cuatro", "Cinco", 2);  
    N.agregarArcoND("Dos", "Seis", 3);  
    N.agregarArcoND("Dos", "Tres", 0);  
    N.agregarArcoND("Cinco", "Seis", 2);  
    N.agregarArcoND("Cuatro", "Seis", 1); 
    N.agregarArcoND("Uno", "Cuatro", 6);   
    //N.modificarPesoArcoND("Dos", "Uno", 16);
    //N.eliminarArcoND("Dos", "Uno");
    vector<string> mapeo; 
    GrafoNoDirigido<int> M = N.mapear(&mapeo);
    //int i;
    
    /*for(i=0;i<M.getNVertices(); i++){
        //cout<<M.getNVertices()<<"  "<<mapeo.at(i)<<endl;
        cout<<"Posicion " << i << " corresponde a: " << mapeo.at(i)<<endl;
    }
    cout<<endl; */
       
   
    N.escribirGrafo(); 
    M.escribirGrafo();  
    //N.NComponentes();  
    /*int c = M.NComponentes();   
    cout << endl      << c << " Componentes"<<endl;*/
    /*list<string> L = N.vecinos("Dos");
    if (L.empty()){
        cout<<"No  hay";
    }else{
        while(!L.empty()){
            cout<<L.front()<<", ";
            L.pop_front();
        } 
    }*/       
    list<int>A;
    list<int>B;


    //A.push_front(1);
    //B.push_front(2);
    list<int> R;   
    R=M.caminoDijkstra(4,0);   
    while(!R.empty()){
        cout<<mapeo[R.front()]<<" -> ";
        R.pop_front(); 
    } 
    cout<<endl;

    list<string> J = N.caminoMenor("Uno", "Seis"); 
    while(!J.empty()){
        if(J.size() == 1){
            cout << J.front();
        }else{
            cout << J.front() << "->";
        }
        J.pop_front();
    }

    cout << endl<<endl;
    GrafoDirigido<string> D;
    D.construir();
    D.agregarVertice("A");
        D.agregarVertice("B");
        D.agregarVertice("C");
        D.agregarVertice("D");
        D.agregarVertice("E");
    D.agregarArco("A", "B", 4);
    D.agregarArco("C", "B", 2);
    D.agregarArco("A", "C", 1);
    D.agregarArco("B", "D", 1);
    D.agregarArco("A", "D", 5);
    D.agregarArco("D", "E", 1);
    D.agregarArco("A", "E", 7);
    D.agregarVertice("G");  
    D.agregarArco("B", "G",0);
    D.agregarArco("G", "D",1);
    list<string> K = D.caminoMenor("A", "E"); 
    while(!K.empty()){
        if(K.size() == 1){
            cout << K.front();
        }else{
            cout << K.front() << "->";
        }
        K.pop_front();
    }
 













    
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
    //g.agregarArco(4,3);
    //g.agregarArco(1,2);
    g.agregarArco(2,3);
    g.eliminarArco(3,4); 
    //g.eliminarVertice(7);    
    g.modificarPesoArco(56,4,49);
    //g.eliminarArco(8,5);     
    if (g.esSumidero(4)){        
        cout<<"Es sumidero";
    }
    vector<int> map;
    GrafoDirigido<int> o = g.mapear(&map);
    int cfc = o.NComponentesFConexas();
  
    cout<<endl<<cfc<< " componentes fuertemente conexas" <<endl;
    //Vertice<int> *v = g.getPrimero();  
 
    g.escribirGrafo();

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
}