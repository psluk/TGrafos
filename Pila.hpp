#ifndef PILA_HPP
#define PILA_HPP

#include "Lista.hpp"

class Vertice;

// -------------------- NODO DE PILA --------------------

class NodoPila
{
private:
	Vertice *nodo;
	NodoPila *siguiente;

public:
	// CONSTRUCTOR
	NodoPila(Vertice *nodo, NodoPila *siguiente);

	friend class Pila;
};

// -------------------- PILA --------------------

class Pila
{
private:
	NodoPila *frente;
public:
	// CONSTRUCTOR
	Pila();

	// AGREGAR
	void push(Vertice *nuevo);

	// QUITAR
	Vertice *pop();

	// COMPROBACIONES
	bool vacia();
};

#endif