#pragma once
#include <string>

#include "Grafo.hpp"

class Archivos
{
private:
	// RÓTULOS
	static void imprimirLeyendo(std::string rutaDeArchivo);
	static void imprimirNoEncontrado(std::string rutaDeArchivo);
	static void imprimirFaltaParametros(std::string linea);
	static void imprimirInvalido(std::string valor, std::string linea);
	static void imprimirOtroError(std::string tipo, std::string valor);

public:
	// MÉTODOS DE CONVERSIÓN
	static int convertirArregloAEntero(char *arreglo);
	static long long int convertirArregloALongLong(char *arreglo);

	static void leerVertices(Grafo &grafo, std::string rutaDeArchivo);
	static void leerConexiones(Grafo &grafo, std::string rutaDeArchivo, bool existePeso);

	// RÓTULOS
	static void imprimirRotuloInicial();
};
