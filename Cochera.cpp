/** @file Cochera.cpp
 *  @brief Implementacion de la clase Cochera
 */
#include "Cochera.hpp"

/* Clase Cochera
 * Representa una cochera
 * Una cochera se caracteriza por una via muerta donde poner los vagones de un tren, y la capacidad de esta.
 */

/* Constructora */
/** @brief Creadora por defecto.
 *  \pre cierto
 *  \post El resultado es una cochera sin datos.
 */
Cochera::Cochera() {
}

/* Consultoras */
/** @brief Devuelve cuantos huecos quedan en la via muerta.
 *  \pre cierto
 *  \post Retorna la capacidad.
 */
int Cochera::get_espacios_libres() const {
  return _capacidad - _via_muerta.size();
}

/* Modificadoras */
/** @brief Anade los vagones a la via muerta.
  *  \pre cierto
  *  \post Los vagones estan en la via muerta.
  */
void Cochera::anadir_vagones(queue<int> &vagones) {
  while (not vagones.empty()) {

    _via_muerta.push(vagones.front());
    vagones.pop();
  }
}
/** @brief Anade los vagones a la via muerta. La via auxiliar queda vacia.
 *  \pre cierto
 *  \post Los vagones estan en la via muerta, y la auxiliar esta vacia.
 */

void Cochera::anadir_vagones(stack<int> &via_auxiliar) {
  while (not via_auxiliar.empty()) {

    _via_muerta.push(via_auxiliar.top());
    via_auxiliar.pop();
  }
}
/** @brief Forma el tren cuyos vagones estan 'vagones'.
 *  Los movimientos ejecutados para formar los vagones encontrados en la cochera se escriben en el canal estandar de salida.
 *  \pre cierto
 *  \post Los vagones del tren encontrados se han quitado de la cochera.
 */

void Cochera::formar_tren(queue<int> &vagones, stack<int> &via_auxiliar) {

  bool no_hay_mas = false;
  while (not vagones.empty() and (not _via_muerta.empty() or not via_auxiliar.empty()) and not no_hay_mas) {

    int vagon = vagones.front();
    // Cuenta de los movimientos necesarios para llegar al vagon buscado en ambas vias
    int movimientos_via_muerta = cuenta_movimientos(vagon, _via_muerta, 0);

    int movimientos_via_auxiliar = cuenta_movimientos(vagon, via_auxiliar, 0);

    // booleanos para controlar la accion
    bool via_muerta_tiene = movimientos_via_muerta < _via_muerta.size();

    bool via_auxiliar_tiene = movimientos_via_auxiliar < via_auxiliar.size();
    if (via_muerta_tiene or via_auxiliar_tiene) {

      // Si ambas vias tienen el vagon, hay que pillarlo de la que menos movimientos se necesiten; si no, de la que lo tenga
      // Hay que sumar 1 a los movimientos de la via auxiliar porque hay que contar el movimiento de pasar el vagon a la via muerta
      bool ambas_tienen = via_muerta_tiene and via_auxiliar_tiene;
      if ((ambas_tienen and movimientos_via_muerta < movimientos_via_auxiliar + 1) or

	  (via_muerta_tiene and not via_auxiliar_tiene))
	mueve_desde_via_muerta(vagon, via_auxiliar);

      else mueve_desde_via_auxiliar(vagon, via_auxiliar);
      vagones.pop();
    } else no_hay_mas = true;
  }
}

/** @brief Retorna la profundidad a la que se encuentra vagon en la pila.
 *  \pre cierto
 *  \post Retorna la profundidad.
 */
int Cochera::cuenta_movimientos(int vagon, stack<int> &via, int profundidad) {

  int cuenta = profundidad;
  if (not via.empty()) {

    int vagon_via = via.top();
    if (vagon != vagon_via) {

      via.pop();
      cuenta = cuenta_movimientos(vagon, via, profundidad + 1);

      via.push(vagon_via);
    }
  }
  return cuenta;
}
/** @brief Mueve vagones desde la via1 hasta la via2, hasta encontrar 'vagon' en la via1.
 *  \pre cierto
 *  \post La via auxiliar tiene los vagones que habia en la muerta hasta 'vagon'.
 */
void Cochera::mueve_de_via_a_via(int vagon, stack<int> &via1, stack<int> &via2, int tipo_movimiento) {

  while (via1.top() != vagon) {
    via2.push(via1.top());

    cout << tipo_movimiento << " " << via1.top() << "  ";

    via1.pop();
  }
}
/** @brief Mueve vagones desde la via muerta hasta la auxiliar, hasta encontrar 'vagon' en la via muerta.
 *  \pre cierto
 *  \post La via auxiliar tiene los vagones que habia en la muerta hasta 'vagon'.
 */
void Cochera::mueve_desde_via_muerta(int vagon, stack<int> &via_auxiliar) {

  mueve_de_via_a_via(vagon, _via_muerta, via_auxiliar, 2);
  cout << "1 " << _via_muerta.top() << "  ";

  _via_muerta.pop();
}
/** @brief Mueve vagones desde la via auxiliar hasta la muerta, hasta encontrar 'vagon' en la via auxiliar.
 *  \pre cierto
 *  \post La via muerta tiene los vagones que habia en la auxiliar hasta 'vagon'.
 */
void Cochera::mueve_desde_via_auxiliar(int vagon, stack<int> &via_auxiliar) {

  mueve_de_via_a_via(vagon, via_auxiliar, _via_muerta, 3);
  cout << "3 " << via_auxiliar.top() << "  1 " << via_auxiliar.top() << "  ";

  via_auxiliar.pop();
}
/* Lectura y escritura */
/** @brief Se leen los datos de la cochera del canal estandar de entrada.
 *  \pre cierto
 *  \post Los datos del parametro implicito son los leidos de la entrada.
 */
void Cochera::leer_cochera() {
  _capacidad = readint();
}

/** @brief Escribe los vagones en la via muerta por orden de antiguedad.
 *  \pre cierto
 *  \post Los vagones en la via muerta se han escrito en el canal estandar de salida.
 */
void Cochera::escribir_cochera() {
  escribir_cochera_recursivo(_via_muerta);
}
/** @brief Escribe los vagones en la via muerta por orden de antiguedad utilizando recursividad.
 *  \pre cierto
 *  \post Los vagones en la via muerta se han escrito en el canal estandar de salida.
 */

void Cochera::escribir_cochera_recursivo(stack<int> &via_muerta) {
  if (not via_muerta.empty()) {

    int vagon = via_muerta.top();
    via_muerta.pop();

    escribir_cochera_recursivo(via_muerta);
    cout << vagon << ' ';
    via_muerta.push(vagon);
  }
}