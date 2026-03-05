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


using namespace std;

int main()
{
  char car;
  unsigned char mac_dst[6]={0x00, 0x00, 0x00, 0x00,0x00, 0x00};
  unsigned char type[2]={0x30,0x00};
 

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
  cout<<"Seleccione una opcion comprendida entre 0 y "<<i-1<<":"<<endl;
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
  cout<<"La MAC origen es: ";
  for(int j = 0; j<= 5 ;j++){
     printf("%0X:", mac_src[j]);
  }
  printf("%0X\n",mac_src[5]);

  cout<<"La MAC destino es: ";
  for(int j = 0; j<= 5 ;j++){
     printf("%0X:", mac_dst[j]);
  }
  printf("%0X\n",mac_dst[5]);

  //Estos dos bucles simplemente se encargan de mostrar por pantalla la MAC origen y
  //la mac destino respectivamente EN HEXADECIMAL.

  //Abrimos el puerto de la MAC seleccionada para poder enviar los paquetes 
  int Puerto=OpenAdapter(&interfazSeleccionada);

  if(Puerto != 0)
    {
        printf("Error al abrir el puerto\n");
        getch();
        return (1);
    }
  else
    printf("Puerto abierto correctamente\n");

    __fpurge(stdin);
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
          EnviarCaracter(interfazSeleccionada,car,mac_src,mac_dst,type);
        }
      }
    }

  //Cerramos el puerto:
  CloseAdapter(&interfazSeleccionada);
  printf("Puerto cerrado\n");


  return 0;
}
