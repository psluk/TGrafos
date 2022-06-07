#include "Funciones auxiliares.hpp"

bool FuncionesAux::esEntero (string & str) 
{
	int largo = str.size() - 1;
	
	for(int aux = 0; aux <= largo; aux++) {
		if (str[aux] < 48 || str[aux] > 57)
		    return false;
    }
    return true;
}

string * FuncionesAux::splitCSVtoArray(string line, int limit)
{
	string * array = new string[limit];	//array de lo que hay en el archivo
	string value = "";		            //va representando un valor especifico que cambia cada ';'
	int csvPointer = 0;		            //contador de ';' en la linea
	for(int i = 0; i < line.size(); i += 1) {
		if (line[i] == ';' && csvPointer<limit){
			array[csvPointer] = value;
			value = "";
			csvPointer++;
			continue;
		}
		value = value + line[i];
    }
    array[csvPointer] = value;
	return array;
}

string FuncionesAux::quitarEspacio (string & strPrincipal)
{
	int largo = strPrincipal.size() - 1;
	string strResult = "";
	char datDelet = 32;
	
	//cout << strPrincipal << "\n";
	for(int aux = 0; aux <= largo; aux++) 
	{
		if (strPrincipal[aux] != datDelet){
			//cout << strPrincipal[aux] << "-\n";
		    strResult = strResult + strPrincipal[aux];
		}
    }
    return strResult;
}

void FuncionesAux::reportar(string str)
{
	ofstream MyFile("Reportes.txt");
	MyFile << str;
	MyFile.close();
}

string FuncionesAux::intToStr(int numero) // Se puede y es mejor hacer (float numero)
{
    ostringstream buff;
    buff<<numero;
    return buff.str();
}
