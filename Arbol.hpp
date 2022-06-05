#ifndef ARBOL_HPP
#define ARBOL_HPP

#include <string>
#include "Lista.hpp"

class NodoArbol;
class Lista;

// HIJOS

class Hijo
{
private:
    NodoArbol *hijo;
    Hijo *siguiente;

public:
    // CONSTRUCTOR Y DESTRUCTOR
    Hijo(NodoArbol *hijo);
    ~Hijo();

    // AGREGAR HIJO
    void agregarHijo(NodoArbol *hijo);

    friend class NodoArbol;
};

// NODO DE ÁRBOL

class NodoArbol
{
private:
    Vertice *vertice;
    Hijo *hijos;
    int numero;
    int bajo;
    NodoArbol *retorno;

    // AGREGAR HIJO DONDE CORRESPONDA
    int nivelParaInsercion(Lista *lista, Vertice *vertice);

public:
    NodoArbol(Vertice *vertice, int numero);
    ~NodoArbol();

    // AGREGAR HIJO DE NODO ACTUAL
    void agregarHijo(Vertice *hijo);

    // AGREGAR ARISTA DE RETORNO
    NodoArbol *nodoDeVertice(Vertice *vertice, Vertice *destino);
    bool agregarRetorno(Vertice *destino, NodoArbol *retorno);
    bool esHijo(NodoArbol *buscado);

    // RECORRIDO
    void preorden();

    // ASIGNAR NUMERACIÓN
    void asignar(int &contador);
    int corregirBajo();
    
    // AGREGAR HIJO DONDE CORRESPONDA
    void agregarHijoAdyacente(Lista *lista, Vertice *vertice);

    // PUNTOS
    int cantidadDeHijos();
    std::string puntosDeArticulacion(bool esRaiz);

    friend class Hijo;
};

// ÁRBOL

class Arbol
{
private:
    NodoArbol *raiz;
    Lista *lista;
    int elementos;

public:
    // CONSTRUCTOR Y DESTRUCTOR
    Arbol(Lista *lista);
    ~Arbol();

    // ASIGNAR NUMERACIÓN
    void asignarNumeros();

    // AGREGAR ELEMENTO
    void agregar(Vertice *vertice);
    void agregarRetorno(Vertice *destino, Vertice *retorno);

    // RECORRIDO
    void preorden();

    // PUNTOS
    std::string puntosDeArticulacion();
};

#endif