#include "Reportes.hpp"

namespace ReporteEnArchivo
{
    Reportes *archivoDeReportes = NULL;
}

Reportes::Reportes()
{
    ReporteEnArchivo::archivoDeReportes = this;
    yaHay = false;
}

void Reportes::escribir(std::string porEscribir)
{
    std::ofstream archivoSalida;
    if (yaHay)
    {
        // Aquí hará "append" (añade al final)
        archivoSalida.open(ReporteEnArchivo::rutaDeSalida, std::ios_base::app);
        if(!archivoSalida.is_open())
        {
            std::cout << "\t[ERROR]\t\tError abriendo archivo de reportes existente. Creando nuevo.\n";
            yaHay = false;
            escribir(porEscribir);
            return;
        }
    }
    else
    {
        // Aquí sobreescribiría el archivo
        archivoSalida.open(ReporteEnArchivo::rutaDeSalida);
        yaHay = true;
        if(!archivoSalida.is_open())
        {
            std::cout << "\t[ERROR]\t\tError creando archivo de reportes.\n";
            return;
        }
    }
    archivoSalida << porEscribir;
}