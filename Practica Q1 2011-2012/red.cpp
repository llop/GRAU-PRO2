/** @file Red.cpp
 *  @brief Implementacion de la clase Red
 */
#include "Red.hpp"

/* Clase Red
 * Representa una red
 * La red tiene una estructura de arbol binario completo de n niveles, en que cada nodo representa una estacion.
 */

/* Constructora */
/** @brief Creadora por defecto
 *  \pre cierto
 *  \post El resultado es una red vacia.
 */
Red::Red() {
}

/* Modificadoras */
/** @brief Devuelve el tiempo que hay entre la estacion con id 'id_estacion' y la estacion central.
 *  \pre id_estacion pertenece a una estacion valida.
 *  \post Retorna el tiempo entre la estacion indicada y su padre
 */
int Red::get_tiempo_estacion(int id_estacion) const {

  return _estaciones[id_estacion];
}

/* Lectura */
/** @brief Se leen los datos de las estaciones de la red del canal estandar de entrada.
 *  \pre cierto
 *  \post Los datos del parametro implicito son los leidos de la entrada
 */
void Red::leer_red() {

  int n = readint();
  int num_estaciones = (1 << n) - 1;  // por definicion

  _estaciones = vector<int>(num_estaciones);
  Arbre<int> a;

  leer_red_recursivo(a, _estaciones, 0, 0);
}

/** @brief Se leen los datos de las etaciones de la red del canal estandar de entrada.
 *  Cada estacion tiene un tiempo; se debe leer la red como un arbol en preorden.
 *  \pre cierto
 *  \post Los datos del parametro implicito son los leidos de la entrada
 */

void Red::leer_red_recursivo(Arbre<int> &a, vector<int> &estaciones, int id_estacion, int tiempo_acumulado) {

  int tiempo = readint();
  if (tiempo >= 0) {

    tiempo_acumulado += tiempo;
    estaciones[id_estacion] = tiempo_acumulado;

    Arbre<int> a1, a2;
    leer_red_recursivo(a1, estaciones, id_estacion * 2 + 1, tiempo_acumulado);

    leer_red_recursivo(a2, estaciones, id_estacion * 2 + 2, tiempo_acumulado);

    a.plantar(tiempo_acumulado, a1, a2);
  }
}