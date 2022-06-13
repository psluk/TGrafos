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

void Grafo::puntosDeArticulacion(long long int codigoCarrera)
{
	std::string reporte = "\n-------------------- PUNTOS DE ARTICULACION --------------------\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	reporte = "";

	Vertice *auxiliar = devolverNodo(codigoCarrera);

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

// DIJKSTRA

void Grafo::dijkstra(long long int carreraInicio, long long int carreraFinal)
{
	std::string reporte = "\n-------------------- DIJKSTRA --------------------\n";
	ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	reporte = "";

	Vertice *auxiliar = devolverNodo(carreraInicio);

	if (auxiliar && auxiliar->sublista)
	{
		Ruta conexiones; // Todas las conexiones

		Pila pila[2]; // Una pila contendrá los nodos resueltos que tienen nodos sin resolver
					  // La otra contendrá nodos temporalmente

		Pila nuevos;  // Adyacentes conectados en el último paso
		Pila nuevosPesos;

		Pila pesos[2]; // Esta pila contendrá los costos desde el inicio hasta cada 
					   // nodo de las otras dos pilas

		Vertice *origen, *destino; // origen y destino de la nueva conexión
		Vertice *peso;			   // para la pila de los pesos
		Conexion *minimo;		   // auxiliar del adyacente de menor peso
		Conexion *conexAux;
		int pesoTotalMinimo;	   // peso mínimo desde el inicio hasta el adyacente nuevo
		int pesoHastaAuxiliar;
		int pesoNuevo;			   // peso de la conexión nueva

		pila[0].push(auxiliar);
		auxiliar->visitado = true;
		pesos[0].push(new Vertice(0)); // 0 = costo desde el origen (empieza en 0)

		while (!pila[0].vacia())
		{
			// Mientras la pila tenga elementos, hace este ciclo
			
			// Resetea las variables necesarias
			origen = destino = NULL;
			pesoTotalMinimo = pesoHastaAuxiliar = -1;
			while (!pila[0].vacia())
			{
				// Ciclo para pasar los vértices de esta pila a la otra
				// (verifica uno por uno cuál adyacente tiene el menor peso desde el origen)
				auxiliar = pila[0].pop();
				peso = pesos[0].pop(); // Peso desde el inicio hasta "auxiliar"
				pesoHastaAuxiliar = peso->codigoCarrera;

				// Mete los nodos sacados a la pila temporal
				pila[1].push(auxiliar);
				pesos[1].push(peso);

				minimo = auxiliar->conexionMinima(); // adyacente de menor peso;

				if (!minimo)
				{
					// Si no tiene adyacentes sin visitar, se sacan los ingresados en la pila temporal
					pila[1].pop();
					pesos[1].pop();
				}

				if (pesoTotalMinimo == -1 || (minimo->peso + pesoHastaAuxiliar < pesoTotalMinimo))
				{
					// Si no se ha encontrado un adyacente para agregar
					// o si se encontró uno cuyo costo es menor
					pesoTotalMinimo = minimo->peso + pesoHastaAuxiliar;
					origen = auxiliar;
					destino = minimo->adyacente;
					pesoNuevo = minimo->peso;
				}
			}

			if (origen)
			{
				conexiones.insertarFinal(origen, destino, pesoNuevo);
				nuevos.push(destino);
				nuevosPesos.push(new Vertice(pesoTotalMinimo));
			}

			// Ahora pasa todos los elementos de pila[1] a pila[0]
			// Si encuentra una conexión cuyo costo desde el inicio es igual,
			// la agrega a la lista de conexiones

			while (!pila[1].vacia())
			{
				auxiliar = pila[1].pop();
				peso = pesos[1].pop(); // Peso desde el inicio hasta "auxiliar"
				pesoHastaAuxiliar = peso->codigoCarrera;

				minimo = auxiliar->conexionMinima(); // adyacente de menor peso;

				if (!minimo)
				{
					// Si entra aquí, ya no tiene adyacentes sin procesar,
					// así que no lo vuelve a meter a la pila original
					continue;
				}

				conexAux = auxiliar->sublista;

				while (conexAux)
				{
					// Recorre los adyacentes y agrega todos los que tengan el mismo
					// costo desde el origen
					if (!conexAux->adyacente->visitado)
					{
						// Hace esto mientras que el adyacente actual no esté visitado
						if (conexAux->peso + pesoHastaAuxiliar == pesoTotalMinimo)
						{
							// (La lista de conexiones revisa que no haya duplicados en las rutas)
							conexiones.insertarFinal(auxiliar, minimo->adyacente, minimo->peso);
							nuevos.push(minimo->adyacente);
							nuevosPesos.push(new Vertice(pesoTotalMinimo));
						}
					}
					conexAux = conexAux->siguiente;
				}

				// Mete los nodos sacados a la pila original
				pila[0].push(auxiliar);
				pesos[0].push(peso);
			}

			while (!nuevos.vacia())
			{
				// Ciclo que marca los nuevos agregados como visitados
				auxiliar = nuevos.pop();
				peso = nuevosPesos.pop();
				if (auxiliar && !auxiliar->visitado)
				{
					pila[0].push(auxiliar);
					pesos[0].push(peso);
					auxiliar->visitado = true;
				}
			}

			while (!pila[0].vacia())
			{
				// Saca los que no tengan más adyacentes sin visitar
				auxiliar = pila[0].pop();
				peso = pesos[0].pop();

				if (auxiliar->conexionMinima())
				{
					// Si tiene alguna conexión mínima, es porque algún adyacente no está visitado
					// Se agrega a la pila temporal
					pila[1].push(auxiliar);
					pesos[1].push(peso);
				}
			}

			// Pasa los elementos de pila[1] (del ciclo anterior) a la pila original
			while (!pila[1].vacia())
			{
				auxiliar = pila[1].pop();
				peso = pesos[1].pop();

				pila[0].push(auxiliar);
				pesos[0].push(peso);
			}
		}

		conexiones.imprimir("Conexiones", true);
		resetearVisitado();
	}
	else
	{
		std::cout << "\n\t[ERROR]\t\tEl nodo [" << carreraInicio << "] no existe o no tiene adyacentes.\n";

		reporte = "\n\t[ERROR]\t\tEl nodo [";
		reporte += std::to_string(carreraInicio);
		reporte += "] no existe o no tiene adyacentes.\n";
		ReporteEnArchivo::archivoDeReportes->escribir(reporte);
	}
}