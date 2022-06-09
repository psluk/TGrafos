#ifndef FUNCIONES_AUXILIARES_HPP
#define FUNCIONES_AUXILIARES_HPP

/*
  Estructura de datos GR1 - Proyecto #2. 
  Profesora: Ivannia Cerdas Quesada.
  Estudiantes: Jorge Luis Rodr�guez Cruz. Carnet: 2020010773.
*/

#include <iostream> 
#include <fstream>
#include <sstream>

using namespace std;

class FuncionesAux 
{
	//Atributos.
	private:
		
	//Metodos.
	public:
		//Metodo que evalua un string, si este tiene unicamente digitos numericos retorna true.
		bool esEntero            (string & str);
		string * splitCSVtoArray (string line, int limit);
		string quitarEspacio (string & strPrincipal);
		void reportar        (string str);
		string intToStr      (int numero);
		
	friend class Menu;
};

#endif
