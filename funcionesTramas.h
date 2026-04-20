/**
 * Autores:
 * - Eduardo Cabello Gil
 * - Carlos Paredes Ruiz
 * Grupo de prácticas: Grupo 8 -- Jueves 10:00 - 11:30 h.
 */

#include "gestionPuerto.h"
#include "linkLayer.h"
#ifndef FUNCIONESTRAMAS_H
#define FUNCIONESTRAMAS_H
using namespace std;

/** 
 * @brief Calcula la trama BCE
 * @param iface iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino.
 */
unsigned char* calcularBCE(interface_t *iface, unsigned char *mac_dst);

bool establecimientoMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo);

void establecimientoEsclava(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo);

/**
 * @brief Función que implementa el envío de caracteres de forma interactiva. Permite al usuario introducir caracteres por teclado, y cada vez que se introduce un carácter, se envía una trama con ese carácter a la estación destino. Además, la función también recibe tramas de la estación destino, y muestra por pantalla el número de caracteres recibidos cada vez que se recibe una trama. El envío de caracteres se realiza hasta que el usuario pulse la tecla ESC (código ASCII 27).
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de descubrimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra y 02 para la estación esclava).
 */
void envioInteractivoCaracteres(interface_t *iface, unsigned char *mac_dst, unsigned char *type);

/**
 * @brief Función que implementa el envío de un fichero. Permite al usuario introducir la ruta de un fichero por teclado, y a continuación, lee el contenido del fichero y lo envía a la estación destino en tramas de caracteres. Además, la función también recibe tramas de la estación destino, y muestra por pantalla el número de caracteres recibidos cada vez que se recibe una trama. El envío del fichero se realiza hasta que se hayan enviado todos los caracteres del fichero, o hasta que el usuario pulse la tecla ESC (código ASCII 27).
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de descubrimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra y 02 para la estación esclava).
 */
void gestionMenuMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo);

/**
 * @brief Función que implementa el protocolo de comunicación para la estación esclava. Permite a la estación esclava enviar caracteres de forma interactiva a la estación maestra, y también recibir caracteres de la estación maestra. El envío de caracteres se realiza hasta que el usuario pulse la tecla ESC (código ASCII 27). Además, la función también muestra por pantalla el número de caracteres recibidos cada vez que se recibe una trama, y al finalizar el envío de caracteres, muestra por pantalla el tamaño del fichero recibido (en caso de que se haya enviado un fichero).
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de descubrimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra y 02 para la estación esclava).
 */
void gestionMenuEsclava(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo);


/**
 * @brief Función que implementa el protocolo de descubrimiento para la estación maestra. Envía una trama de descubrimiento y espera a recibir una respuesta de la estación esclava. Devuelve la MAC de la estación esclava.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino que se va a usar en la trama de descubrimiento, que en este caso será la MAC de broadcast (FF:FF:FF:FF:FF:FF).
 * @param type Tipo de la trama de descubrimiento, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra).
 * @param numGrupo Número de grupo al que pertenece la estación, que se introduce por teclado al inicio del programa.
 */
void conexionDesdeMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo);

/**
 * @brief Función que implementa el protocolo de descubrimiento para la estación esclava. Espera a recibir una trama de descubrimiento de la estación maestra, y si se recibe, responde con una trama de respuesta. No devuelve nada, pero muestra por pantalla la MAC de la estación maestra y guarda la MAC de la estación maestra para usarla posteriormente como MAC de destino en los envíos de caracteres.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param type Tipo de la trama de respuesta, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 02 para la estación esclava).
 * @param numGrupo Número de grupo al que pertenece la estación, que se introduce por teclado al inicio del programa.
 */
void conexionDesdeEsclava(interface_t *iface, unsigned char *type, int numGrupo);

#endif