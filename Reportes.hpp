#ifndef REPORTES_HPP
#define REPORTES_HPP

#include <string>
#include <fstream>
#include <iostream>

class Reportes
{
private:
    bool yaHay;

public:
    // CONSTRUCTOR
    Reportes();

    // ESCRIBIR
    void escribir(std::string porEscribir);
};

namespace ReporteEnArchivo
{
    const std::string rutaDeSalida = "SalidaReportes.txt";
    extern Reportes *archivoDeReportes;
}

#endif