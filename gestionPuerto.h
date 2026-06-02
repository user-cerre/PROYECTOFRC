/**
 * Autores:
 * - Eduardo Cabello Gil
 * - Carlos Paredes Ruiz
 * Grupo de prácticas: Grupo 8 -- Jueves 10:00 - 11:30 h.
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "linkLayer.h"
#include "funcionesTramas.h"
#ifndef GESTIONPUERTO_H
#define GESTIONPUERTO_H
using namespace std;

/**
 * @brief Función que envía un carácter a través de la interfaz de red.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar la trama.
 * @param dato Carácter que se va a enviar.
 * @param mac_src MAC de origen que se va a usar en la trama.
 * @param mac_dst MAC de destino que se va a usar en la trama.
 * @param type Tipo de la trama que se va a enviar.
 */
void enviarCaracter(interface_t *iface, char dato, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type);

/**
 * @brief Función que recibe un carácter desde la interfaz de red.
 * @param iface Puntero a la interfaz de red que se va a usar para recibir la trama.
 * @return Carácter recibido.
 */
int recibirCaracter(interface_t *iface);

/**
 * @brief Función que envía un fichero a través de la interfaz de red.
 * @param iface Interfaz de red que se va a usar para enviar la trama.
 * @param mac_dst MAC de destino que se va a usar en la trama.
 * @param type Tipo de la trama que se va a enviar.
 */
void enviarFichero(interface_t *iface, unsigned char *mac_dst, unsigned char *type);
/**
 * @brief Función que envía una trama de control a través de la interfaz de red.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar la trama.
 * @param mac_dst MAC de destino que se va a usar en la trama.
 * @param type Tipo de la trama que se va a enviar.
 * @param control Valor del campo de control de la trama.
 * @param tramaN Número de la trama.
 * @param direccion Dirección de la trama.
 */
void enviarTramaDeControl(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int control, char tramaN, char direccion);
/**
 * @brief Función que envía una trama de datos a través de la interfaz de red.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar la trama.
 * @param mac_dst MAC de destino que se va a usar en la trama.
 * @param type Tipo de la trama que se va a enviar.
 * @param control Valor del campo de control de la trama.
 * @param tramaN Número de la trama.
 * @param direccion Dirección de la trama.
 * @param cad Cadena de caracteres que se va a enviar.
 * @param longitud Longitud de la cadena de caracteres.
 * @param e Indicador de error.
 */
void enviarTramaDeDatos(interface_t * iface, unsigned char *mac_dst, unsigned char *type, int control, char tramaN, char direccion, char *cad, int longitud, bool e);
/**
 * @brief Función que muestra por pantalla el contenido de una trama.
 * @param control Valor del campo de control de la trama.
 * @param tramaN Número de la trama.
 * @param direccion Dirección de la trama.
 */
void mostrarTrama(int control,int tramaN, int direccion);
#endif