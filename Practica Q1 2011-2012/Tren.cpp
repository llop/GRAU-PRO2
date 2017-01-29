/** @file Tren.cpp
 *  @brief Implementacion de la clase Tren
 */
#include "Tren.hpp"

/* Clase Tren
 * Representa un tren
 * Los atributos de un tren son su identificador, la hora en que empieza su ultimo viaje del dia, 
 * cuanto tarda en recorrerlo, y sus vagones (cada vagon se representa con un entero que indica su tipo -pasajeros, bar, ...).
 */

/* Constructora */
/** @brief Creadora por defecto
 *  \pre cierto
 *  \post El resultado es un tren sin datos.
 */
Tren::Tren() {
}

/* Consultoras */
/** @brief Devuelve el identificador del tren.
 *  \pre cierto
 *  \post Retorna el id.
 */
int Tren::get_id() const {
  return _id;
}

/** @brief Devuelve la hora de llegada del ultimo tren.
 *  \pre cierto
 *  \post Retorna la hora de llegada.
 */
int Tren::get_hora_llegada() const {
  return _hora_llegada;
}

/** @brief Devuelve los vagones del tren.
 *  \pre cierto
 *  \post Retorna un vector de vagones.
 */
queue<int> Tren::get_vagones() const {
  return _vagones;
}

/* Modificadoras */
/** @brief Establece la hora de llegada del ultimo tren.
 *  \pre cierto
 *  \post La hora de llegada es 'hora_llegada'.
 */
void Tren::set_hora_llegada(int hora_llegada) {
  _hora_llegada = hora_llegada;
}

/** @brief Establece los vagones del tren.
 *  \pre cierto
 *  \post La cola de vagones es 'vagones'.
 */
void Tren::set_vagones(queue<int> &vagones) {
  _vagones = vagones;
}

/* Lectura */
/** @brief Se leen los datos del tren del canal estandar de entrada.
 *  \pre cierto
 *  \post Los datos del parametro implicito son los leidos de la entrada.
 */
void Tren::leer_tren() {
  _id = readint();

  int num_vagones = readint();
  _vagones = queue<int>();

  for (int i = 0; i < num_vagones; i++) {

    int vagon = readint();
    _vagones.push(vagon);
  }
}