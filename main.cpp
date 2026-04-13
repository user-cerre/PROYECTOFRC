  //============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2025/26 --------------------------------
// ----------------------------- SESION2.CPP ---------------------------------
//============================================================================
#include <stdio.h>
#include <stdio_ext.h>
#include <iostream>
#include "linkLayer.h"
#include "gestionPuerto.h"
#include "funcionesTramas.h"


using namespace std;

int main()
{
  char car;
 

  printf("\n----------------------------\n");
  printf("------ SESION 2 - FRC ------\n");
  printf("----------------------------\n");
  interface_t iface;
  pcap_if_t *avail_ifaces=NULL;
  pcap_if *Lista = GetAvailAdapters();
  pcap_if *aux = Lista;
  int i = 0;
  int seleccion;
  while (aux->next != NULL){
      cout<<"["<<i<<"]"<<" "<<aux->name<<endl;
      i++;
      aux = aux->next;
  }
  cout<<"Seleccione interfaz:"<<endl;
  cin>>seleccion;
  for(int j = 0; j< seleccion; j++){
      Lista= Lista->next;
  }
  cout<<"Interfaz Elegida: "<<Lista->name<<endl;
  //Hasta aquí simplemente estamos dando al usuario que elija la interfaz de red que desea usar para enviar los paquetes. Ahora vamos a obtener la MAC de esa interfaz y mostrarla por pantalla, así como la MAC destino que hemos definido al principio del programa.
  interface_t interfazSeleccionada;
  unsigned char *mac_src = interfazSeleccionada.MACaddr;
  setDeviceName(&interfazSeleccionada,Lista->name);
  GetMACAdapter(&interfazSeleccionada);
  //Guardamos en mac_src la MAC de la interfaz seleccionada
  cout<<"La MAC es: ";
  for(int j = 0; j<= 5 ;j++){
     printf("%0X:", mac_src[j]);
  }
  cout<<endl;
  printf("Introduzca el número de grupo: ");
  int numGrupo;
  cin>>numGrupo;

  //Abrimos el puerto de la MAC seleccionada para poder enviar los paquetes 
  int Puerto=OpenAdapter(&interfazSeleccionada);

  if(Puerto != 0)
    {
        printf("Error al abrir el puerto\n");
        getch();
        return (1);
    }
  else{
    printf("Puerto abierto correctamente\n");
  }

    __fpurge(stdin);

  printf("Selección del modo de la estación:\n");
  printf("[1] Modo Maestra\n");
  printf("[2] Modo Esclava\n");
  int modo;
  cin>>modo;

  //FIN DEL PROCESO DE INICIALIZACIÓN, AHORA SE EJECUTARÁ EL PROTOCOLO DE DESCUBRIMIENTO DEPENDIENDO DEL MODO SELECCIONADO POR EL USUARIO.

  unsigned char mac_dst[6];
  unsigned char type[2] = {0, 0}; // Tipo de trama, se construirá a partir del número de grupo y la operación que se está ejecutando.
  
  type[0] = (unsigned char)(0x30 + numGrupo); // El primer byte del tipo se construye a partir del número de grupo, sumándole 0x30 para que quede en el rango de tipos personalizados (0x3000 - 0x3FFF).

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
  - Por último se guarda la MAC de la estación esclava para usarla posteriormente como MAC de destino en los envíos de caracteres.
- Caso de seleccionar el modo Esclava:
  - Se espera a recibir una trama de descubrimiento de la estación maestra, viendo si coincide el numero de grupo de las tramas que se reciben 
    con el que se ha introducido.
  - Si se recibe una trama de descubrimiento válida, se muestra la MAC de la estación maestra por pantalla.
  - Por último se construye una trama de respuesta con la MAC de origen (la esclava, que es la que le interesa a la maestra para saber a quién tendrá 
    que enviarle los caracteres), la MAC de destino (que es la MAC de la estación maestra que se ha obtenido de la trama recibida) y el tipo correspondiente 
    al número de grupo y a la operación que se está ejecutando, en este caso sería 02, y se envía.
  */

  switch (modo)
  {
  case 1://MAESTRO
    type[1] = 0x01;
    protocoloDescubrimientoMaestra(&interfazSeleccionada, mac_src, mac_dst, type, numGrupo);
    break;
  case 2://ESCLAVO
    type[1] = 0x02;
    protocoloDescubrimientoEsclava(&interfazSeleccionada, mac_src,mac_dst, type, numGrupo);
    //NECESITAMOS GUARDAR LA MAC
    break;
  }

  type[1] = 0x00; //Tipo para el envío de caracteres, que es diferente al tipo usado para el descubrimiento, por eso se pone a 0.

  printf("Selección de Modo: \n");
  printf("[F1] - Envío de caracteres interactivo\n");
  if(modo == 1){
    printf("[F2] - Envío de un fichero\n");
  }
  printf("[ESC] - Salir\n");

  while(car != 27){
    if(kbhit()){
      car = getch();
      if(car != 27){
        printf("La tecla pulsada no es válida. Por favor, pulse una de las teclas indicadas en el menú.\n");
      } else{
        if(kbhit()){
          car = getch();
          if(car == 'O'){
            car = getch();
            switch (car){
              case 'P':
                
              break;
              case 'Q':

              break;
              case 'R':
              //TODO: Tecla F3 aún no usada
              break;
              case 'S':
              //TODO: Tecla F4 aún no usada
              break;
            }
          }
        }
      }
    }
  }

  type[1] = 0x00; //Tipo para el envío de caracteres, que es diferente al tipo usado para el descubrimiento, por eso se pone a 0.

  printf("Selección de Modo: \n");
  printf("[F1] - Envío de caracteres interactivo\n");
  if(modo == 1){
    printf("[F2] - Envío de un fichero\n");
  }
  printf("[ESC] - Salir\n");

  while(car != 27){
    if(kbhit()){
      car = getch();
      if(car != 27){
        printf("La tecla pulsada no es válida. Por favor, pulse una de las teclas indicadas en el menú.\n");
      } else{
        if(kbhit()){
          car = getch();
          if(car == 'O'){
            car = getch();
            switch (car){
              case 'P':
                
              break;
              case 'Q':

              break;
              case 'R':
              //TODO: Tecla F3 aún no usada
              break;
              case 'S':
              //TODO: Tecla F4 aún no usada
              break;
            }
          }
        }
      }
    }
  }

  type[1] = 0x00;
  //Estos dos bucles simplemente se encargan de mostrar por pantalla la MAC origen y
  //la mac destino respectivamente EN HEXADECIMAL.
    printf("Pulse los caracteres a enviar:\n");

    //Este while se encarga de leer por teclado los caracteres que el usuario desea 
    // enviar, y a su vez, también se encarga de recibir los caracteres que le lleguen
    // a la interfaz seleccionada. El bucle se mantendrá activo hasta que el usuario pulse
    // la tecla ESC (carácter 27 en ASCII).
    while(car != 27){
      car = recibirCaracter(interfazSeleccionada);
      if(car){
        printf("Recibido el carácter: %c\n",car);
      }
      if(kbhit()){
        car = getch();
        if(car != 27){
          enviarCaracter(interfazSeleccionada,car,mac_src,mac_dst,type);
        }
      }
    }

  //Cerramos el puerto:
  CloseAdapter(&interfazSeleccionada);
  printf("Puerto cerrado\n");


  return 0;
}
