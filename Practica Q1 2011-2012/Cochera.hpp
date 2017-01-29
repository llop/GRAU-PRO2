/** @file Cochera.hpp
 *  @brief Especificacion de la clase Cochera
 */
#ifndef COCHERA_HPP
#define COCHERA_HPP

#include <stack>
#include <queue>

#include "utils.PRO2"

/*
 * Clase Cochera
 */
/** @class Cochera
 *  @brief Representa una cochera
 *  Una cochera se caracteriza por una via muerta donde poner los vagones de un tren, y la capacidad de esta.
 */
class Cochera {
private:
  /** @brief Capacidad de la via muerta. */
  int _capacidad;

  /** @brief Via muerta de la cochera. */
  stack<int> _via_muerta;
  /** @brief Retorna la profundidad a la que se encuentra vagon en la pila.
   *  \pre cierto
   *  \post Retorna la profundidad.
   */
  int cuenta_movimientos(int vagon, stack<int> &via, int profundidad);

  /** @brief Mueve vagones desde la via1 hasta la via2, hasta encontrar 'vagon' en la via1.
   *  \pre cierto
   *  \post La via auxiliar tiene los vagones que habia en la muerta hasta 'vagon'.
   */
  void mueve_de_via_a_via(int vagon, stack<int> &via1, stack<int> &via2, int tipo_movimiento);

  /** @brief Mueve vagones desde la via muerta hasta la auxiliar, hasta encontrar 'vagon' en la via muerta.
   *  \pre cierto
   *  \post La via auxiliar tiene los vagones que habia en la muerta hasta 'vagon'.
   */
  void mueve_desde_via_muerta(int vagon, stack<int> &via_auxiliar);

  /** @brief Mueve vagones desde la via auxiliar hasta la muerta, hasta encontrar 'vagon' en la via auxiliar.
   *  \pre cierto
   *  \post La via muerta tiene los vagones que habia en la auxiliar hasta 'vagon'.
   */
  void mueve_desde_via_auxiliar(int vagon, stack<int> &via_auxiliar);

  /** @brief Escribe los vagones en la via muerta por orden de antiguedad utilizando recursividad.
   *  \pre cierto
   *  \post Los vagones en la via muerta se han escrito en el canal estandar de salida.
   */
  void escribir_cochera_recursivo(stack<int> &via_muerta);
public:

  /* Constructora */
  /** @brief Creadora por defecto.
   *  \pre cierto
   *  \post El resultado es una cochera sin datos.
   */
  Cochera();
  /* Consultoras */
  /** @brief Devuelve cuantos huecos quedan en la via muerta.
   *  \pre cierto
   *  \post Retorna la capacidad.
   */
  int get_espacios_libres() const;

  /* Modificadoras */
  /** @brief Forma el tren cuyos vagones estan 'vagones'.
   *  Los movimientos ejecutados para formar los vagones encontrados en la cochera se escriben en el canal estandar de salida.
   *  \pre cierto
   *  \post Los vagones del tren encontrados se han quitado de la cochera.
   */
  void formar_tren(queue<int> &vagones, stack<int> &via_auxiliar);

  /** @brief Anade los vagones a la via muerta.
   *  \pre cierto
   *  \post Los vagones estan en la via muerta.
   */
  void anadir_vagones(queue<int> &vagones);
  /** @brief Anade los vagones a la via muerta. La via auxiliar queda vacia.
   *  \pre cierto
   *  \post Los vagones estan en la via muerta, y la auxiliar esta vacia.
   */

  void anadir_vagones(stack<int> &via_auxiliar);
  /* Lectura y escritura */
  /** @brief Se leen los datos de la cochera del canal estandar de entrada.
   *  \pre cierto
   *  \post Los datos del parametro implicito son los leidos de la entrada.
   */
  void leer_cochera();

  /** @brief Escribe los vagones en la via muerta por orden de antiguedad.
   *  \pre cierto
   *  \post Los vagones en la via muerta se han escrito en el canal estandar de salida.
   */
  void escribir_cochera();
};
#endif