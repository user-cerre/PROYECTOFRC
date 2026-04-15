//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2025/26 --------------------------------
//============================================================================

/**
 * Autores:
 * - Eduardo Cabello Gil
 * - Carlos Paredes Ruiz
 * Grupo de prácticas: Grupo 8 -- Jueves 10:00 - 11:30 h.
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <iostream>
#include "linkLayer.h"
#include "gestionPuerto.h"
#include "funcionesTramas.h"


using namespace std;

int main(){
  int numGrupo;
  int modo = 0;
  interface_t iface;
  pcap_if_t *avail_ifaces=nullptr;
  pcap_if *Lista = GetAvailAdapters();
  pcap_if *aux = Lista;
  unsigned char *mac_src;
  unsigned char mac_dstEsclava;
  unsigned char mac_dstMaestra;
  unsigned char mac_dst[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; //dirección de Broadcast
  unsigned char type[2] = {0x30, 0x30};
  int i = 0;

  printf("\n----------------------------\n");
  printf("------ SESION 3 - FRC ------\n");
  printf("----------------------------\n");

  printf("Interfaces de disponibles:\n");
  
  while (aux->next != NULL){
      cout<<"["<<i<<"]"<<" "<<aux->name<<endl;
      aux = aux->next;
      i++;
  }
  cout<<"Seleccione interfaz:"<<endl;
  aux = Lista;
  int seleccion;
  cin>>seleccion;
  if(cin.fail()){
    cout<<"Error al seleccionar la interfaz"<<endl;
  }else if (seleccion < i){
    i = 0;
    bool enc = false;
    while (aux != nullptr && !enc){
      if (seleccion == i){
        enc = true;
        cout<< "Intefaz elegida: "<<aux->name<<endl;
        mac_src = iface.MACaddr;
        setDeviceName(&iface, aux->name);
        GetMACAdapter(&iface);
        cout<< "La MAC seleccionada es: ";
        for (int j = 0; j < 6; j++){
          if( j < 5){
            printf("%02X:", mac_src[j]);
          }else{
            printf("%02X\n", mac_src[j]);
          }
        }
        printf("Introduzca el número de grupo: ");
        cin>>numGrupo;
        type[0] = (unsigned char)(0x30 + numGrupo);
        cout<<endl;
      }else{
        aux = aux->next;
        i++;
      }
    }



    if (OpenAdapter(&iface) == 0){
      printf("Puerto abierto correctamente\n");
      printf("Seleccione el modo de la estación:\n");
      printf("[1] Modo Maestra\n");
      printf("[2] Modo Esclava\n");
      cin>> modo;
      switch (modo)
      {
      case 1://MAESTRO
        type[1] = 0x01;
        conexionDesdeMaestra(&iface, mac_dst, type, numGrupo);
        break;
      case 2://ESCLAVO
        type[1] = 0x02;
        conexionDesdeEsclava(&iface, type, numGrupo);
        break;
        }
       type[1] = 0x00;
    }else{
      cout<<"Error al intentar abrir el puerto"<<endl;
    }
  }else{
    cout<<"Error en la selección de la interfaz"<<endl;
  }
  cout<<endl;
  
  //Cerramos el puerto:
  CloseAdapter(&iface);
  printf("Puerto cerrado\n");

  return 0;
}

  /*Explicación del proceso:
- Primero se muestra al usuario una lista de las interfaces de red disponibles en el sistema, y se le pide que seleccione una.
- Luego se obtiene la MAC de la interfaz seleccionada y se muestra por pantalla.
- A continuación, se le pide al usuario que introduzca el número de grupo al que pertenece su estación.
- Después se abre el puerto de la interfaz seleccionada para poder enviar y recibir paquetes.
- Finalmente, se le pide al usuario que seleccione el modo de la estación (maestra o esclava), y dependiendo de la selección, se 
  ejecuta el protocolo de descubrimiento correspondiente.
- Caso de seleccionar el modo Maestra:
  - Se construye una trama de descubrimiento con la MAC de origen, la MAC de destino (broadcast) y el tipo correspondiente al número de grupo y a la operación que se está 
    ejecutando, en este caso sería 01.  
  - Se envía la trama de descubrimiento.
  - Se espera a recibir una respuesta de la estación esclava, y si se recibe, se muestra la MAC de la estación esclava por pantalla.
  - Por último, se da a elegir al usuario si qué es lo que quiere enviar a la estación esclava, si caracteres de forma interactiva o un fichero, 
    y se ejecuta el protocolo correspondiente para cada caso.
  
- Caso de seleccionar el modo Esclava:
  - Se espera a recibir una trama de descubrimiento de la estación maestra, viendo si coincide el numero de grupo de las tramas que se reciben 
    con el que se ha introducido.
  - Si se recibe una trama de descubrimiento válida, se muestra la MAC de la estación maestra por pantalla.
  - A continuación se construye una trama de respuesta con la MAC de origen (la esclava, que es la que le interesa a la maestra para saber a quién tendrá 
    que enviarle los caracteres), la MAC de destino (que es la MAC de la estación maestra que se ha obtenido de la trama recibida) y el tipo correspondiente 
    al número de grupo y a la operación que se está ejecutando, en este caso sería 02, y se envía.
  - Por último, se da a elegir al usuario sólo la posibilidad de enviar caracteres de forma interactiva o finalizar la conexión. Si el usuario decide la primera opción, 
    se ejecuta el protocolo correspondiente para ello, que es el mismo que para la estación maestra, pero con la diferencia de que en este caso, cada vez que se recibe una 
    trama, se muestra por pantalla el número de caracteres recibidos, y al finalizar el envío de caracteres, se muestra por pantalla el tamaño del fichero recibido 
    (en caso de que la maestra haya enviado un fichero).
  */
