#include <sstream>
#include "Listas.hpp"



string intToStr(int numero)
{
    ostringstream buff;
    buff<<numero;
    return buff.str();
}

Lista::Lista()
{
	primero = NULL;
}

Lista::~Lista () 
{
	pNodList aux;
    while (primero) {
    	aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
}

void Lista::insertFinal  (Vertice * dato)
{
	if (listaVacia ()) {
		primero = new NodoLista (dato);
        return;
    } else {
    	pNodList aux = primero;
		while(aux->siguiente != NULL) aux= aux->siguiente;
		aux->siguiente = new NodoLista (dato);
    }    
}

Vertice* Lista::buscar(long long int codigo) 
{
	if (listaVacia()) return NULL;
	pNodList aux = primero;
	while (aux) {
		if (aux->getDato()->getCodigo() == codigo) return aux->getDato();
		aux = aux->getSiguiente();
	} return NULL;
}

bool Lista::estaValor (long long int codigo)
{
	return this->buscar(codigo) != NULL;
}

int Lista::size ()
{
	if (listaVacia()) return 0;
	int cant = 0; pNodList aux = primero;
	while (aux) {
		cant++;
		aux = aux->getSiguiente();
	} return cant;
	
}

Vertice* Lista::getVert (int indx)
{
	if (listaVacia()) return NULL;
	int cant = 1; pNodList aux = primero;
	while (aux) {
		if (indx == cant) return aux->getDato ();
		cant++; aux = aux->getSiguiente();
	} return NULL;
}

string Lista::toStringVert ()
{
	if (listaVacia()) return "";
	string str = ""; pNodList aux = primero;
	while (aux) {
		str = str + intToStr(aux->getDato()->getCodigo())+" - ";
		aux = aux->getSiguiente();
	} return str;
}

/*-------------------------------------*/
/*-------------------------------------*/

ListaCX::ListaCX()
{
	primero = NULL;
}

ListaCX::~ListaCX () 
{
	pNodListCX aux;
    while (primero) {
    	aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
}

void ListaCX::insertFinal  (long long int codVertice, Conexion * dato, int total)
{
	if (listaVacia ()) {
		primero = new NodoListaCX (codVertice, dato, total);
        return;
    } else {
    	pNodListCX aux = primero;
		while(aux->siguiente != NULL) aux= aux->siguiente;
		aux->siguiente = new NodoListaCX (codVertice, dato, total);
    }    
}

Conexion* ListaCX::buscar(long long int inicio, long long int final) 
{
	if (listaVacia()) return NULL;
	pNodListCX aux = primero;
	while (aux) {
		if (aux->getCodV() == inicio && aux->getDato()->getVertice()->getCodigo() == final) return aux->getDato();
		aux = aux->getSiguiente();
	} return NULL;
}

pNodListCX ListaCX::buscar2(long long int inicio, long long int final) 
{
	if (listaVacia()) return NULL;
	pNodListCX aux = primero; 
	while (aux) {
		if (aux->getCodV() == inicio && aux->getDato()->getVertice()->getCodigo() == final) return aux;
		aux = aux->getSiguiente();
	} return NULL;
}

/***/
void ListaCX::eliminar(long long int inicio, long long int final) 
{
	if (listaVacia()) return;
	pNodListCX pasAux = NULL; pNodListCX aux = primero; pNodListCX temp;
	
	if (primero->getCodV() == inicio && primero->getDato()->getVertice()->getCodigo() == final){
		temp = primero; primero = primero->siguiente; delete temp; return;
	}
	
	while (aux) {
		if (aux->getCodV() == inicio && aux->getDato()->getVertice()->getCodigo() == final) break;
		pasAux = aux; aux = aux->getSiguiente();
	}
	
	if (aux != NULL && pasAux != NULL) {
		if (aux->getCodV() == inicio && aux->getDato()->getVertice()->getCodigo() == final) {
			pasAux->siguiente = aux->getSiguiente(); delete aux;
		}
	} return;
}

int ListaCX::size ()
{
	if (listaVacia()) return 0;
	int cant = 0; pNodListCX aux = primero;
	while (aux) {
		cant++;
		aux = aux->getSiguiente();
	} return cant;
	
}


/*--------------------------------------------*/

int ListaCX::getDisMinima_Dis() 
{
	if (listaVacia()) return 0;
	pNodListCX aux = primero; int disMinima = aux->getDato()->getPeso();
	while (aux) {
		if (aux->getDato()->getPeso() < disMinima) {disMinima = aux->getDato()->getPeso();}
		aux = aux->getSiguiente();
	} return disMinima;
}

long long int ListaCX::getCondVert_Minimo()
{
	if (listaVacia()) return 0;
	pNodListCX aux = primero; int disMinima = aux->getDato()->getPeso(); long long int codVert = aux->getCodV ();
	while (aux) {
		if (aux->getDato()->getPeso() < disMinima) {disMinima = aux->getDato()->getPeso(); codVert = aux->getCodV ();}
		aux = aux->getSiguiente();
	} return codVert;
}

Conexion * ListaCX::getDisMinima_Nodo ()
{
	if (listaVacia()) return 0;
	pNodListCX aux = primero; int disMinima = aux->getDato()->getPeso(); Conexion * conex = aux->getDato();
	while (aux) {
		if (aux->getDato()->getPeso() < disMinima) {disMinima = aux->getDato()->getPeso(); conex = aux->getDato();}
		aux = aux->getSiguiente();
	} return conex;
}
        
int ListaCX::getDisTotal_Dis (ListaCX & lista) 
{
	if (listaVacia()) return 0;
	int disTotal; int extra;
	
	if ( (lista.buscar2(primero->getCodV() , primero->getDato()->getVertice()->getCodigo()) != NULL )) {
		extra = lista.buscar2(primero->getCodV() , primero->getDato()->getVertice()->getCodigo())->getTotal();
		disTotal = primero->getDato()->getPeso() + extra;
	}else{ disTotal = primero->getDato()->getPeso(); }
	
	pNodListCX aux = primero; Conexion * conex = aux->getDato();
	
	while (aux) {
		
		if  (lista.buscar2(aux->getCodV() , aux->getDato()->getVertice()->getCodigo()) != NULL ) {
			extra = lista.buscar2(aux->getCodV() , aux->getDato()->getVertice()->getCodigo()->aux->getTotal();
		    if ( (aux->getDato()->getPeso() + extra) < disTotal ) 
				disTotal = aux->getDato()->getPeso() + extra; conex = aux->getDato();
		
		} else if (aux->getDato()->getPeso() < disTotal) {
			disTotal = aux->getDato()->getPeso(); conex = aux->getDato();
		}
		aux = aux->getSiguiente();
	} return disTotal;
}

pNodListCX ListaCX::getDisTotal_Nodo (ListaCX & lista)
{
	if (listaVacia()) return 0;
	
	int disTotal; int extra;
	
	if ( (lista.buscar2(primero->getCodV() , primero->getDato()->getVertice()->getCodigo()) != NULL ))
		extra = lista.buscar2(primero->getCodV() , primero->getDato()->getVertice()->getCodigo())->getTotal();
		disTotal = primero->getDato()->getPeso() extra;
	else{ disTotal = primero->getDato()->getPeso(); }
	
	pNodListCX aux = primero; pNodListCX nodoAux = aux;
	while (aux) {
		
		if ( (lista.buscar2(aux->getCodV() , aux->getDato()->getVertice()->getCodigo()) != NULL ){
			extra = lista.buscar2(aux->getCodV() , aux->getDato()->getVertice()->getCodigo()->aux->getTotal();
			if  ( (aux->getDato()->getPeso() + extra) < disTotal )
				disTotal = aux->getDato()->getPeso() + extra; nodoAux = aux;
		
		} else if (aux->getDato()->getPeso() < disTotal) {
			disTotal = aux->getDato()->getPeso(); nodoAux = aux;
		}
		
		aux = aux->getSiguiente();
	} return nodoAux;
}

string ListaCX::toStringConx ()
{
	if (listaVacia()) return "";
	pNodListCX aux = primero; int disMinima = aux->getDato()->getPeso(); string str = "";
	while (aux) {
		//if (aux->getDato()->getPeso() < disMinima) {disMinima = aux->getDato()->getPeso(); conex = aux->getDato();}
		str = str +intToStr(aux->getDato()->getVertice()->getCodigo()) + " - ";
		aux = aux->getSiguiente();
	} return str;
}

/*
Conexion* ListaCX::get (int indx)
{
	if (listaVacia() || indx <= 0) return NULL;
	int cant = 1; pNodListCX aux = primero;
	while (aux) {
		if (indx == cant) return aux->getDato ();
		cant++; aux = aux->getSiguiente();
	} return NULL;
}

Conexion* ListaCX::getConxMinimo()
{
	if (listaVacia()) return NULL;
	int cant = 0; pNodListCX aux = primero; Conexion* auxRet = NULL;
	while (aux) {
		if (aux->dato->peso > cant) {auxRet = aux->dato; cant = aux->dato->peso}
		aux = aux->getSiguiente();
	} return auxRet;
}

Conexion* ListaCX::getConxMinimo_Avansada (long long int codigo, int extra);
{
	if (listaVacia()) return NULL;
	int cant = 0; pNodListCX aux = primero; Conexion* auxRet = NULL;
	while (aux) {
		if (aux->dato->peso < cant) {
			if (aux->dato->adyacente->codigoCarrera == codigo && (aux->dato->peso + extra) < cant){
				auxRet = aux->dato; cant = (aux->dato->peso + extra);
			} else {
				auxRet = aux->dato; cant = aux->dato->peso;
			}
		}
		aux = aux->getSiguiente();
	} return auxRet;
}

long long int ListaCX::getConxV_Minimo_Avansada (long long int codigo, int extra);
{
	if (listaVacia()) return NULL;
	int cant = 0; pNodListCX aux = primero; long long int auxRet = -1;
	while (aux) {
		if (aux->dato->peso < cant) {
			if (aux->dato->adyacente->codigoCarrera == codigo && (aux->dato->peso + extra) < cant){
				auxRet = aux->codVertice; cant = (aux->dato->peso + extra);
			} else {
				auxRet = aux->codVertice; cant = aux->dato->peso;
			}
		}
		aux = aux->getSiguiente();
	} return auxRet;
}

void ListaCX::agregarConexs (Vertice * vertice)
{
	Conexion *auxiliar = vertice->sublista;
	while (auxiliar)
	{
		insertFinal(vertice->codigoCarrera, auxiliar);
		auxiliar = auxiliar->siguiente;
	} return;
}
*/
