#ifndef MENU_HPP
#define MENU_HPP

#include <iostream> 
#include <cstdlib>

#include "Funciones auxiliares.hpp"
#include "Grafo.hpp"
#include "Reportes.hpp"


using namespace std;

class Menu
{
	//Atributos.
	private:
		
	//Metodos.
	public:
		Menu () {
		}
		void menu_Principal ();
		
		void opcion1 ();
		void opcion2 ();
		void opcion3 ();
		void opcion4 ();
		void opcion5 ();
		void opcion6 ();
};

#endif
