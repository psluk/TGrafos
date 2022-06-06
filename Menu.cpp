#include "Menu.hpp"


void Menu::opcion1()
{
	system("cls");
	cout<<"\t"; system("pause");
	return;
}

void Menu::opcion2()
{
	system("cls");
	cout<<"\t"; system("pause");
	return;
}

void Menu::opcion3()
{
	system("cls");
	cout<<"\t"; system("pause");
	return;
}

void Menu::opcion4()
{
	system("cls");
	cout<<"\t"; system("pause");
	return;
}

void Menu::opcion5()
{
	system("cls");
	cout<<"\t"; system("pause");
	return;
}

void Menu::opcion6()
{
	system("cls");
	cout<<"\t"; system("pause");
	return;
}


void Menu::menu_Principal() ()
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
        cout << "\t1. Seleccionar Grafo." << endl;
        cout << "\t2. Prim." << endl;
        cout << "\t3. Kruskal." << endl;
        cout << "\t4. Dijkstra." << endl;
        cout << "\t5. Profundidad." << endl;
        cout << "\t6. Puntos de Articulaion." << endl;
        cout << "\t7. Salir." << endl;
        
        cout << "\n\tIngrese una opcion: ";
        cin >> input;
        
        if (!fAuxs.esEntero(input)) opcion = -1;
        else opcion = atoi(input.c_str());
        
		switch (opcion){
            case 1:
            	this.opcion1();
            	cin.ignore();
				break;
            case 2:
            	this.opcion2();
            	cin.ignore();
                break;
            case 3:
            	this.opcion3();
            	cin.ignore();
            	break;
            case 4:
            	this.opcion4();
            	cin.ignore();
                break;
            case 5:
            	this.opcion5();
            	cin.ignore();
                break;
            case 6:
            	this.opcion6();
            	cin.ignore();
                break;
            case 7:
            	flag = false;
            	cin.ignore();
                break;
            default:
            	cin.ignore();
            	cout << "\n\tError: Debe introducir una de las anteriores opciones.\n\n";
            	cout<<"\t"; system("pause");
            	break;
        }        
    } while (flag);
    system("cls");
	return;
}
