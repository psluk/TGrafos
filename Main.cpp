#include <iostream>

#include "Menu.hpp"
#include "leerArchivos.h"

const char vertices1[] = "Vertices1.txt";
const char vertices2[] = "Vertices2.txt";
const char conexiones1[] = "Conexiones1.txt";
const char conexiones2[] = "Conexiones2.txt";

int main()
{
	Reportes reportes;
	Grafo grafo1, grafo2;
	Archivos::imprimirRotuloInicial();

	// LECTURA DE GRAFOS
	Archivos::leerVertices(grafo1, vertices1);
	Archivos::leerConexiones(grafo1, conexiones1, true);
	Archivos::leerVertices(grafo2, vertices2);
	Archivos::leerConexiones(grafo2, conexiones2, false);

	Menu m;
	m.menu_Principal(grafo1, grafo2);

	// GRAFO 1
	grafo1.imprimir();
	std::cout << "\n\n";
	grafo1.imprimir(5001);

	grafo1.prim(5001);
	grafo1.kruskal();
	grafo1.puntosDeArticulacion(5001);
	grafo1.dijkstra(5001, 5001);

	std::cout << "\n\n";

	// GRAFO 2
	grafo2.imprimir();
	std::cout << "\n\n";
	grafo2.imprimir(5001);

	grafo2.prim(5001);
	grafo2.kruskal();
	grafo2.puntosDeArticulacion(5001);

	return 0;
}
