


#include "LeerArchivos.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

int Archivos::convertirArregloAEntero(char *arreglo)
{
    int resultado = 0, i = 0;

    while (arreglo[i] != 0)
    {
        if (arreglo[i] >= 48 && arreglo[i] <= 57)
        {
            resultado = resultado * 10 + (arreglo[i] - 48);
        }
        else
        {
            return -2; // -2 significa "error"
        }
        i = i + 1;
    }

    return resultado;
}

long long int Archivos::convertirArregloALongLong(char *arreglo)
{
    long long int resultado = 0, i = 0;

    while (arreglo[i] != 0)
    {
        if (arreglo[i] >= 48 && arreglo[i] <= 57)
        {
            resultado = resultado * 10 + (arreglo[i] - 48);
        }
        else
        {
            return -2; // -2 significa "error"
        }
        i = i + 1;
    }

    return resultado;
}

// RÓTULOS




void Archivos::leerEstudiantes(Grafo &grafo) 
{
    std::ifstream archivoEstudiantes;
   
    archivoEstudiantes.open("Vertices1.txt");
    if (!archivoEstudiantes.is_open())
    {
        
        return;
    }
    std::string linea;
    while (getline(archivoEstudiantes, linea))
    {
        if (linea == "")
        {
            continue;
        }

        char lineaChar[linea.size() + 1];
        strcpy(lineaChar, linea.c_str());

        long long int id = convertirArregloALongLong(lineaChar); 
        if (id == -2)
        {
            
            continue;
        }
        
        grafo.agregarNodo(id);
        
    }
    archivoEstudiantes.close();
}


void Archivos::leerCon(Grafo &grafo) 
{
    std::ifstream archivoGrupo;
  
    archivoGrupo.open("Conexiones1.txt");
    if (!archivoGrupo.is_open())
    {
      	std::cout<<"no abrio  ";
        return;
    }
    std::string linea;
    while (getline(archivoGrupo, linea))
    {
        if (linea == "")
        {
            continue;
        }

        char lineaChar[linea.size() + 1];
        strcpy(lineaChar, linea.c_str());

        char *codigoCarreraChar = strtok(lineaChar, ";");
        if (codigoCarreraChar == NULL)
        {
         
            continue;
        }

        long long int codigoCarrera = convertirArregloALongLong(codigoCarreraChar); 
        if (codigoCarrera == -2)
        {
            
            continue;
        }

        char *codigoCursoChar = strtok(NULL, ";");
        if (codigoCursoChar == NULL)
        {
            
            continue;
        }

        long long int codigoCurso = convertirArregloALongLong(codigoCursoChar); 
        if (codigoCurso == -2)
        {
            
            continue;
        }

        char *codigoGrupoChar = strtok(NULL, ";");
        if (codigoGrupoChar == NULL)
        {
           
            continue;
        }

        long long int codigoGrupo = convertirArregloALongLong(codigoGrupoChar); 
        if (codigoGrupo == -2)
        {
           
            continue;
        }
	
	grafo.agregarBidireccional(codigoCarrera,codigoCurso,codigoGrupo);
	
    }
    archivoGrupo.close();
}





