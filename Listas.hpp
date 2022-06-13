#ifndef LISTAS_HPP
#define LISTAS_HPP

#include "Grafo.hpp"

class Vertice;
class Conexion;

using namespace std;

class NodoLista
{	
	private:
		Vertice *dato;
    	NodoLista * siguiente;
    public:
    	NodoLista (Vertice * dato) {
    		this->dato = dato;
        	this->siguiente = NULL;
    	}
    	NodoLista (Vertice * dato, NodoLista * siguiente) {
    		this->dato = dato;
        	this->siguiente = siguiente;
    	}
        Vertice* getDato() {return dato;}
    	NodoLista* getSiguiente () {return siguiente;}
    
	friend class Grafo;
	friend class Lista;
};

typedef NodoLista * pNodList;

class Lista 
{	
	private:
		pNodList primero;
   
    public:
        Lista ();
        ~Lista ();
        pNodList getPrimero () {return primero;}
        bool listaVacia   () {return primero == NULL;}
        void insertFinal  (Vertice * dato);
        
        Vertice* buscar (long long int codigo);
        bool estaValor  (long long int codigo);
        
        string toStringVert ();
        
        int size ();
        Vertice* getVert (int indx);
	friend class Grafo;
};

/*-------------------------------------*/
/*-------------------------------------*/

class NodoListaCX
{	
	private:
		long long int codVertice;
		Conexion * dato;
    	NodoListaCX * siguiente;
    	int disTotal;
    
    public:
    	NodoListaCX (long long int codVertice, Conexion * dato, int total) {
    		this->codVertice = codVertice;
			this->dato = dato;
        	this->siguiente = NULL;
        	this->disTotal = total;
    	}
    	NodoListaCX (long long int codVertice, Conexion * dato, NodoListaCX * siguiente) {
    		this->codVertice = codVertice;
			this->dato = dato;
        	this->siguiente = siguiente;
    	}
    	long long int getCodV () {return codVertice;}
        Conexion* getDato() {return dato;}
    	NodoListaCX* getSiguiente () {return siguiente;}
    	int getTotal () { return this->disTotal; }
    	
    
	friend class Grafo;
	friend class ListaCX;
};

typedef NodoListaCX * pNodListCX;

class ListaCX
{	
	private:
		pNodListCX primero;
   
    public:
        ListaCX ();
        ~ListaCX ();
        pNodListCX getPrimero () {return primero;}
        bool listaVacia   () {return primero == NULL;}
        void insertFinal  (long long int codVertice, Conexion * dato, int total);
        
        Conexion* buscar (long long int inicio, long long int final);
        pNodListCX buscar2 (long long int inicio, long long int final);
        void eliminar (long long int inicio, long long int final);
        
        int size ();
        Conexion* get (int indx);
        
        
        
        int getDisMinima_Dis ();
        long long int getCondVert_Minimo ();
        Conexion * getDisMinima_Nodo ();
        
        int getDisTotal_Dis (ListaCX & lista);
        pNodListCX getDisTotal_Nodo (ListaCX & lista);
        
        string toStringConx ();
        
		Conexion* getConxMinimo ();
		long long int getConxV_Minimo_Avansada (long long int codigo, int extra);
		Conexion* getConxMinimo_Avansada (long long int codigo, int extra);
        
        void agregarConexs (Vertice * vertice);
        
	friend class Grafo;
};

string intToStr(int numero);



#endif
