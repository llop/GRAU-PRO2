/** @file Cjt_Cocheras.hpp
 *  @brief Especificacion de la clase Cjt_Cocheras
 */
#ifndef CJT_COCHERAS_HPP
#define CJT_COCHERAS_HPP

#include "Cjt_Trenes.hpp"
#include "Cochera.hpp"
#include "utils.PRO2"

/*
Clase Cjt_Cocheras
*/
/** @class Cjt_Cocheras
 *  @brief Representa un conjunto de cocheras
 */
class Cjt_Cocheras {

private:
  /** @brief Lista de cocheras. */
  vector<Cochera> _cocheras;
  /** @brief Lista de cocheras. */
  vector<int> _prioridades;

  /* Metodos almacenamiento nocturno */
  /** @brief Lee las horas de salida de los trenes para el almacenamiento nocturno del canal estandar de entrada, y devuelve una lista con esos trenes ordenada por hora de llegada.
   *  \pre cierto
   *  \post Retorna una lista de los trenes indicados ordenada por hora de llegada.
   */
  list<Tren> get_trenes_almacenamiento_nocturno(const Red &red, Cjt_Trenes &trenes) const;

  /** @brief Escribe las horas de llegada de los trenes de la lista en el canal estandar de salida.
   *  \pre Los trenes deben haber realizado su ultimo viaje.
   *  \post Las horas de llegada se han escrito en el canal estandar de salida.
   */
  void escribir_llegadas(list<Tren> &trenes) const;

  /** @brief Rellena las cocheras con los vagones de los trenes, siguiendo la politica descrita en el enunciado.
   *  Se informara de los trenes y sus respectivas horas de salida por el canal estandar de entrada.
   *  \pre La lista de cocheras esta ordenada por prioridad, y la de trenes por hora de llegada. Todos los trenes caben en las cocheras.
   *  \post Las cocheras contienen los vagones de los trenes indicados.
   */
  void rellena_cocheras(const list<Tren> &trenes);
  /* Metodos formacion matinal */
  /** @brief Se leen los trenes para la formacion matinal del canal estandar de entrada.
   *  \pre cierto
   *  \post Retorna una lista con los trenes.
   */

  list<Tren> get_trenes_formacion_matinal(Cjt_Trenes &trenes) const;
  /** @brief Forma los trenes indicados con los vagones de las vias de las cocheras.
   *  Al terminar, las cocheras quedan sin los vagones que se utilizaron para los trenes.
   *  Los movimientos para formar los trenes se escriben en el canal estandar de salida.
   *  \pre Se garantiza que los trenes se podran formar porque todos sus vagones estan en las cocheras.
   *  \post Se han formado los trenes indicados con los vagones de las cocheras.
   */

  void vacia_cocheras(list<Tren> &trenes);
public:
  /* Constructora */
  /** @brief Creadora
   *  M es el numero de cocheras.
   *  \pre M > 0
   *  \post El resultado es un conjunto de M cocheras.
   */

  Cjt_Cocheras(int M);
  /* Modificadoras */
  /** @brief Realiza el almacenamiento nocturno de trenes en el conjunto proporcionado.
   *  Se informara de los trenes y sus respectivas horas de salida por el canal estandar de entrada.
   *  \pre cierto
   *  \post Las cocheras contienen los vagones de los trenes indicados.
   */
  void almacenamiento_nocturno(const Red &red, Cjt_Trenes &trenes);

  /** @brief Realiza la formacion matinal de trenes pertenecientes al conjunto proporcionado que salen un dia.
   *  Se informara de que trenes salen por el canal estandar de entrada.
   *  \pre Las cocheras se han llenado en una almacenamiento nocturno.
   *  \post Se han formado los trenes indicados con los vagones de las cocheras.
   */
  void formacion_matinal(Cjt_Trenes &trenes);
  /* Lectura y escritura */
  /** @brief Se leen los datos de las cocheras de la red del canal estandar de entrada.
   *  \pre cierto
   *  \post Los datos del parametro implicito son los leidos de la entrada.
   */
  void leer_cocheras();

  /** @brief Escritura de las cocheras.
   *  \pre cierto
   *  \post Los datos de las cocheras se han escrito en el canal estandar de salida.
   */
  void escribir_cocheras();
};
#endif