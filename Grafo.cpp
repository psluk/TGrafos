#include <iostream>
#include "Grafo.hpp"
#include "Pila.hpp"
#include "Arbol.hpp"
#include "Ruta.hpp"
#include "Listas.hpp"

// -------------------- VÉRTICE --------------------

// CONSTRUCTOR

Vertice::Vertice(long long int codigoCarrera)
{
	this->codigoCarrera = codigoCarrera;
	this->siguiente = NULL;
	this->sublista = NULL;
	this->visitado = false;
}

// DESTRUCTOR

Vertice::~Vertice()
{
	if (this->sublista)
	{
		delete this->sublista;
	}
	if (this->siguiente)
	{
		delete this->siguiente;
	}
}

// LISTA DE ADYACENTES

void Vertice::agregarAdyacente(Vertice *adyacente, int peso)
{
	if (this->sublista)
	{
		Conexion *auxiliar = this->sublista;
		while (auxiliar->siguiente)
		{
			if (auxiliar->adyacente == adyacente)
			{
				std::cout << "\t[ADVERTENCIA]\tEl nodo [" << adyacente->codigoCarrera << "] ya es adyacente de [" << this->codigoCarrera << "].\n";
				return;
			}
			auxiliar = auxiliar->siguiente;
		}
		auxiliar->siguiente = new Conexion(adyacente, peso);
	}
	else
	{
		this->sublista = new Conexion(adyacente, peso);
	}
}

bool Vertice::esAdyacente(Vertice *adyacente)
{
	Conexion *auxiliar = this->sublista;
	while (auxiliar)
	{
		if (auxiliar->adyacente == adyacente)
		{
			return true;
		}
		auxiliar = auxiliar->siguiente;
	}
	return false;
}

int Vertice::pesoDeConexion(Vertice *adyacente)
{
	// Si existe el adyacente, devuelve el peso de la conexión
	// Si no, devuelve -1
	Conexion *auxiliar = this->sublista;
	while (auxiliar)
	{
		if (auxiliar->adyacente == adyacente)
		{
			return auxiliar->peso;
		}
		auxiliar = auxiliar->siguiente;
	}
	return -1;
}

int Vertice::cantidadAdyacentes()
{
	Conexion *auxiliar = this->sublista;
	int cantidad = 0;
	while (auxiliar)
	{
		cantidad++;
		auxiliar = auxiliar->siguiente;
	}
	return cantidad;
}

// PRIM

Conexion *Vertice::conexionMinima()
{
	// Devuelve la conexión con el menor peso del nodo actual con uno sin visitar
	Conexion *auxiliar = sublista, *minimo = NULL;
	while (auxiliar)
	{
		if (!auxiliar->adyacente->visitado)
		{
			if (!minimo || minimo->peso > auxiliar->peso)
			{
				minimo = auxiliar;
			}
		}
		auxiliar = auxiliar->siguiente;
	}
	return minimo;
}

// -------------------- CONEXIÓN --------------------

// CONSTRUCTORES

Conexion::Conexion(Vertice *adyacente)
{
	this->adyacente = adyacente;
	this->siguiente = NULL;
	this->peso = 0;
}

Conexion::Conexion(Vertice *adyacente, int peso)
{
	this->adyacente = adyacente;
	this->siguiente = NULL;
	this->peso = peso;
}

// DESTRUCTOR

Conexion::~Conexion()
{
	if (this->siguiente)
	{
		delete this->siguiente;
	}
}

// -------------------- LISTA --------------------

// CONSTRUCTOR

Grafo::Grafo()
{
	this->primero = NULL;
}

// DESTRUCTOR

Grafo::~Grafo()
{
	delete primero;
	primero = NULL;
}

// AGREGAR NODO

void Grafo::agregarNodo(long long int codigoCarrera)
{
	if (this->primero)
	{
		Vertice *auxiliar = this->primero;
		while (auxiliar->siguiente)
		{
			if (auxiliar->codigoCarrera == codigoCarrera)
			{
				std::cout << "\t[ADVERTENCIA]\tEl nodo [" << codigoCarrera << "] ya existe y no se vuelve a insertar.\n";
				return;
			}
			auxiliar = auxiliar->siguiente;
		}
		auxiliar->siguiente = new Vertice(codigoCarrera);
	}
	else
	{
		this->primero = new Vertice(codigoCarrera);
	}
}

bool Grafo::agregarAdyacente(long long int codigoCarrera1, long long int codigoCarrera2)
{
	return agregarAdyacente(codigoCarrera1, codigoCarrera2, 0);
}

bool Grafo::agregarAdyacente(long long int codigoCarrera1, long long int codigoCarrera2, int peso)
{
	Vertice *nodo1 = devolverNodo(codigoCarrera1);
	if (nodo1)
	{
		Vertice *nodo2 = devolverNodo(codigoCarrera2);
		if (nodo2)
		{
			nodo1->agregarAdyacente(nodo2, peso);
			return true;
		}
	}
	std::cout << "\t[ERROR]\t\t No se puede establecer la adyacencia entre [" << codigoCarrera1 << "] y [" << codigoCarrera2 << "] ya que no existe uno de los nodos.\n";
	return false;
}

void Grafo::agregarBidireccional(long long int codigoCarrera1, long long int codigoCarrera2)
{
	agregarBidireccional(codigoCarrera1, codigoCarrera2, 0);
}

void Grafo::agregarBidireccional(long long int codigoCarrera1, long long int codigoCarrera2, int peso)
{
	if (agregarAdyacente(codigoCarrera1, codigoCarrera2, peso))
	{
		// Si se pudo agregar la primera adyacencia (de 1 a 2), se agrega la misma
		// en dirección contraria
		agregarAdyacente(codigoCarrera2, codigoCarrera1, peso);
	}
}

// COMPROBACIONES

Vertice *Grafo::devolverNodo(long long int codigoCarrera)
{
	Vertice *auxiliar = primero;
	while (auxiliar)
	{
		if (auxiliar->codigoCarrera == codigoCarrera)
		{
			break;
		}
		auxiliar = auxiliar->siguiente;
	}
	return auxiliar;
}

bool Grafo::existe(long long int codigoCarrera)
{
	// NULL = 0 = false
	// Cualquier otro puntero = true
	return devolverNodo(codigoCarrera);
}

// IMPRIMIR

void Grafo::imprimir()
{
	Vertice *auxiliar = primero;
	Conexion *auxiliar2;
	int contador1 = 0, contador2;
	while (auxiliar)
	{
		contador2 = 0;
		auxiliar2 = auxiliar->sublista;
		if (contador1)
		{
			std::cout << "\n";
		}
		contador1++;
		std::cout << "\t" << contador1 << ".\t[" << auxiliar->codigoCarrera << "]\n";
		while (auxiliar2)
		{
			contador2++;
			std::cout << "\t\t" << contador2 << ".\t[" << auxiliar2->adyacente->codigoCarrera
					  << "]\t(peso: " << auxiliar2->peso << ")\n";
			auxiliar2 = auxiliar2->siguiente;
		}
		if (!contador2)
		{
			std::cout << "\t\t[INFO]\tNo hay adyacentes.\n";
		}
		auxiliar = auxiliar->siguiente;
	}
	if (!contador1)
	{
		std::cout << "\t[INFO]\tNo hay nodos.\n";
	}
}

void Grafo::imprimir(long long int codigoCarrera)
{
	std::string reporte = "\n-------------------- RECORRIDO EN PROFUNDIDAD --------------------\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	reporte = "";

	Vertice *auxiliar = devolverNodo(codigoCarrera);
	if (auxiliar)
	{
		reporte = "\n\t[INFO]\t\tRecorrido en profundidad:\n\t\t\t\t";
		std::cout << "\n\t[INFO]\t\tRecorrido en profundidad:\n\t\t\t";
		Conexion *adyacente;
		Pila pila;
		pila.push(auxiliar);
		auxiliar->visitado = true;
		while (!pila.vacia())
		{
			auxiliar = pila.pop();
			std::cout << "[" << auxiliar->codigoCarrera << "]";
			reporte += "[";
			reporte += std::to_string(auxiliar->codigoCarrera);
			reporte += "]";

			adyacente = auxiliar->sublista;
			while (adyacente)
			{
				if (!adyacente->adyacente->visitado)
				{
					pila.push(adyacente->adyacente);
					adyacente->adyacente->visitado = true;
				}
				adyacente = adyacente->siguiente;
			}

			if (!pila.vacia())
			{
				// Añade la flecha si aún quedan elementos
				// después del actual
				std::cout << " -> ";
				reporte += " -> ";
			}
		}
		std::cout << "\n";
		reporte += "\n";
		ReporteEnArchivo::archivoDeReportes->escribir(reporte);
		resetearVisitado();
	}
	else
	{
		std::cout << "\n\t[ERROR]\t\tEl nodo [" << codigoCarrera << "] no existe.\n";

		reporte = "\n\t[ERROR]\t\tEl nodo [";
		reporte += std::to_string(codigoCarrera);
		reporte += "] no existe.\n";
		ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	}
}

// PUNTOS DE ARTICULACIÓN

void Grafo::puntosDeArticulacion()
{
	std::string reporte = "\n-------------------- PUNTOS DE ARTICULACION --------------------\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	reporte = "";

	Vertice *auxiliar = primero;

	if (auxiliar)
	{
		reporte = "\n\t[INFO]\t\tPuntos de articulacion:\n\t\t\t\t";
		std::cout << "\n\t[INFO]\t\tPuntos de articulaci" << (char)162 << "n:\n\t\t\t";

		Conexion *adyacente;
		Pila pila;
		Arbol arbol(this);
		pila.push(auxiliar);
		auxiliar->visitado = true;
		while (!pila.vacia())
		{
			auxiliar = pila.pop();
			arbol.agregar(auxiliar);
			adyacente = auxiliar->sublista;
			while (adyacente)
			{
				arbol.agregarRetorno(auxiliar, adyacente->adyacente);
				if (!adyacente->adyacente->visitado)
				{
					pila.push(adyacente->adyacente);
					adyacente->adyacente->visitado = true;
				}
				adyacente = adyacente->siguiente;
			}
		}
		resetearVisitado();

		arbol.asignarNumeros();
		arbol.preorden();
		std::string retorno = arbol.puntosDeArticulacion();
		if (retorno == "")
		{
			std::cout << "No hay.";
			reporte += "No hay.";
		}
		else
		{
			std::cout << retorno;
			reporte += retorno;
		}
		std::cout << "\n";

		reporte += "\n";
		ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	}
	return;
}

// DESPUÉS DE IMPRIMIR O HACER PUNTOS DE ARTICULACIÓN

void Grafo::resetearVisitado()
{
	Vertice *auxiliar = primero;
	while (auxiliar)
	{
		auxiliar->visitado = false;
		auxiliar = auxiliar->siguiente;
	}
}

// COMPROBACIONES

bool Grafo::adyacentes(long long int codigoCarrera1, long long int codigoCarrera2)
{
	Vertice *auxiliar1 = devolverNodo(codigoCarrera1), *auxiliar2 = devolverNodo(codigoCarrera2);
	if (!auxiliar1 || !auxiliar2)
	{
		// Si alguno de los dos no existe
		return false;
	}
	return adyacentes(auxiliar1, auxiliar2);
}

bool Grafo::adyacentes(Vertice *nodo1, Vertice *nodo2)
{
	if (!(nodo1 && nodo2))
	{
		// Si alguno de los dos no existe
		return false;
	}
	return nodo1->esAdyacente(nodo2) || nodo2->esAdyacente(nodo1);
}

// ÁRBOL DE EXPANSIÓN MÍNIMA

// KRUSKAL

void Grafo::kruskal()
{
	ReporteEnArchivo::archivoDeReportes->escribir("\n-------------------- KRUSKAL --------------------\n");
	Ruta conexiones, aem;
	// conexiones = lista con todas las conexiones
	// aem = lista con las conexiones del árbol de expansión mínima

	Vertice *nodo = primero;
	Conexion *auxiliar;

	// Agrega todas las conexiones a la lista correspondiente
	while (nodo)
	{
		auxiliar = nodo->sublista;
		while (auxiliar)
		{
			conexiones.insertarOrdenado(nodo, auxiliar->adyacente, auxiliar->peso);
			auxiliar = auxiliar->siguiente;
		}
		nodo = nodo->siguiente;
	}

	conexiones.imprimir("Todas las conexiones", false);

	// Ahora, recorre la lista de primero (menor peso) a fin (mayor peso)
	NodoRuta *conexion = conexiones.primero;

	while (conexion)
	{
		if (!conexion->origen->visitado || !conexion->llegada->visitado)
		{
			// Si alguno no ha sido visitado (agregado al AEM) aún,
			// no se va a armar ningún ciclo, así que no hace falta verificarlo
			aem.insertarFinal(conexion->origen, conexion->llegada, conexion->peso);
			conexion->origen->visitado = true;
			conexion->llegada->visitado = true;
		}
		else
		{
			// Si ya están agregados los dos, hay que verificar que no haya
			// alguna ruta posible entre ambos
			if (!aem.existeRuta(conexion->origen, conexion->llegada))
			{
				// Se inserta solo si no hay alguna ruta posible entre ambos nodos
				// (en ese caso, se cerraría un ciclo al agregar esta conexión)
				aem.insertarFinal(conexion->origen, conexion->llegada, conexion->peso);
			}
		}
		conexion = conexion->siguiente;
	}

	aem.imprimir("AEM", true);
	resetearVisitado();
}

// PRIM

void Grafo::prim(long long int codigoCarrera)
{
	std::string reporte = "\n-------------------- PRIM --------------------\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	reporte = "";

	Vertice *auxiliar = devolverNodo(codigoCarrera);
	if (auxiliar && auxiliar->sublista)
	{
		Vertice *origen;
		Conexion *adyacente = auxiliar->conexionMinima(), *minimo, *actual;
		Ruta aem;
		NodoRuta *conexion;
		aem.insertarFinal(auxiliar, adyacente->adyacente, adyacente->peso); // Agrega la primera conexión
		adyacente->adyacente->visitado = true;
		while (true)
		{
			origen = NULL;
			minimo = NULL;			// Siguiente conexión de menor peso
			actual = NULL;			// Temporal
			conexion = aem.primero; // Para recorrer los nodos ya conectados
			while (conexion)
			{
				actual = conexion->origen->conexionMinima();
				if (actual && (!minimo || minimo->peso > actual->peso))
				{
					origen = conexion->origen;
					minimo = actual;
				}
				actual = conexion->llegada->conexionMinima();
				if (actual && (!minimo || minimo->peso > actual->peso))
				{
					origen = conexion->llegada;
					minimo = actual;
				}
				conexion = conexion->siguiente;
			}
			if (!minimo)
			{
				// Ya no hay nodos por agregar
				break;
			}
			aem.insertarFinal(origen, minimo->adyacente, minimo->peso); // Conecta dos nodos
			minimo->adyacente->visitado = true; // Para que no se encicle
		}

		aem.imprimir("AEM", true);
		resetearVisitado();
	}
	else
	{
		std::cout << "\n\t[ERROR]\t\tEl nodo [" << codigoCarrera << "] no existe o no tiene adyacentes.\n";

		reporte = "\n\t[ERROR]\t\tEl nodo [";
		reporte += std::to_string(codigoCarrera);
		reporte += "] no existe o no tiene adyacentes.\n";
		ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	}
}


void Grafo::setVisibilidad (long long int codigoCarrera, bool visibilidad)
{
	Vertice *auxiliar = primero;
	while (auxiliar)
	{
		if (auxiliar->codigoCarrera == codigoCarrera) {
			auxiliar->visitado = visibilidad;
		}
		auxiliar = auxiliar->siguiente;
	}
}

bool Grafo::todosVisitados ()
{
	Vertice *auxiliar = primero;
	while (auxiliar)
	{
		if (auxiliar->visitado == false) return false;
		auxiliar = auxiliar->siguiente;
	} return true;
}

bool Grafo::estaVisitado (long long int codigo)
{
	Vertice *auxiliar = primero;
	while (auxiliar)
	{
		if (auxiliar->codigoCarrera == codigo && auxiliar->visitado) return true;
		auxiliar = auxiliar->siguiente;
	} return false;
}

void Grafo::aux_dijkstra_addConxs (Vertice * vertice, ListaCX & list, int total)
{
	Conexion *auxiliar = vertice->sublista;
	while (auxiliar)
	{
		if (!estaVisitado(auxiliar->adyacente->codigoCarrera) && list.buscar (vertice->getCodigo(), auxiliar->getVertice()->getCodigo()) == NULL ) { 
			list.insertFinal (vertice->getCodigo(), auxiliar, total);
		}
		auxiliar = auxiliar->siguiente;
	} return;
}

void Grafo::dijkstra (long long int inicio, long long int final)
{
	if (this->primero == NULL) {std::cout<<"Grafo vacio.\n"; return;}
	if (devolverNodo(inicio) == NULL) {std::cout<<"No se ha encontrado el nodo de partida.\n"; return;}
	if (devolverNodo(final) == NULL) {std::cout<<"No se ha encontrado el nodo de llegada.\n"; return;}
	
	Lista list; list.insertFinal (devolverNodo(inicio)); setVisibilidad (devolverNodo(inicio)->codigoCarrera, true);
	ListaCX listCX; ListaCX listCX_2; int i = 1;
	
	/*Vertice * vertcAux; Conexion* conexAux;
	int distTotal [30]; int miniTemp = -1; int miniAux = -1; 
	bool repetir; int cantIter = 0;*/
	
	/**********************/
	bool repetir;
	int disMinima; int disTotal = 0; long long int codVertAux; int comparador;
	Conexion* nodConx_uno; pNodListCX nodConxTotal; string str;

	while (!todosVisitados()) {
		str = "";
		std::cout<<"EeeeEEEEEEeeeeEEEE-"<<i<<"\n";
		repetir = true;
		aux_dijkstra_addConxs (list.getVert(i), listCX, disTotal); //listCX.agregarConexs( list.get(i), this );
		
		while (repetir) {
			std::cout<<"\nEntra-\n";
			if (i == 1){
				std::cout<<"\nA-\n";
				//Obtener dis minima. == Obtener nodos ruta directa mas corta.
				disMinima = listCX.getDisMinima_Dis();
				codVertAux = listCX.getCondVert_Minimo();
				nodConx_uno = listCX.getDisMinima_Nodo();
				
				std::cout<<"Nodos Resueltos:\n"<<list.toStringVert()<<"\nNodos no Resueltos:\n"<<listCX.toStringConx();
				//str = "Distancia Minima: " + disMinima + "\nDistancia Total: "+ disMinima + "\nUltimas conexiones:\n";
				
				if (nodConx_uno != NULL) {
					listCX.eliminar (codVertAux, nodConx_uno->getVertice()->getCodigo());
					listCX_2.insertFinal(codVertAux, nodConx_uno, disMinima);
					
					list.insertFinal ( devolverNodo(nodConx_uno->getVertice()->getCodigo()) ); 
					setVisibilidad (devolverNodo(nodConx_uno->getVertice()->getCodigo())->codigoCarrera, true);
					
					comparador = listCX.getDisMinima_Dis();
					repetir = disMinima == comparador;
					
					//std::cout<<"Nodos Resueltos:\n"<<list.toStringVert()<<"Nodos no Resueltos:\n"<<listCX.toStringConx();
					std::cout<<"\nDistancia Minima: "<<disMinima<<"\nDistancia Total: "<<disMinima<<"\nUltimas conexiones:\n"<<listCX_2.toStringConx();
				}
				
			} else {
				std::cout<<"\nB-\n";
				//Obtener dis minima. //Obtener dis total.
				disMinima =  listCX.getDisMinima_Dis();
				disTotal = listCX.getDisTotal_Dis (listCX_2);
				nodConxTotal = listCX.getDisTotal_Nodo (listCX_2);
				std::cout<<"\nNodos Resueltos:\n"<<list.toStringVert()<<"\nNodos no Resueltos:\n"<<listCX.toStringConx();
				
				if (nodConxTotal != NULL) {
					listCX.eliminar (nodConxTotal->getCodV(), nodConxTotal->getDato()->getVertice()->getCodigo());
					listCX_2.insertFinal(nodConxTotal->getCodV(), nodConxTotal->getDato(), disTotal);
					
					list.insertFinal ( devolverNodo(nodConxTotal->getDato()->getVertice()->getCodigo()) ); 
					setVisibilidad (devolverNodo(nodConxTotal->getDato()->getVertice()->getCodigo())->codigoCarrera, true);
					
					comparador = listCX.getDisTotal_Dis (listCX_2);
					repetir = disTotal == comparador;
					
					std::cout<<"\nDistancia Minima: "<<disMinima<<"\nDistancia Total: "<<disTotal<<"\nUltimas conexiones:\n"<<listCX_2.toStringConx();
					if (i == 3) return;
				}
			}
		}
		i++;
	}
}








