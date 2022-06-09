#pragma once
#include <string>

#include "Grafo.hpp"

class Archivos
{
private:


public:
	// M?TODOS DE CONVERSI?N
	static int convertirArregloAEntero(char *arreglo);
	static long long int convertirArregloALongLong(char *arreglo);

	static void leerEstudiantes(Grafo &grafo);
	static void leerCon(Grafo &grafo);



};
