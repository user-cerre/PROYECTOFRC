
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "gestionPuerto.h"
#include "linkLayer.h"
#include "kbhit.h"
#ifndef FASES_H
#define FASES_H
using namespace std;

/**
 * @brief Función que implementa la fase de establecimiento para la estación maestra. Envía una trama de control de tipo ENQ (código 05) a la estación esclava, y espera a recibir una trama de control de tipo ACK (código 06) por parte de la estación esclava. La función se bloquea hasta que se recibe la trama de control ACK, lo que indica que la conexión se ha establecido correctamente. Una vez establecida la conexión, la función llama a la fase de transferencia para la estación maestra.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de descubrimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra).
 * @param recepcion Estructura donde se almacenará la trama recibida durante el proceso de establecimiento.
 */
void faseDeEstablecimientoMaestro(interface_t *iface, unsigned char *mac_dst, unsigned char *type, apacket_t &recepcion);

/**
 * @brief Función que implementa la fase de establecimiento para la estación esclava. Espera a recibir una trama de control de tipo ENQ (código 05) por parte de la estación maestra, y si se recibe, responde con una trama de control de tipo ACK (código 06). La función se bloquea hasta que se recibe la trama de control ENQ, lo que indica que la conexión se ha establecido correctamente. Una vez establecida la conexión, la función llama a la fase de transferencia para la estación esclava.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 02 para la estación esclava).
 */
void faseDeEstablecimientoEsclavo(interface_t *iface, unsigned char *type);
/**
 * @brief Función que implementa la fase de transferencia para la estación maestra. Lee el contenido de un fichero llamado "EProtoc.txt" y lo envía a la estación esclava en tramas de caracteres. Cada trama de caracteres contiene un número de trama (que alterna entre '0' y '1'), la longitud del payload, el payload (que es una cadena de caracteres leída del fichero) y un Byte de Control de Error (BCE) calculado a partir del payload. La función también recibe tramas de control por parte de la estación esclava, y si se recibe una trama de control ACK (código 06) con el mismo número de trama que se ha enviado, se continúa enviando la siguiente trama. Si se recibe una trama de control NACK (código 21) con el mismo número de trama que se ha enviado, se vuelve a enviar la misma trama. El proceso de envío de tramas continúa hasta que se han enviado todos los caracteres del fichero, o hasta que el usuario pulse la tecla ESC (código ASCII 27).
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de establecimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra).
 * @param recepcion Estructura donde se almacenará la trama recibida durante el proceso de transferencia.
 */
void faseDeTransferenciaMestro(interface_t *iface, unsigned char *mac_dst, unsigned char *type, apacket_t &recepcion);
/**
 * @brief Función que implementa la fase de transferencia para la estación esclava. Espera a recibir tramas de caracteres por parte de la estación maestra, y cada vez que se recibe una trama de caracteres, se muestra por pantalla el número de trama, la longitud del payload, el payload (que es una cadena de caracteres) y el Byte de Control de Error (BCE) calculado a partir del payload. Si el BCE calculado a partir del payload coincide con el BCE recibido en la trama, se responde con una trama de control ACK (código 06) con el mismo número de trama que se ha recibido. Si el BCE calculado a partir del payload no coincide con el BCE recibido en la trama, se responde con una trama de control NACK (código 21) con el mismo número de trama que se ha recibido. El proceso de recepción de tramas continúa hasta que se recibe una trama de control EOT (código 04) con número de trama '0', lo que indica que la transferencia ha finalizado.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de establecimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 02 para la estación esclava).
 * @param car Referencia a un carácter donde se almacenará el valor 27 (código ASCII para ESC) cuando se reciba la trama de control EOT, lo que indica que la transferencia ha finalizado.
 */
void faseDeTransferenciaEsclavo(interface_t *iface, unsigned char *mac_dst, unsigned char *type, char &car);
/**
 * @brief Función que implementa la fase de cierre para la estación maestra. Envía una trama de control de tipo EOT (código 04) a la estación esclava, y espera a recibir una trama de control de tipo ACK (código 06) por parte de la estación esclava. La función se bloquea hasta que se recibe la trama de control ACK, lo que indica que la conexión se ha cerrado correctamente.
 * @param iface Puntero a la interfaz de red que se va a usar para enviar y recibir las tramas.
 * @param mac_dst MAC de destino a la que se van a enviar las tramas, que se obtiene en el proceso de establecimiento.
 * @param type Tipo de las tramas que se van a enviar, que se construye a partir del número de grupo y la operación que se está ejecutando (en este caso sería 01 para la estación maestra).
 */
void faseDeCierre(interface_t *iface, unsigned char *mac_dst, unsigned char *type);

#endif