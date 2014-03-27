/** @file Tren.hpp
 *  @brief Especificacion de la clase Tren
 */
#ifndef TREN_HPP
#define TREN_HPP

#include <queue>
#include "utils.PRO2"


/*
 * Clase Tren
 */
/** @class Tren
 *  @brief Representa un tren
 *  Los atributos de un tren son su identificador, la hora en que empieza su ultimo viaje del dia, cuanto tarda en recorrerlo, y sus vagones (cada vagon se representa con un entero que indica su tipo -pasajeros, bar, ...).
 */
class Tren {
private:
  /** @brief Identificador unico del tren. */
  int _id;

  /** @brief Hora de llegada del ultimo viaje del tren. */
  int _hora_llegada;
  /** @brief Contiene los vagones que conforman el tren. */
  queue<int> _vagones;

public:
  /* Constructora */
  /** @brief Creadora por defecto
   *  \pre cierto
   *  \post El resultado es un tren sin datos.
   */
  Tren();
  /* Consultoras */
  /** @brief Devuelve el identificador del tren.
   *  \pre cierto
   *  \post Retorna el id.
   */
  int get_id() const;

  /** @brief Devuelve la hora de llegada del ultimo tren.
   *  \pre cierto
   *  \post Retorna la hora de llegada.
   */
  int get_hora_llegada() const;
  /** @brief Devuelve los vagones del tren.
   *  \pre cierto
   *  \post Retorna un vector de vagones.
   */
  queue<int> get_vagones() const;

  /* Modificadoras */
  /** @brief Establece la hora de llegada del ultimo tren.
   *  \pre cierto
   *  \post La hora de llegada es 'hora_llegada'.
   */
  void set_hora_llegada(int hora_llegada);
  /** @brief Establece los vagones del tren.
   *  \pre cierto
   *  \post La cola de vagones es 'vagones'.
   */
  void set_vagones(queue<int> &vagones);

  /* Lectura */
  /** @brief Se leen los datos del tren del canal estandar de entrada.
   *  \pre cierto
   *  \post Los datos del parametro implicito son los leidos de la entrada.
   */
  void leer_tren();
};
#endif