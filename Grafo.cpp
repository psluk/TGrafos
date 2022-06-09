#include <iostream>
#include "Grafo.hpp"
#include "Pila.hpp"
#include "Arbol.hpp"
#include "Ruta.hpp"

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

// KRUSKAL
void Grafo::kruskal()
{
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