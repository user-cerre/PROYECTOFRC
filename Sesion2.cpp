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
  char car = 'M';
  unsigned char mac_src[6]={0x00, 0x00, 0x00, 0x00,0x00, 0x00};
  unsigned char mac_dst[6]={0x00, 0x01, 0x02, 0x03,0x04, 0x05};
  unsigned char type[2]={0x30,0x00};
 
  interface_t iface;

  printf("\n----------------------------\n");
  printf("------ SESION 2 - FRC ------\n");
  printf("----------------------------\n");


  //Elegimos el puerto
  setDeviceName(&iface, "lo");
  GetMACAdapter(&iface);

  //Abrimos el puerto
  int Puerto=OpenAdapter(&iface);

  if(Puerto != 0)
    {
        printf("Error al abrir el puerto\n");
        getch();
        return (1);
    }
  else
    printf("Puerto abierto correctamente\n");

  __fpurge(stdin);
  //Enviamos un carácter
  EnviarCaracter(iface,car,mac_src,mac_dst,type);
  printf("Enviado el carácter: %c\n",car);

  //Cerramos el puerto:
  CloseAdapter(&iface);
  printf("Puerto cerrado\n");

  return 0;
}
