#ifndef MENU_HPP
#define MENU_HPP

#include <iostream> 
#include <cstdlib>

#include "FuncionesAuxiliares.hpp"
#include "Grafo.hpp"
#include "Reportes.hpp"


using namespace std;

class Menu
{
	//Atributos.
	private:
		bool esGrafo2 = false; // Empieza en el grafo 1

		// PARA RECIBIR ENTRADAS DE TECLADO
    	int obtenerOpcionMenu(int cantidadDeElementos);
		long long int obtenerVertice(Grafo &grafo1, Grafo &grafo2);

		// VACIAR ENTRADA
    	void vaciarEntrada(); // Después de leer un valor no válido
		
	//Metodos.
	public:
		Menu () {}
		void menu_Principal (Grafo &grafo1, Grafo &grafo2);
		
		void opcion1 (Grafo &grafo1, Grafo &grafo2);
		void opcion2 (Grafo &grafo1, Grafo &grafo2);
		void opcion3 (Grafo &grafo1, Grafo &grafo2);
		void opcion4 (Grafo &grafo1, Grafo &grafo2);
		void opcion5 (Grafo &grafo1, Grafo &grafo2);
		void opcion6 (Grafo &grafo1, Grafo &grafo2);
};

#endif
