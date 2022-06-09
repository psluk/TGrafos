#ifndef RUTA_HPP
#define RUTA_HPP

#include "Grafo.hpp"

class Vertice;

// -------------------- NODO --------------------

class NodoRuta
{
private:
    Vertice *origen;
    Vertice *llegada;
    int peso;
    NodoRuta *siguiente;
    int subruta;

public:
    NodoRuta(Vertice *origen, Vertice *llegada, int peso, int subruta);

    // COMPROBACIONES
    bool conectable(Vertice *nodo1, Vertice *nodo2);
    // Retorna true si alguno de los nodos es igual al de origen o llegada

    friend class Ruta;
    friend class Grafo;
};

// -------------------- LISTA --------------------

class Ruta
{
private:
    NodoRuta *primero;
    int ultimaSubruta;

    // COMPROBACIONES INTERNAS
    int numeroDeSubruta(Vertice *buscado);

public:
    // CONSTRUCTOR Y DESTRUCTOR
    Ruta();
    ~Ruta();

    // INSERCIONES
    void insertarFinal(Vertice *origen, Vertice *llegada, int peso);
    void insertarOrdenado(Vertice *origen, Vertice *llegada, int peso); // Ordenado por pesos

    // COMPROBACIONES
    bool existeNodo(Vertice *buscado);               // Para ver si ese vértice ya se agregó
    bool existeRuta(Vertice *nodo1, Vertice *nodo2); // Para verificar que no se haga un ciclo

    // CONECTAR SUBRUTAS
    int buscarSubrutas(Vertice *nodo1, Vertice *nodo2);
    void unirSubrutas(int subruta1, int subruta2);

    // IMPRIMIR
    void imprimir(std::string titulo, bool imprimirSuma);

    friend class Grafo;
};

#endif