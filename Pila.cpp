#include "Pila.hpp"

// -------------------- NODO DE PILA --------------------

// CONSTRUCTOR

NodoPila::NodoPila(Vertice *nodo, NodoPila *siguiente)
{
	this->nodo = nodo;
	this->siguiente = siguiente;
}

// -------------------- PILA --------------------

// CONSTRUCTOR

Pila::Pila()
{
	frente = NULL;	
}

// AGREGAR

void Pila::push(Vertice *nuevo)
{
	frente = new NodoPila(nuevo, frente);
}

// QUITAR

Vertice *Pila::pop()
{
	if (frente)
	{
		Vertice *temporal = frente->nodo;
		NodoPila *temporalPila = frente;
		frente = frente->siguiente;
		delete temporalPila;
		return temporal;
	}
	return NULL;
}

// COMPROBACIONES

bool Pila::vacia()
{
	return !frente;
}