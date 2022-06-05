#include <iostream>
#include "Lista.hpp"
#include "Reportes.hpp"

int main()
{
	Lista lista1, lista2;
	Reportes reportes;

	// GRAFO 1
	
	lista1.agregarNodo(5001);
	lista1.agregarNodo(5003);
	lista1.agregarNodo(5006);
	lista1.agregarNodo(5009);
	lista1.agregarNodo(5005);
	lista1.agregarNodo(5011);
	lista1.agregarNodo(5003);
	lista1.agregarNodo(5008);
	lista1.agregarNodo(5005);
	lista1.agregarNodo(5012);
	lista1.agregarNodo(5005);
	lista1.agregarNodo(5002);
	lista1.agregarNodo(5004);
	lista1.agregarNodo(5007);
	lista1.agregarNodo(5010);

	lista1.agregarBidireccional(5001, 5002, 16);
	lista1.agregarBidireccional(5001, 5009, 12);
	lista1.agregarBidireccional(5003, 5001, 10);
	lista1.agregarBidireccional(5005, 5003, 1);
	lista1.agregarBidireccional(5002, 5003, 7);
	lista1.agregarBidireccional(5002, 5005, 2);
	lista1.agregarBidireccional(5005, 5004, 13);
	lista1.agregarBidireccional(5003, 5007, 21);
	lista1.agregarBidireccional(5004, 5007, 15);
	lista1.agregarBidireccional(5005, 5006, 9);
	lista1.agregarBidireccional(5005, 5011, 4);
	lista1.agregarBidireccional(5006, 5007, 3);
	lista1.agregarBidireccional(5009, 5010, 5);
	lista1.agregarBidireccional(5011, 5010, 6);
	lista1.agregarBidireccional(5006, 5011, 8);
	lista1.agregarBidireccional(5011, 5012, 11);
	lista1.agregarBidireccional(5010, 5012, 14);
	lista1.agregarBidireccional(5008, 5010, 17);
	lista1.agregarBidireccional(5007, 5008, 18);
	lista1.agregarBidireccional(5008, 5009, 19);
	lista1.agregarBidireccional(5006, 5008, 20);

	lista1.imprimir();
	std::cout << "\n\n";
	lista1.imprimir(5001);

	// GRAFO 2
	
	lista2.agregarNodo(5001);
	lista2.agregarNodo(5003);
	lista2.agregarNodo(5006);
	lista2.agregarNodo(5009);
	lista2.agregarNodo(5005);
	lista2.agregarNodo(5008);
	lista2.agregarNodo(5012);
	lista2.agregarNodo(5002);
	lista2.agregarNodo(5004);
	lista2.agregarNodo(5007);
	lista2.agregarNodo(5010);
	
	lista2.agregarBidireccional(5001, 5002);
	lista2.agregarBidireccional(5002, 5005);
	lista2.agregarBidireccional(5004, 5008);
	lista2.agregarBidireccional(5001, 5004);
	lista2.agregarBidireccional(5001, 5003);
	lista2.agregarBidireccional(5005, 5010);
	lista2.agregarBidireccional(5006, 5010);
	lista2.agregarBidireccional(5007, 5003);
	lista2.agregarBidireccional(5009, 5007);
	lista2.agregarBidireccional(5009, 5012);
	lista2.agregarBidireccional(5012, 5008);

	lista2.imprimir();
	std::cout << "\n\n";
	lista2.imprimir(5001);

	std::cout << "\n\nPuntos de articulaci" << (char)162 << "n: " << lista2.puntosDeArticulacion();
	return 0;
}
