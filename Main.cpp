#include <iostream>
#include "Lista.hpp"
#include "Reportes.hpp"

int main()
{
	Lista lista;
	Reportes reportes;

	// GRAFO 1
	/*
	lista.agregarNodo(5001);
	lista.agregarNodo(5003);
	lista.agregarNodo(5006);
	lista.agregarNodo(5009);
	lista.agregarNodo(5005);
	lista.agregarNodo(5011);
	lista.agregarNodo(5008);
	lista.agregarNodo(5012);
	lista.agregarNodo(5002);
	lista.agregarNodo(5004);
	lista.agregarNodo(5007);
	lista.agregarNodo(5010);

	lista.agregarBidireccional(5001, 5002);
	lista.agregarBidireccional(5001, 5009);
	lista.agregarBidireccional(5003, 5001);
	lista.agregarBidireccional(5005, 5003);
	lista.agregarBidireccional(5002, 5003);
	lista.agregarBidireccional(5002, 5005);
	lista.agregarBidireccional(5005, 5004);
	lista.agregarBidireccional(5003, 5007);
	lista.agregarBidireccional(5004, 5007);
	lista.agregarBidireccional(5005, 5006);
	lista.agregarBidireccional(5005, 5011);
	lista.agregarBidireccional(5006, 5007);
	lista.agregarBidireccional(5009, 5010);
	lista.agregarBidireccional(5011, 5010);
	lista.agregarBidireccional(5006, 5011);
	lista.agregarBidireccional(5011, 5012);
	lista.agregarBidireccional(5010, 5012);
	lista.agregarBidireccional(5008, 5010);
	lista.agregarBidireccional(5007, 5008);
	lista.agregarBidireccional(5008, 5009);
	lista.agregarBidireccional(5006, 5008);*/

	// GRAFO 2
	
	lista.agregarNodo(5001);
	lista.agregarNodo(5003);
	lista.agregarNodo(5006);
	lista.agregarNodo(5009);
	lista.agregarNodo(5005);
	lista.agregarNodo(5008);
	lista.agregarNodo(5012);
	lista.agregarNodo(5002);
	lista.agregarNodo(5004);
	lista.agregarNodo(5007);
	lista.agregarNodo(5010);
	
	lista.agregarBidireccional(5001, 5002);
	lista.agregarBidireccional(5002, 5005);
	lista.agregarBidireccional(5004, 5008);
	lista.agregarBidireccional(5001, 5004);
	lista.agregarBidireccional(5001, 5003);
	lista.agregarBidireccional(5005, 5010);
	lista.agregarBidireccional(5006, 5010);
	lista.agregarBidireccional(5007, 5003);
	lista.agregarBidireccional(5009, 5007);
	lista.agregarBidireccional(5009, 5012);
	lista.agregarBidireccional(5012, 5008);

	lista.imprimir();
	std::cout << "\n\n";
	lista.imprimir(5001);

	std::cout << "\n\nPuntos de articulaci" << (char)162 << "n: " << lista.puntosDeArticulacion();
	return 0;
}
