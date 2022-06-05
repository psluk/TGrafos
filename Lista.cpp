#include <iostream>
#include "Lista.hpp"
#include "Pila.hpp"
#include "Arbol.hpp"

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

void Vertice::agregarAdyacente(Vertice *adyacente)
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
		auxiliar->siguiente = new Conexion(adyacente);
	}
	else
	{
		this->sublista = new Conexion(adyacente);
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

// CONSTRUCTOR

Conexion::Conexion(Vertice *adyacente)
{
	this->adyacente = adyacente;
	this->siguiente = NULL;
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

Lista::Lista()
{
	this->primero = NULL;
}

// DESTRUCTOR

Lista::~Lista()
{
	delete primero;
	primero = NULL;
}

// AGREGAR NODO

void Lista::agregarNodo(long long int codigoCarrera)
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

bool Lista::agregarAdyacente(long long int codigoCarrera1, long long int codigoCarrera2)
{
	Vertice *nodo1 =  devolverNodo(codigoCarrera1);
	if (nodo1)
	{
		Vertice *nodo2 = devolverNodo(codigoCarrera2);
		if (nodo2)
		{
			nodo1->agregarAdyacente(nodo2);
			return true;
		}
	}
	std::cout << "\t[ERROR]\t\t No se puede establecer la adyacencia entre [" << codigoCarrera1 << "] y [" << codigoCarrera2 << "] ya que no existe uno de los nodos.\n";
	return false;
}

void Lista::agregarBidireccional(long long int codigoCarrera1, long long int codigoCarrera2)
{
	if (agregarAdyacente(codigoCarrera1, codigoCarrera2))
	{
		// Si se pudo agregar la primera adyacencia (de 1 a 2), se agrega la misma
		// en dirección contraria
		agregarAdyacente(codigoCarrera2, codigoCarrera1);
	}
}

// COMPROBACIONES

Vertice *Lista::devolverNodo(long long int codigoCarrera)
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

bool Lista::existe(long long int codigoCarrera)
{
	// NULL = 0 = false
	// Cualquier otro puntero = true
	return devolverNodo(codigoCarrera);
}

// IMPRIMIR

void Lista::imprimir()
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
			<< "]\n";
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

void Lista::imprimir(long long int codigoCarrera)
{
	Vertice *auxiliar = devolverNodo(codigoCarrera);
	if (auxiliar)
	{
		std::cout << "\t[INFO]\t\t";
		Conexion *adyacente;
		Pila pila;
		pila.push(auxiliar);
		auxiliar->visitado = true;
		while (!pila.vacia())
		{
			auxiliar = pila.pop();
			std::cout << "[" << auxiliar->codigoCarrera << "] -> ";
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
		}
		std::cout << "\n";
		resetearVisitado();
	}
	else
	{
		std::cout << "\t[ERROR]\t\tEl nodo [" << codigoCarrera << "] no existe.\n";
	}
}

// PUNTOS DE ARTICULACIÓN

std::string Lista::puntosDeArticulacion()
{
	Vertice *auxiliar = primero;
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
	std::cout << "\n";
	resetearVisitado();

	arbol.asignarNumeros();
	arbol.preorden();
	std::string resultado, retorno = arbol.puntosDeArticulacion();
	if (retorno == "")
	{
		resultado = "No hay.";
	}
	else
	{
		resultado = retorno;
	}
	return resultado;
}

// DESPUÉS DE IMPRIMIR O HACER PUNTOS DE ARTICULACIÓN

void Lista::resetearVisitado()
{
	Vertice *auxiliar = primero;
	while (auxiliar)
	{
		auxiliar->visitado = false;
		auxiliar = auxiliar->siguiente;
	}
}

// COMPROBACIONES

bool Lista::adyacentes(long long int codigoCarrera1, long long int codigoCarrera2)
{
	Vertice *auxiliar1 = devolverNodo(codigoCarrera1), *auxiliar2 = devolverNodo(codigoCarrera2);
	if (!auxiliar1 || !auxiliar2)
	{
		// Si alguno de los dos no existe
		return false;
	}
	return adyacentes(auxiliar1, auxiliar2);
}

bool Lista::adyacentes(Vertice *nodo1, Vertice *nodo2)
{
	if (!(nodo1 && nodo2))
	{
		// Si alguno de los dos no existe
		return false;
	}
	return nodo1->esAdyacente(nodo2) || nodo2->esAdyacente(nodo1);
}