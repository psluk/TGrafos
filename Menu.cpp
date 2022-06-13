#include "Menu.hpp"
#include "Grafo.hpp"
#include <limits>

// PARA LEER ENTRADA

void Menu::vaciarEntrada()
{
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Borra la cantidad de caracteres dada por numeric_limits<streamsize>::max()
    // o hasta que encuentre un cambio de línea
}

int Menu::obtenerOpcionMenu(int cantidadDeElementos)
{
    int respuestaMenu;
    while (true) // Cuando hay una respuesta válida, se sale
    {
        if (std::cin >> respuestaMenu)
        {
            if (respuestaMenu > 0 && respuestaMenu <= cantidadDeElementos)
            {
                // Si respuestaMenu está en el rango o es -1 (si es que se acepta -1), retorna el valor
                return respuestaMenu;
            }
        }
        else
        {
            vaciarEntrada(); // Resetea el std::cin
        }
        std::cout << "\n"
                  << "\t[ERROR]\t\tNo ingres" << (char)162 << " una opci" << (char)162 << "n v" << (char)160 << "lida.\n";
        std::cout << "\nInt" << (char)130 << "ntelo de nuevo: ";
    }
}

long long int Menu::obtenerVertice(Grafo &grafo1, Grafo &grafo2)
{
	long long int respuestaVertice;
    Grafo *grafo;
	if (esGrafo2)
	{
		grafo = &grafo2;
	}
	else
	{
		grafo = &grafo1;
	}

    while (true)
    {
        if (std::cin >> respuestaVertice)
        {
            if (grafo->existe(respuestaVertice) || respuestaVertice == -1)
            {
                // Si respuestaVertice existe o es -1, retorna el valor
                return respuestaVertice;
            }
            std::cout << "\n\t[ERROR]\t\tLa carrera [" << respuestaVertice << "] no existe.\n";
        }
        else
        {
            vaciarEntrada(); // Resetea el std::cin
            std::cout << "\n"
                      << "\t[ERROR]\t\tNo ingres" << (char)162 << " una opci" << (char)162 << "n v" << (char)160 << "lida.\n";
        }
        std::cout << "\nInt" << (char)130 << "ntelo de nuevo o salga con -1: ";
    }
}

// OPCIONES

void Menu::opcion1(Grafo &grafo1, Grafo &grafo2)
{
	system("cls");
	esGrafo2 = !esGrafo2;
	return;
}

void Menu::opcion2(Grafo &grafo1, Grafo &grafo2)
{
	system("cls");
	cout<<"\tIngrese la carrera por donde se empieza: ";
	long long int carrera = obtenerVertice(grafo1, grafo2);
	if (carrera == -1)
	{
		return;
	}
	if (esGrafo2)
	{
		grafo2.prim(carrera);
	}
	else
	{
		grafo1.prim(carrera);
	}
	system("pause");
	return;
}

void Menu::opcion3(Grafo &grafo1, Grafo &grafo2)
{
	system("cls");
	cout<<"\t";
	if (esGrafo2)
	{
		grafo2.kruskal();
	}
	else
	{
		grafo1.kruskal();
	}
	system("pause");
	return;
}

void Menu::opcion4(Grafo &grafo1, Grafo &grafo2)
{
	system("cls");
	cout<<"\tIngrese la carrera por donde se empieza: ";
	long long int carrera = obtenerVertice(grafo1, grafo2);
	if (carrera == -1)
	{
		return;
	}
	if (esGrafo2)
	{
		grafo2.dijkstra(carrera, carrera);
	}
	else
	{
		grafo1.dijkstra(carrera, carrera);
	}
	system("pause");
	return;
}

void Menu::opcion5(Grafo &grafo1, Grafo &grafo2)
{
	system("cls");
	cout<<"\tIngrese la carrera por donde se empieza: ";
	long long int carrera = obtenerVertice(grafo1, grafo2);
	if (carrera == -1)
	{
		return;
	}
	if (esGrafo2)
	{
		grafo2.imprimir(carrera);
	}
	else
	{
		grafo1.imprimir(carrera);
	}
	system("pause");
	return;
}

void Menu::opcion6(Grafo &grafo1, Grafo &grafo2)
{
	system("cls");
	cout<<"\tIngrese la carrera por donde se empieza: ";
	long long int carrera = obtenerVertice(grafo1, grafo2);
	if (carrera == -1)
	{
		system("pause");
		return;
	}
	if (esGrafo2)
	{
		grafo2.puntosDeArticulacion(carrera);
	}
	else
	{
		grafo1.puntosDeArticulacion(carrera);
	}
	system("pause");
	return;
}

void Menu::menu_Principal(Grafo &grafo1, Grafo &grafo2)
{
	bool flag = true;
	do {
		string input;
	    int opcion;
	    FuncionesAux fAuxs;
	    
        system("cls");      // Para limpiar la pantalla
        system("color 70"); //El primer numero modifica el color del fondo y el segundo las letras. (En hexadecimal)

        cout << "\n\n\t\t\t\tMENU PRINCIPAL" << endl;
        cout     << "\t\t\t\t--------------" << endl << endl;
        cout << "\tElija una de las siguientes opciones:" << endl << endl;
        cout << "\t1. Grafo actual: " << ((int)esGrafo2 + 1) << ". Cambiar al otro" << endl;
        cout << "\t2. Prim" << endl;
        cout << "\t3. Kruskal" << endl;
        cout << "\t4. Dijkstra" << endl;
        cout << "\t5. Profundidad" << endl;
        cout << "\t6. Puntos de articulaion" << endl;
        cout << "\t7. Salir" << endl;
        
        cout << "\n\tIngrese una opcion: ";
        opcion = obtenerOpcionMenu(7);
        
		switch (opcion){
            case 1:
				this->opcion1(grafo1, grafo2);
				break;
            case 2:
            	this->opcion2(grafo1, grafo2);
                break;
            case 3:
            	this->opcion3(grafo1, grafo2);
            	break;
            case 4:
            	this->opcion4(grafo1, grafo2);
                break;
            case 5:
            	this->opcion5(grafo1, grafo2);
                break;
            case 6:
            	this->opcion6(grafo1, grafo2);
                break;
            case 7:
            	flag = false;
                break;
            default:
            	cout << "\n\tError: Debe introducir una de las anteriores opciones.\n\n";
            	cout<<"\t"; system("pause");
            	break;
        }        
    } while (flag);
    system("cls");
	return;
}
