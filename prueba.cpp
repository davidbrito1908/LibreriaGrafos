#include <iostream>
#include <string>
#include "grafoDirigido.hpp"
#include "grafoNoDirigido.hpp"
#include <list>
#include <vector>
#include <sstream>
#include<algorithm>
using namespace std;

void leer2(GrafoNoDirigido<string> * g, list<string> *bloqueados){
    string bloqueo, info,d, v, w;
    float peso;

    getline(cin, bloqueo);
    stringstream data(bloqueo);
    getline(data, info, '[');
    getline(data, info, ']'); //La cadena resultante tiene todos los datos entre los corchetes 
    stringstream a(info);

    while(getline(a, d, ',')){ //Separar dato "d" mediante las comas
        d.erase(remove_if(d.begin(), d.end(), ::isspace),d.end()); //eliminar espacios sobrantes
        bloqueados->push_back(d); //Añadir a la lista
    }

    while(cin>>v){
        cin>>w;
        cin>>peso; 
        g->agregarVertice(v);
        g->agregarVertice(w);
        g->agregarArco(v,w, peso);
    }
}
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
    GrafoNoDirigido<string> G, K;
    G.construir();
    list<string> L;
    leer2(&G, &L);  
    /*while(!L.empty()){ 
        cout<<L.front();
        L.pop_front();
    }*/
    //K.copiar(&G);
    G.escribirGrafo();
    /*list<string> B = G.puntosArticulacion();
    while(!B.empty()){
        cout << B.front() << " -"; 
        B.pop_front();
    }*/
    cout<<endl;
    //K.escribirGrafo();
    vector<string> map;
    GrafoNoDirigido<int> A, M = G.mapear(&map);
    //float p;
    //M.arbolExpandidoMinimo(&A, &p);

    //GrafoNoDirigido<string> W = G.convertirEnNoDirigido();
    cout<<endl;           
    //W.escribirGrafo();
    //return 0;
    cout<<endl;
    /*for(int i = 0; i<M.getNVertices();i++){ 
        cout<<endl<<i<<" Es igual a:" << map[i]<<endl;    
   
    }    */   
    //M.escribirGrafo();
    //M.eliminarArco(0,1);
    //M.escribirGrafo();
    //A.escribirGrafo();  
    //cout<<endl<<p;
    //L.push_back("B");
    list<string> C ;//= G.caminoMenor("luis", "jeison");  
    float p;   
    list<string> D = G.caminoMenorConBloqueo("A", "E", L, &p);                         
    /*while(!C.empty()){     
        if(C.size() == 1){
            cout<<C.front();
        }else{  
            cout<<C.front()<<"->";   
        }  
        C.pop_front(); 
    }*/
    cout<<"EL PESO ES: "<<p<<endl;
    while(!D.empty()){    
        if(D.size() == 1){
            cout<<D.front();
        }else{ 
            cout<<D.front()<<"->";
        }
        D.pop_front();
    }  
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
    //list<list<string>> c = G.ciclosHamiltonianos();
    //cout << "M = " << M.getNArcos()<<endl;
    list<list<string>> aux;
    list<string> a;
    aux = G.getCaminosEulerianos();
    /*while(!c.empty()){    
        aux = c.front(); 
        while(!aux.empty()){
            cout << aux.front() << "->"; 
            aux.pop_front();
        }
        cout<<endl;
        c.pop_front();       
    }
    cout<<"MINIMO"<<endl;
    aux = G.cicloHamiltonianoMinimo();
    while(!aux.empty()){
        cout << aux.front() << "->"; 
        aux.pop_front();
    }*/
    cout<<endl;

    //G.escribirGrafo();       


    //list<string> U = G.listaDFS("A");
    vector<string> P = {"Ba", "Da", "Aaa", "Ea", "Ca", "Wa"};  
    vector<string> I = ordenar(P, P.size());
    int i;
    /*while(!U.empty()){
        cout<< U.front()<<" ";
        U.pop_front(); 
    }*/
    cout<<endl;
    for(i =0; i<P.size();i++){ 
        cout<< I.at(i)<<" "; 
    }   
    cout<<endl;
    if(G.esBipartito()){ 
        cout << "SI ES ";
    }else{ 
        cout << "NO ES";
    }
    cout<<endl;
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