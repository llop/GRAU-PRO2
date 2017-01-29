/** @mainpage Practica de PRO2: Red ferroviaria
 *  Se construye un programa modular que simula el funcionamiento de una red ferroviaria.
 */
/** @file main.cpp
 *  @brief Programa principal para la practica de PRO2: 'Red ferroviaria'.
 */
#include "Red.hpp"
#include "Cjt_Trenes.hpp"
#include "Cjt_Cocheras.hpp"
#include "utils.PRO2"

/** @brief Programa principal para la practica de PRO2: 'Red ferroviaria'. */
int main() {

  // Leer cuantas cocheras
  int M = readint();
  // Inicializar la red, las cocheras y los trenes
  Red red;

  red.leer_red();
  Cjt_Cocheras cocheras(M);
  cocheras.leer_cocheras();

  Cjt_Trenes trenes;
  trenes.leer_trenes();
  // Procesar las opciones
  int opcion = readint();

  while (opcion != -6) {
    if (opcion == -1) cocheras.almacenamiento_nocturno(red, trenes);

    else if (opcion == -2) cocheras.formacion_matinal(trenes);

    else if (opcion == -3) trenes.leer_tren();
    else if (opcion == -4) cocheras.leer_cocheras();

    else if (opcion == -5) cocheras.escribir_cocheras();
    opcion = readint();
  }

  return 0;
}