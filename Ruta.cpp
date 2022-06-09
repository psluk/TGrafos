#include "Ruta.hpp"
#include "Reportes.hpp"
#include <string>

// -------------------- NODO --------------------

NodoRuta::NodoRuta(Vertice *origen, Vertice *llegada, int peso, int subruta)
{
    this->origen = origen;
    this->llegada = llegada;
    this->peso = peso;
    this->subruta = subruta;
    this->siguiente = NULL;
}

bool NodoRuta::conectable(Vertice *nodo1, Vertice *nodo2)
{
    // Retorna true si alguno de los nodos es igual al de origen o llegada
    return (nodo1 == origen || nodo1 == llegada || nodo2 == origen || nodo2 == llegada);
}

// -------------------- LISTA --------------------

// CONSTRUCTOR Y DESTRUCTOR

Ruta::Ruta()
{
    this->primero = NULL;
    this->ultimaSubruta = 0;
}

Ruta::~Ruta()
{
    NodoRuta *auxiliar = primero, *temporal;
    while (auxiliar)
    {
        temporal = auxiliar;
        auxiliar = auxiliar->siguiente;
        delete temporal;
    }
}

// INSERCIONES

void Ruta::insertarFinal(Vertice *origen, Vertice *llegada, int peso)
{
    // Inserta al final de la lista

    if (primero)
    {
        NodoRuta *auxiliar = primero;
        while (auxiliar->siguiente)
        {
            if (auxiliar->origen == llegada && auxiliar->llegada == origen)
            {
                return; // Si hay conexiones en ambos sentidos, solo se inserta una
            }
            auxiliar = auxiliar->siguiente;
        }
        if (auxiliar->origen == llegada && auxiliar->llegada == origen)
        {
            return; // Si hay conexiones en ambos sentidos, solo se inserta una
        }
        auxiliar->siguiente = new NodoRuta(origen, llegada, peso, buscarSubrutas(origen, llegada));
    }
    else
    {
        primero = new NodoRuta(origen, llegada, peso, buscarSubrutas(origen, llegada));
    }
}

void Ruta::insertarOrdenado(Vertice *origen, Vertice *llegada, int peso)
{
    // Inserta de forma que la lista quede ordenada de menor (primero) a mayor peso (último)

    if (primero)
    {
        if (primero->origen == llegada && primero->llegada == origen)
        {
            return; // Si hay conexiones en ambos sentidos, solo se inserta una
        }

        NodoRuta *auxiliar = primero;
        if (peso < primero->peso)
        {
            // Se inserta al inicio
            primero = new NodoRuta(origen, llegada, peso, buscarSubrutas(origen, llegada));
            primero->siguiente = auxiliar;
        }
        else
        {
            while (auxiliar->siguiente && auxiliar->siguiente->peso <= peso)
            {
                // Si el siguiente es menor o igual, sigue avanzando
                if (auxiliar->origen == llegada && auxiliar->llegada == origen)
                {
                    return; // Si hay conexiones en ambos sentidos, solo se inserta una
                }
                auxiliar = auxiliar->siguiente;
            }

            if (auxiliar->origen == llegada && auxiliar->llegada == origen)
            {
                return; // Si hay conexiones en ambos sentidos, solo se inserta una
            }

            // Si llega aquí, ya no existe siguiente (se inserta al final) o el siguiente no tiene
            // un peso menor al del nuevo

            NodoRuta *temporal = auxiliar->siguiente;
            auxiliar->siguiente = new NodoRuta(origen, llegada, peso, buscarSubrutas(origen, llegada));
            auxiliar->siguiente->siguiente = temporal;
            return;
        }
    }
    else
    {
        primero = new NodoRuta(origen, llegada, peso, buscarSubrutas(origen, llegada));
    }
}

// COMPROBACIONES

bool Ruta::existeNodo(Vertice *buscado) // Para ver si ya se agregó un vértice a la ruta
{
    NodoRuta *auxiliar;

    while (auxiliar)
    {
        if ((auxiliar->origen == buscado) || (auxiliar->llegada == buscado))
        {
            // Lo encontró
            return true;
        }

        // Si no lo encontró, va al siguiente
        auxiliar = auxiliar->siguiente;
    }

    // Si llegó aquí, no lo encontró en toda la lista
    return false;
}

int Ruta::numeroDeSubruta(Vertice *buscado)
{
    NodoRuta *auxiliar = primero;
    while (auxiliar)
    {
        if (auxiliar->origen == buscado || auxiliar->llegada == buscado)
        {
            return auxiliar->subruta;
        }
        auxiliar = auxiliar->siguiente;
    }
    return -1; // -1 = no encontrado
}

bool Ruta::existeRuta(Vertice *nodo1, Vertice *nodo2) // Para verificar que no se haga un ciclo
{
    // Si ambos existen (subruta != -1), existe una ruta entre ambos si su número de subruta es el mismo
    int subrutas[2] = {numeroDeSubruta(nodo1), numeroDeSubruta(nodo2)};
    return ((subrutas[0] == subrutas[1]) && (subrutas[0] != -1));
}

// CONECTAR SUBRUTAS

int Ruta::buscarSubrutas(Vertice *nodo1, Vertice *nodo2)
{
    // Si encuentra más de una ruta con estos nodos, se pueden unir en una sola

    if (!primero)
    {
        return ultimaSubruta;
    }

    int subrutas[2] = {-1, -1};

    NodoRuta *auxiliar = primero;
    while (auxiliar && (subrutas[0] == -1 || subrutas[1] == -1))
    {
        // En caso de que no se hayan encontrado dos subrutas por conectar aún
        // O sea, aún se cumple lo siguiente: subrutas[0] == -1 || subrutas[1] == -1
        if (auxiliar->subruta != -1 && auxiliar->conectable(nodo1, nodo2))
        {
            // Si auxiliar->subruta == 1, entonces es el nodo nuevo y no se toma en cuenta
            if (subrutas[0] == -1)
            {
                subrutas[0] = auxiliar->subruta;
            }
            else
            {
                if (auxiliar->subruta != subrutas[0])
                {
                    // No agrega dos veces la misma subruta al arreglo
                    subrutas[1] = auxiliar->subruta;
                }
            }
        }
        auxiliar = auxiliar->siguiente;
    }

    if (subrutas[0] == -1 && subrutas[1] == -1)
    {
        // Si no se encontró ninguna subruta conectable a la nueva,
        // entonces hay que crear una nueva
        ultimaSubruta++;
        return ultimaSubruta;
    }
    else
    {
        if (subrutas[1] != -1)
        {
            // Encontró dos subrutas. Borra la segunda primero (para que se una a la primera)
            if (subrutas[0] > subrutas[1])
            {
                // Se asegura de que el menor quede de primero en el arreglo
                int temporal = subrutas[0];
                subrutas[0] = subrutas[1];
                subrutas[1] = temporal;
            }
            unirSubrutas(subrutas[0], subrutas[1]);
        }
        return subrutas[0];
    }
}

void Ruta::unirSubrutas(int subruta1, int subruta2)
{
    // Resta 1 de todos los nodos cuya subruta > subruta2 indicada
    // Si nodo->subruta == subruta2, lo reemplaza con subruta1
    // Presume que subruta1 < subruta2
    if (subruta1 == -1 || subruta2 == -1)
    {
        return;
    }
    NodoRuta *auxiliar = primero;
    bool encontrado = false;

    while (auxiliar)
    {
        if (auxiliar->subruta > subruta2)
        {
            encontrado = true;
            auxiliar->subruta--;
        }
        else
        {
            if (auxiliar->subruta == subruta2)
            {
                auxiliar->subruta = subruta1;
            }
        }
        auxiliar = auxiliar->siguiente;
    }

    if (encontrado)
    {
        // Si se restó el número de subruta de alguna, este también disminuyó
        ultimaSubruta--;
    }
}

// IMPRIMIR

void Ruta::imprimir(std::string titulo, bool imprimirSuma)
{
    std::string reporte = "";
    int contador = 1, pesoTotal = 0;

    if (primero)
    {
        NodoRuta *auxiliar = primero;
        std::cout << "\n\t[INFO]\t\t" << titulo << ":\n\n";
        reporte += "\n\t[INFO]\t\t";
        reporte += titulo;
        reporte += ":\n\n";
        while (auxiliar)
        {
            std::cout << "\t\t\t" << contador
                      << ".\t[" << auxiliar->origen->codigoCarrera
                      << "] <-> [" << auxiliar->llegada->codigoCarrera
                      << "]\tPeso: " << auxiliar->peso
                      << "  \tSubruta: " << auxiliar->subruta << "\n";
            
            reporte += "\t\t\t";
            reporte += std::to_string(contador);
            reporte += ".\t[";
            reporte += std::to_string(auxiliar->origen->codigoCarrera);
            reporte += "] <-> [";
            reporte += std::to_string(auxiliar->llegada->codigoCarrera);
            reporte += "]\t\tPeso: ";
            reporte += std::to_string(auxiliar->peso);
            reporte += "\n";
            
            contador++;
            pesoTotal = pesoTotal + auxiliar->peso;
            auxiliar = auxiliar->siguiente;
        }
    }
    else
    {
        std::cout << "\n\t[INFO]\t\t" << titulo << ":\tNo hay elementos.\n";
        reporte = "\n\t[INFO]\t\t";
        reporte += titulo;
        reporte += ":\tNo hay elementos.\n";
    }

    if (imprimirSuma)
    {
        std::cout << "\n\t\t\tSuma:\t" << pesoTotal << "\n";
        reporte += "\n\t\t\tSuma:\t";
        reporte += std::to_string(pesoTotal);
        reporte += "\n";
    }

    ReporteEnArchivo::archivoDeReportes->escribir(reporte);
}