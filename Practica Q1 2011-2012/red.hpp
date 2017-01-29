/** @file Red.hpp
 *  @brief Especificacion de la clase Red
 */
#ifndef RED_HPP
#define RED_HPP

#include <vector>
#include "Arbre.hpp"
#include "utils.PRO2"


/*
 * Clase Red
 */
/** @class Red
 *  @brief Representa una red
 *  La red tiene una estructura de arbol binario completo de n niveles, en que cada nodo representa una estacion.
 */
class Red {
private:
  /** @brief Contiene los tiempos entre cada estacion y la central. */
  vector<int> _estaciones;

  /** @brief Se leen los datos de las etaciones de la red del canal estandar de entrada.
   *  Cada estacion tiene un tiempo; se debe leer la red como un arbol en preorden.
   *  \pre cierto
   *  \post Los datos del parametro implicito son los leidos de la entrada
   */
  void leer_red_recursivo(Arbre<int> &a, vector<int> &estaciones, int id_estacion, int tiempo_acumulado);

public:
  /* Constructora */
  /** @brief Creadora por defecto
   *  \pre cierto
   *  \post El resultado es una red vacia.
   */
  Red();
  /* Modificadoras */
  /** @brief Devuelve el tiempo que hay entre la estacion con id 'id_estacion' y la estacion central.
   *  \pre id_estacion pertenece a una estacion valida.
   *  \post Retorna el tiempo entre la estacion indicada y su padre
   */
  int get_tiempo_estacion(int id_estacion) const;

  /* Lectura */
  /** @brief Se leen los datos de las etaciones de la red del canal estandar de entrada.
   *  \pre cierto
   *  \post Los datos del parametro implicito son los leidos de la entrada
   */
  void leer_red();
};
#endif