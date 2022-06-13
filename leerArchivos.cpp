#include "LeerArchivos.h"
#include "Reportes.hpp"

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

void Archivos::imprimirRotuloInicial()
{
    std::string resultado = "\t\t\t\tLectura de archivos\n";
    std::cout << "\n"
              << resultado;
    ReporteEnArchivo::archivoDeReportes->escribir(resultado);
}

void Archivos::imprimirLeyendo(std::string rutaDeArchivo)
{
    std::string resultado = "Leyendo \"";
    resultado += rutaDeArchivo;
    resultado += "\"...\n";
    std::cout << "\n"
              << resultado;
    ReporteEnArchivo::archivoDeReportes->escribir(resultado);
}

void Archivos::imprimirNoEncontrado(std::string rutaDeArchivo)
{
    std::string resultado = "\t[ERROR]\t\tNo se pudo encontrar el archivo \"";
    resultado += rutaDeArchivo;
    resultado += "\".\n";
    std::cout << resultado;
    ReporteEnArchivo::archivoDeReportes->escribir(resultado);
}

void Archivos::imprimirFaltaParametros(std::string linea)
{
    std::string resultado = "\t[ERROR]\t\tNo hay datos suficientes para leer: \"";
    resultado += linea;
    resultado += "\".\n";
    std::cout << resultado;
    ReporteEnArchivo::archivoDeReportes->escribir(resultado);
}

void Archivos::imprimirInvalido(std::string valor, std::string linea)
{
    std::string resultado = "\t[ERROR]\t\tNo se pudo leer el valor \"";
    resultado += valor;
    resultado += "\", en \"";
    resultado += linea;
    resultado += "\".\n";
    std::cout << resultado;
    ReporteEnArchivo::archivoDeReportes->escribir(resultado);
}

void Archivos::imprimirOtroError(std::string tipo, std::string valor)
{
    std::string resultado = "\t[";
    resultado += tipo;
    resultado += "]\t\t";
    resultado += valor;
    resultado += ".\n";
    std::cout << resultado;
    ReporteEnArchivo::archivoDeReportes->escribir(resultado);
}

void Archivos::leerVertices(Grafo &grafo, std::string rutaDeArchivo)
{
    std::ifstream archivoVertices;
    imprimirLeyendo(rutaDeArchivo);

    archivoVertices.open(rutaDeArchivo);
    if (!archivoVertices.is_open())
    {
        imprimirNoEncontrado(rutaDeArchivo);
        return;
    }
    std::string linea;
    while (getline(archivoVertices, linea))
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
    archivoVertices.close();
}

void Archivos::leerConexiones(Grafo &grafo, std::string rutaDeArchivo, bool existePeso)
{
    std::ifstream archivoConexiones;
    imprimirLeyendo(rutaDeArchivo);

    archivoConexiones.open(rutaDeArchivo);
    if (!archivoConexiones.is_open())
    {
        imprimirNoEncontrado(rutaDeArchivo);
        return;
    }
    std::string linea;
    while (getline(archivoConexiones, linea))
    {
        if (linea == "")
        {
            continue;
        }

        char lineaChar[linea.size() + 1];
        strcpy(lineaChar, linea.c_str());

        char *id1Char = strtok(lineaChar, ";");
        if (id1Char == NULL)
        {
            imprimirFaltaParametros(linea);
            continue;
        }

        long long int id1 = convertirArregloALongLong(id1Char);
        if (id1 == -2)
        {
            imprimirInvalido(id1Char, linea);
            continue;
        }

        char *id2Char = strtok(NULL, ";");
        if (id2Char == NULL)
        {
            imprimirFaltaParametros(linea);
            continue;
        }

        long long int id2 = convertirArregloALongLong(id2Char);
        if (id2 == -2)
        {
            imprimirInvalido(id2Char, linea);
            continue;
        }

        long long int peso = 0;
        if (existePeso)
        {
            char *pesoChar = strtok(NULL, ";");
            if (pesoChar == NULL)
            {
                imprimirFaltaParametros(linea);
                continue;
            }

            peso = convertirArregloALongLong(pesoChar);
            if (peso == -2)
            {
                imprimirInvalido(pesoChar, linea);
                continue;
            }
        }

        grafo.agregarBidireccional(id1, id2, peso);
    }
    archivoConexiones.close();
}
