#include "gestionPuerto.h"
#include "linkLayer.h"
#ifndef FUNCIONESTRAMAS_H
#define FUNCIONESTRAMAS_H
using namespace std;

/**
 * @brief Función que implementa el protocolo de descubrimiento para la estación maestra. Envía una trama de descubrimiento y espera a recibir una respuesta de la estación esclava. Devuelve la MAC de la estación esclava.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_src MAC de origen que se va a usar en la trama de descubrimiento.
 * @param mac_dst MAC de destino que se va a usar en la trama de descubrimiento, que en este caso será la MAC de broadcast (FF:FF:FF:FF:FF:FF).
 * @param type Tipo de la trama de descubrimiento, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra).
 * @param numGrupo Número de grupo al que pertenece la estación, que se introduce por teclado al inicio del programa.
 */
void protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type, int numGrupo);

/**
 * @brief Función que implementa el protocolo de descubrimiento para la estación esclava. Espera a recibir una trama de descubrimiento de la estación maestra, y si se recibe, responde con una trama de respuesta. No devuelve nada, pero muestra por pantalla la MAC de la estación maestra y guarda la MAC de la estación maestra para usarla posteriormente como MAC de destino en los envíos de caracteres.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_src MAC de origen que se va a usar en la trama de respuesta, que en este caso será la MAC de la estación esclava (la propia MAC de la interfaz seleccionada).
 * @param type Tipo de la trama de respuesta, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 02 para la estación esclava).
 * @param numGrupo Número de grupo al que pertenece la estación, que se introduce por teclado al inicio del programa.
 */
void protocoloDescubrimientoEsclava(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type, int numGrupo);

/** 
 * @brief Función que implementa la conexión entre la estación maestra y la estación esclava. La estación maestra envía una trama de conexión a la estación esclava, y la estación esclava responde con una trama de confirmación. Si la conexión se establece correctamente, ambas estaciones muestran por pantalla un mensaje de confirmación.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param type Tipo de la trama de conexión, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 03 para la conexión entre la estación maestra y la estación esclava).  
*/
void respuesta(interface_t *iface, unsigned char *type);

/** 
 * @brief Función que implementa la conexión entre la estación maestra y la estación esclava. La estación maestra envía una trama de conexión a la estación esclava, y la estación esclava responde con una trama de confirmación. Si la conexión se establece correctamente, ambas estaciones muestran por pantalla un mensaje de confirmación.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param type Tipo de la trama de conexión, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 03 para la conexión entre la estación maestra y la estación esclava).  
*/
void respuestaEsclava(interface_t *iface, unsigned char *type);

#endif