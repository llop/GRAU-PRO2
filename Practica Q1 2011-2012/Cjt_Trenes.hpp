/** @file Cjt_Trenes.cpp
 *  @brief Implementacion de la clase Cjt_Trenes
 */
#include "Cjt_Trenes.hpp"

/* Clase Cjt_Trenes
 * Representa el conjunto de trenes
 */
  
/* Constructora */
/** @brief Creadora por defecto.
 *  \pre cierto
 *  \post El resultado es un conjunto de trenes vacio.
 */
Cjt_Trenes::Cjt_Trenes() {
}

/* Modificadoras */
/** @brief Anade el tren indicado al conjunto; si ya existe un tren con el mismo identificador, sus datos se sobreescriben.
 *  \pre cierto
 *  \post 'tren' forma parte del conjunto.
 */
void Cjt_Trenes::set_tren(Tren &tren) {
  bool found = false;

  int id_tren = tren.get_id();
  list<Tren>::iterator it = _trenes.begin();

  while (it != _trenes.end() and it->get_id() <= id_tren and not found) {

    if (it->get_id() == id_tren) {
      queue<int> vagones = tren.get_vagones();

      it->set_vagones(vagones);
      found = true;
    } else ++it;
  }

  if (not found) _trenes.insert(it, tren);
}

/* Consultoras */
/** @brief Devuelve el tren con id 'id_tren'. 
 *  \pre El tren pertenece al conjunto.
 *  \post Retorna el tren indicado.
 */
Tren Cjt_Trenes::get_tren(int id_tren) const {
  Tren tren;

  bool loop = true;
  list<Tren>::const_iterator it = _trenes.begin();

  while (it != _trenes.end() and loop) {

    if (it->get_id() == id_tren) {
      tren = *it;

      loop = false;
    } else ++it;
  }
  return tren;
}

/* Lectura */
/** @brief Se leen los datos de los trenes del canal estandar de entrada
 *  \pre cierto
 *  \post Los datos de los trenes son los leidos de la entrada
 */
void Cjt_Trenes::leer_trenes() {
  int num_trenes = readint();

  for (int i = 0; i < num_trenes; i++) 
    leer_tren();
}

/** @brief Se leen los datos de un tren del canal estandar de entrada, y: se anade al conjunto si en este no hay otro tren con el mismo 'id'; si lo hay, se machacan sus datos.
 *  \pre cierto
 *  \post El tren descrito forma parte del conjunto.
 */
void Cjt_Trenes::leer_tren() {
  Tren tren;
  tren.leer_tren();

  set_tren(tren);
}