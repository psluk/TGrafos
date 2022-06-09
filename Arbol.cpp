#include <iostream>
#include <string>
#include "Arbol.hpp"

// LISTA DE HIJO

Hijo::Hijo(NodoArbol *hijo)
{
    this->hijo = hijo;
    siguiente = NULL;
}

Hijo::~Hijo()
{
    if (siguiente)
    {
        delete siguiente;
    }
}

void Hijo::agregarHijo(NodoArbol *hijo)
{
    Hijo *auxiliar = this;
    while (auxiliar->siguiente)
    {
        auxiliar = auxiliar->siguiente;
    }
    hijo->numero = 0;
    auxiliar->siguiente = new Hijo(hijo);
}

// NODO DE ÁRBOL

NodoArbol::NodoArbol(Vertice *vertice)
{
    this->vertice = vertice;
    this->numero = 0;
    hijos = NULL;
    retorno = NULL;
}

NodoArbol::~NodoArbol()
{
    delete hijos;
}

void NodoArbol::agregarHijo(Vertice *hijo)
{
    NodoArbol *nuevo = new NodoArbol(hijo);
    if (this->hijos)
    {
        this->hijos->agregarHijo(nuevo);
    }
    else
    {
        this->hijos = new Hijo(nuevo);
    }
}

NodoArbol *NodoArbol::nodoDeVertice(Vertice *vertice, Vertice *destino)
{
    if (this->vertice == destino)
    {
        // Se supone que "destino", que es el nodo que va a apuntar
        // a "vertice", debe estar más abajo que "vertice"
        // Si nos encontramos a "destino" antes, retornamos NULL
        // para no insertarlo
        return NULL;
    }
    if (this->vertice == vertice)
    {
        return this;
    }
    else
    {
        NodoArbol *resultado = NULL;
        Hijo *hijo = hijos;
        while (hijo)
        {
            resultado = hijo->hijo->nodoDeVertice(vertice, destino);
            if (resultado)
            {
                // Si encontró una coincidencia, detiene el ciclo
                break;
            }
            hijo = hijo->siguiente;
        }
        return resultado; // No lo encontró
    }
}

bool NodoArbol::agregarRetorno(Vertice *destino, NodoArbol *retorno)
{
    // Retorna true si se pudo insertar (o si no hace falta insertarlo)
    if (this->vertice == destino)
    {
        if (!(retorno->esHijo(this))) // Si el "retorno" es padre del actual, no se agrega
        {
            if (!(this->retorno && retorno->numero >= this->retorno->numero))
            {
                // Para entrar aquí tienen que pasar dos cosas
                // 1. No tener ya una arista de retorno
                // 2. Tener una arista de retorno, pero a un nodo con un número menor
                //    que el del retorno que se le pretende dar
                this->retorno = retorno;
            }
            else
            {
                // Puede ser que necesite agregarse la arista de retorno, pero en dirección contraria
                // (apuntando del retorno hacia este nodo)
                if (retorno && !(retorno->retorno && retorno->retorno->numero <= numero) && retorno->numero > numero)
                {
                    retorno->retorno = this;
                }
            }
        }
        return true;
    }
    else
    {
        Hijo *hijo = hijos;
        while (hijo)
        {
            if (hijo->hijo->agregarRetorno(destino, retorno))
            {
                return true;
            }
            hijo = hijo->siguiente;
        }
        return false;
    }
}

bool NodoArbol::esHijo(NodoArbol *buscado)
{
    Hijo *hijo = hijos;
    while (hijo)
    {
        if (hijo->hijo == buscado)
        {
            return true;
        }
        hijo = hijo->siguiente;
    }
    return false;
}

// RECORRIDO

std::string NodoArbol::preorden()
{
    std::string reporte = "\n\t\t\t";
    reporte += std::to_string(numero + 1);
    reporte += ".\t[";
    reporte += std::to_string(this->vertice->codigoCarrera);
    reporte += "] (";
    reporte += std::to_string(numero + 1);
    reporte += ", ";
    reporte += std::to_string(bajo + 1);
    reporte += ")\t\tRetorno: ";
    if (this->retorno)
    {
        reporte += "[";
        reporte += std::to_string(this->retorno->vertice->codigoCarrera);
        reporte += "]";
    }
    else
    {
        reporte += "* no hay *";
    }

    Hijo *hijo = hijos;
    while (hijo)
    {
        reporte += hijo->hijo->preorden();
        hijo = hijo->siguiente;
    }

    return reporte;
}

// ASIGNAR NUMERACIÓN

void NodoArbol::asignar(int &contador)
{
    this->numero = contador;
    this->bajo = contador;
    contador++;
    Hijo *auxiliar = hijos;
    while (auxiliar)
    {
        auxiliar->hijo->asignar(contador);
        auxiliar = auxiliar->siguiente;
    }
}

int NodoArbol::corregirBajo()
{
    if (this->retorno)
    {
        this->bajo = this->retorno->bajo;
    }
    if (this->hijos)
    {
        int actual;
        int minimo = hijos->hijo->corregirBajo();
        // El mínimo es, inicialmente, el del primer hijo
        Hijo *hijo = hijos->siguiente;
        while (hijo)
        {
            actual = hijo->hijo->corregirBajo();
            if (actual < minimo)
            {
                minimo = actual;
            }
            hijo = hijo->siguiente;
        }
        if (minimo < this->bajo)
        {
            this->bajo = minimo;
        }
    }
    return this->bajo;
}

// AGREGAR HIJO DONDE CORRESPONDA

void NodoArbol::agregarHijoAdyacente(Grafo *lista, Vertice *vertice)
{
    if (this->hijos)
    {
        int maximo = -1, actual;
        Hijo *auxiliar = hijos;
        NodoArbol *hijoMaximo = NULL;
        while (auxiliar)
        {
            actual = auxiliar->hijo->nivelParaInsercion(lista, vertice);
            if (actual > maximo)
            {
                hijoMaximo = auxiliar->hijo;
                maximo = actual;
            }
            auxiliar = auxiliar->siguiente;
        }
        if (hijoMaximo)
        {
            // Si entra aquí, es porque se puede insertar en algún hijo
            hijoMaximo->agregarHijoAdyacente(lista, vertice);
            return;
        }
    }
    if (this->vertice->esAdyacente(vertice))
    {
        agregarHijo(vertice);
        // Se agrega como hijo del actual
        // (si no se pudo insertar en alguno de los hijos)
    }
}

int NodoArbol::nivelParaInsercion(Grafo *lista, Vertice *vertice)
{
    int maximo = -1, actual;
    Hijo *auxiliar = hijos;
    while (auxiliar)
    {
        actual = auxiliar->hijo->nivelParaInsercion(lista, vertice);
        if (actual > maximo)
        {
            maximo = actual;
        }
        auxiliar = auxiliar->siguiente;
    }
    if (maximo != -1)
    {
        maximo++;
    }
    else
    {
        if (this->vertice->esAdyacente(vertice))
        {
            return 1;
        }
    }
    return maximo;
}

// PUNTOS

int NodoArbol::cantidadDeHijos()
{
    int resultado = 0;
    Hijo *auxiliar = hijos;
    while (auxiliar)
    {
        resultado++;
        auxiliar = auxiliar->siguiente;
    }
    return resultado;
}

std::string NodoArbol::puntosDeArticulacion(bool esRaiz)
{
    std::string resultado = "", actual = "", reporte;
    Hijo *auxiliar = hijos;
    bool agregado = false; // Para no agregarlo más de una vez

    reporte = "\n\t\t\t";
    reporte += std::to_string(this->numero + 1);
    reporte += ".\t[";
    reporte += std::to_string(this->vertice->codigoCarrera);
    reporte += "]\t(";
    reporte += "num: ";
    reporte += std::to_string(this->numero + 1);
    reporte += " | bajo: ";
    reporte += std::to_string(this->bajo + 1);
    reporte += ")";

    if (esRaiz)
    {
        reporte += "\n\t\t\t\t\t¿Hijos (";
        reporte += std::to_string(cantidadDeHijos());
        reporte += ") > 1?\t\t\t";
        if (cantidadDeHijos() > 1)
        {
            agregado = true;
            reporte += "Si";
        }
        else
        {
            reporte += "No";
        }
    }
    else
    {
        if (auxiliar)
        {
            while (auxiliar)
            {
                reporte += "\n\t\t\t\t\t[";
                reporte += std::to_string(auxiliar->hijo->vertice->codigoCarrera);
                reporte += "] ¿Bajo (";
                reporte += std::to_string(auxiliar->hijo->bajo + 1);
                reporte += ") >= ";
                reporte += std::to_string(this->numero + 1);
                reporte += "?\t";
                if (auxiliar->hijo->bajo >= numero)
                {
                    agregado = true;
                    reporte += "Si";
                }
                else
                {
                    reporte += "No";
                }
                auxiliar = auxiliar->siguiente;
            }
        }
        else
        {
            reporte += "\n\t\t\t\t\tSin hijos";
        }
    }
    reporte += "\n\t\t\t\tResultado: ";
    if (agregado)
    {
        reporte += "Si";
    }
    else
    {
        reporte += "No";
    }
    reporte += " es punto de articulacion\n";
    ReporteEnArchivo::archivoDeReportes->escribir(reporte);

    auxiliar = hijos;
    agregado = false;

    while (auxiliar)
    {
        if (!agregado && ((esRaiz && cantidadDeHijos() > 1) || (!esRaiz && auxiliar->hijo->bajo >= numero)))
        {
            if (resultado != "")
            {
                resultado += ", ";
            }
            resultado += "[";
            resultado += std::to_string(vertice->codigoCarrera);
            resultado += "]";
            agregado = true;
        }
        actual = auxiliar->hijo->puntosDeArticulacion(false);
        if (actual != "")
        {
            if (resultado != "")
            {
                resultado += ", ";
            }
            resultado += actual;
        }
        auxiliar = auxiliar->siguiente;
    }
    return resultado;
}

// ÁRBOL

Arbol::Arbol(Grafo *lista)
{
    raiz = NULL;
    this->lista = lista;
}

Arbol::~Arbol()
{
    delete raiz;
}

// ASIGNAR NUMERACIÓN

void Arbol::asignarNumeros()
{
    if (raiz)
    {
        int contador = 0;
        raiz->asignar(contador);
        raiz->corregirBajo();
    }
}

// AGREGAR ELEMENTO

void Arbol::agregar(Vertice *vertice)
{
    if (raiz)
    {
        raiz->agregarHijoAdyacente(lista, vertice);
    }
    else
    {
        raiz = new NodoArbol(vertice);
    }
    asignarNumeros();
}

void Arbol::agregarRetorno(Vertice *destino, Vertice *retorno)
{
    if (raiz)
    {
        NodoArbol *nodoDeRetorno = raiz->nodoDeVertice(retorno, destino);
        if (nodoDeRetorno)
        {
            raiz->agregarRetorno(destino, nodoDeRetorno);
        }
    }
}

// RECORRIDO

void Arbol::preorden()
{
    std::string reporte = "\n\t[INFO]\t\tRecorrido en preorden. Formato: [cod] (num, bajo):\n";
    if (raiz)
    {
        reporte += raiz->preorden();
    }
    else
    {
        reporte += "* sin elementos *";
    }
    reporte += "\n";
    ReporteEnArchivo::archivoDeReportes->escribir(reporte);
}

// PUNTOS

std::string Arbol::puntosDeArticulacion()
{
    std::string resultado = "";
    ReporteEnArchivo::archivoDeReportes->escribir("\n\t[INFO]\t\tAnalizando posibles puntos:\n");
    if (raiz)
    {
        resultado = raiz->puntosDeArticulacion(true);
    }
    return resultado;
}