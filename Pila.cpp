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

	std::string reporte = "\n\t[INFO]\t\tSe inserta [";
	reporte += std::to_string(nuevo->codigoCarrera);
	reporte += "] a la pila.\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	escribirPila();
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

		std::string reporte = "\n\t[INFO]\t\tSe saca [";
		reporte += std::to_string(temporal->codigoCarrera);
		reporte += "] de la pila.\n";
		ReporteEnArchivo::archivoDeReportes->escribir(reporte);
		escribirPila();

		return temporal;
	}
	return NULL;
}

// COMPROBACIONES

bool Pila::vacia()
{
	return !frente;
}

// REPORTE EN ARCHIVO

void Pila::escribirPila()
{
	std::string reporte = "\t\t\t\tPila: ";
	if (vacia())
	{
		reporte += "* sin elementos *";
	}
	else
	{
		NodoPila *auxiliar = frente;
		while (auxiliar)
		{
			reporte += "[";
			reporte += std::to_string(auxiliar->nodo->codigoCarrera);
			reporte += "]";
			if (auxiliar->siguiente)
			{
				reporte += " -> ";
			}
			auxiliar = auxiliar->siguiente;
		}
	}
	reporte += "\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
}