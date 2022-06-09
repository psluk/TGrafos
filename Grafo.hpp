#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <string>
#include "Reportes.hpp"

// NODO DE VÉRTICE

class Conexion;

class Vertice
{
private:
	long long int codigoCarrera;
	Conexion *sublista;
	Vertice *siguiente;
	bool visitado;

public:
	// CONSTRUCTOR Y DESTRUCTOR
	Vertice(long long int codigoCarrera);
	~Vertice();

	// LISTA DE ADYACENTES
	void agregarAdyacente(Vertice *adyacente, int peso);
	bool esAdyacente(Vertice *adyacente);
	int pesoDeConexion(Vertice *adyacente); // Si es adyacente, devuelve el peso. Si no, devuelve -1
	int cantidadAdyacentes();

	friend class Grafo;
	friend class Conexion;
	friend class Arbol;
	friend class NodoArbol;
	friend class Pila;
	friend class Ruta;
};

// NODO DE CONEXIÓN

class Conexion
{
private:
	Vertice *adyacente;
	Conexion *siguiente;
	int peso;

public:
	// CONSTRUCTOR Y DESTRUCTOR
	Conexion(Vertice *adyacente);			// Sin peso
	Conexion(Vertice *adyacente, int peso); // Con peso
	~Conexion();

	friend class Vertice;
	friend class Grafo;
};

// LISTA PRINCIPAL

class Grafo
{
private:
	Vertice *primero;

	// COMPROBACIONES
	Vertice *devolverNodo(long long int codigoCarrera);

	// DESPUÉS DE IMPRIMIR O HACER PUNTOS DE ARTICULACIÓN
	void resetearVisitado();

public:
	// CONSTRUCTOR Y DESTRUCTOR
	Grafo();
	~Grafo();

	// AGREGAR NODO
	void agregarNodo(long long int codigoCarrera);

	// ADYACENCIAS
	// Dirección: 1 → 2
	bool agregarAdyacente(long long int codigoCarrera1, long long int codigoCarrera2);			 
	bool agregarAdyacente(long long int codigoCarrera1, long long int codigoCarrera2, int peso);
	// En ambas direcciones
	void agregarBidireccional(long long int codigoCarrera1, long long int codigoCarrera2);
	void agregarBidireccional(long long int codigoCarrera1, long long int codigoCarrera2, int peso);

	// IMPRIMIR
	void imprimir();							// Imprime nodos y adyacentes
	void imprimir(long long int codigoCarrera); // codigoCarrera = donde empieza

	// PUNTOS DE ARTICULACIÓN
	void puntosDeArticulacion();

	// COMPROBACIONES
	bool existe(long long int codigoCarrera);

	// COMPROBACIÓN DE ADYACENCIA (en cualquier dirección: 1 → 2, 2 → 1)
	bool adyacentes(long long int codigoCarrera1, long long int codigoCarrera2);
	bool adyacentes(Vertice *nodo1, Vertice *nodo2);

	// KRUSKAL
	void kruskal();
};

#endif