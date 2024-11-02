#include <iostream>
#include "Grafo.h"

int main() {
    // Crear una instancia del grafo
    Grafo<std::string> redSocial;

    // Cargar las relaciones desde un archivo
    std::string archivoRelaciones = "./taller_4_archivos/personasMias.txt"; // Archivo de entrada con relaciones de amistad
    redSocial.cargarRelacionesDesdeArchivo(archivoRelaciones);

    // Imprimir la lista de vértices y aristas para confirmar la carga de datos
    std::cout << "Vertices en la red social: ";
    redSocial.plano();

    // Evaluar los pares de personas para verificar la teoría de los 6 grados de separación
    std::string archivoPares = "./taller_4_archivos/testMias.txt"; // Archivo de entrada con pares a evaluar
    std::string archivoResultado = "resultado.txt";   // Archivo de salida con los resultados de la evaluación
    redSocial.evaluarGradosDeSeparacion(archivoPares, archivoResultado);

    std::cout << "Evaluación completada. Revisa el archivo de resultados: " << archivoResultado << std::endl;

    return 0;
}