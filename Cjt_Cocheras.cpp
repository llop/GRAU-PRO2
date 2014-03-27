/** @file Cjt_Cocheras.cpp
 *  @brief Implementacion de la clase Cjt_Cocheras
 */
#include "Cjt_Cocheras.hpp"

/* Clase Cjt_Cocheras
 * Representa un conjunto de cocheras
 */

/* Constructora */
/** @brief Creadora
 *  M es el numero de cocheras.
 *  \pre M > 0
 *  \post El resultado es un conjunto de M cocheras.
 */

Cjt_Cocheras::Cjt_Cocheras(int M) {
  _cocheras = vector<Cochera>(M);

  _prioridades = vector<int>(M);
}
/* Modificadoras */
/** @brief Realiza el almacenamiento nocturno de trenes en el conjunto proporcionado.
 *  Se informara de los trenes y sus respectivas horas de salida por el canal estandar de entrada.
 *  \pre cierto
 *  \post Las cocheras contienen los vagones de los trenes indicados.
 */
void Cjt_Cocheras::almacenamiento_nocturno(const Red &red, Cjt_Trenes &trenes) {

  list<Tren> trenes_almacenamiento = get_trenes_almacenamiento_nocturno(red, trenes);
  escribir_llegadas(trenes_almacenamiento);

  rellena_cocheras(trenes_almacenamiento);
}
/** @brief Rellena las cocheras con los vagones de los trenes, siguiendo la politica descrita en el enunciado.
 *  Se informara de los trenes y sus respectivas horas de salida por el canal estandar de entrada.
 *  \pre La lista de cocheras esta ordenada por prioridad, y la de trenes por hora de llegada. Todos los trenes caben en las cocheras.
 *  \post Las cocheras contienen los vagones de los trenes indicados.
 */
void Cjt_Cocheras::rellena_cocheras(const list<Tren> &trenes) {

  for (list<Tren>::const_iterator it_t = trenes.begin(); it_t != trenes.end(); ++it_t) {

    bool almacenado = false;
    queue<int> vagones = it_t->get_vagones();

    for (int i = 0; i < _cocheras.size() and not almacenado; i++) {

      int espacios_libres = _cocheras[_prioridades[i]].get_espacios_libres();
      if (vagones.size() <= espacios_libres) {

	_cocheras[_prioridades[i]].anadir_vagones(vagones);
        almacenado = true;
      }
    }
  }
}

/** @brief Escribe las horas de llegada de los trenes en el canal estandar de salida
 *  \pre Los trenes deben haber realizado su ultimo viaje
 *  \post Las horas de llegada se han escrito en el canal estandar de salida
 */
void Cjt_Cocheras::escribir_llegadas(list<Tren> &trenes) const {

  cout << "Horarios para el almacenamiento nocturno" << endl;
  for (list<Tren>::iterator it = trenes.begin(); it != trenes.end(); ++it) {

    int tiempo = it->get_hora_llegada();
    int hora = (tiempo / 60) % 24;

    int minuto = tiempo % 60;
    cout << "Tren " << it->get_id() << ' ' << "H. " << hora << " M. " << minuto << endl;
  }

  cout << endl;
}
/** @brief Funcion auxiliar para realizar la ordenacion de los trenes por hora de llegada.
 *  \pre cierto
 *  \post El resultado indica si el primer tren deberia ir antes que el segundo.
 */
bool sort_hora_llegada(const Tren &tren1, const Tren &tren2) {

  int hora_llegada_tren1 = tren1.get_hora_llegada();
  int hora_llegada_tren2 = tren2.get_hora_llegada();

  bool ret = hora_llegada_tren1 < hora_llegada_tren2;
  if (hora_llegada_tren1 == hora_llegada_tren2) ret = tren1.get_id() < tren2.get_id();

  return ret;
}
/** @brief Lee las horas de salida de los trenes para el almacenamiento nocturno del canal estandar de entrada, y devuelve una lista con esos trenes ordenada por hora de llegada.
 *  \pre cierto
 *  \post Retorna una lista de los trenes indicados ordenada por hora de llegada.
 */
list<Tren> Cjt_Cocheras::get_trenes_almacenamiento_nocturno(const Red &red, Cjt_Trenes &trenes) const {

  list<Tren> trenes_almacenamiento;
  int num_trenes = readint();

  for (int i = 0; i < num_trenes; i++) {

    int id_tren = readint();
    int hora = readint();

    int minuto = readint();
    int hora_salida = hora * 60 + minuto;

    int hora_llegada = hora_salida + red.get_tiempo_estacion(id_tren);

    Tren tren = trenes.get_tren(id_tren);
    tren.set_hora_llegada(hora_llegada);

    trenes_almacenamiento.insert(trenes_almacenamiento.end(), tren);
  }
  trenes_almacenamiento.sort(sort_hora_llegada);

  return trenes_almacenamiento;
}
/** @brief Realiza la formacion matinal de trenes pertenecientes al conjunto proporcionado que salen un dia.
 *  Se informara de que trenes salen por el canal estandar de entrada.
 *  \pre Las cocheras se han llenado en una almacenamiento nocturno.
 *  \post Se han formado los trenes indicados con los vagones de las cocheras.
 */
void Cjt_Cocheras::formacion_matinal(Cjt_Trenes &trenes) {

  list<Tren> trenes_formacion = get_trenes_formacion_matinal(trenes);
  vacia_cocheras(trenes_formacion);
}

/** @brief Forma los trenes indicados con los vagones de las vias de las cocheras.
 *  Al terminar, las cocheras quedan sin los vagones que se utilizaron para los trenes.
 *  Los movimientos para formar los trenes se escriben en el canal estandar de salida.
 *  \pre Se garantiza que los trenes se podran formar porque todos sus vagones estan en las cocheras.
 *  \post Se han formado los trenes indicados con los vagones de las cocheras.
 */
void Cjt_Cocheras::vacia_cocheras(list<Tren> &trenes) {
  stack<int> via_auxiliar;

  cout << "Movimientos para la formacion matinal" << endl;
  for (list<Tren>::iterator it = trenes.begin(); it != trenes.end(); ++it) {

    cout << "  Tren " << it->get_id() << " :" << endl;

    queue<int> vagones = it->get_vagones();
    for (int i = 0; i < _cocheras.size() and not vagones.empty(); i++) {

      cout << "    Cochera " << (_prioridades[i] + 1) << " : ";

      _cocheras[_prioridades[i]].formar_tren(vagones, via_auxiliar);
      _cocheras[_prioridades[i]].anadir_vagones(via_auxiliar);

      cout << endl;
    }
  }
  cout << endl;
}

/** @brief Se leen los trenes para la formacion matinal del canal estandar de entrada.
 *  \pre cierto
 *  \post Retorna una lista con los trenes.
 */
list<Tren> Cjt_Cocheras::get_trenes_formacion_matinal(Cjt_Trenes &trenes) const {

  list<Tren> trenes_formacion;
  int num_trenes = readint();

  for (int i = 0; i < num_trenes; i++) {

    int id_tren = readint();
    Tren tren = trenes.get_tren(id_tren);

    trenes_formacion.insert(trenes_formacion.end(), tren);
  }
  return trenes_formacion;
}

/* Lectura y escritura */
/** @brief Se leen los datos de las cocheras de la red del canal estandar de entrada.
 *  \pre cierto
 *  \post Los datos del parametro implicito son los leidos de la entrada.
 */
void Cjt_Cocheras::leer_cocheras() {
  for (int i = 0; i < _cocheras.size(); i++) {

    _cocheras[i].leer_cochera();
    int prioridad = readint();

    _prioridades[prioridad - 1] = i;
  }
}
/** @brief Escritura de las cocheras.
 *  \pre cierto
 *  \post Los datos de las cocheras se han escrito en el canal estandar de salida.
 */
void Cjt_Cocheras::escribir_cocheras() {

  cout << "Cocheras" << endl;
  for (int i = 0; i < _cocheras.size(); i++) {

    cout << (i + 1) << " : ";
    _cocheras[i].escribir_cochera();

    cout << endl;
  }
  cout << endl;
}