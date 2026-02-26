//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2025/26 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================
/*
AUTORES DEL PROYECTO
====================

Eduardo Cabello Gil
Carlos Paredes Ruiz
*/

#include <stdio.h>
#include <iostream>
#include "linkLayer.h"




using namespace std;

// int main()
// {
// printf("\n----------------------------\n");
// printf("------ SESION 1 - FRC ------\n");
// printf("----------------------------\n");    
// interface_t iface;
// pcap_if_t *avail_ifaces=NULL;
// pcap_if *Lista = GetAvailAdapters();
// pcap_if *aux = Lista;
// int i = 0;
// int seleccion;
// while (aux->next != NULL){
//     cout<<"["<<i<<"]"<<" "<<aux->name<<endl;
//     i++;
//     aux = aux->next;
// }
// cout<<"Seleccione una opcion comprendida entre 0 y "<<i-1<<":";
// cin>>seleccion;
// for(int j = 0; j< seleccion; j++){
//     Lista= Lista->next;
// }
// cout<<"Interfaz Elegida: "<<Lista->name<<endl;
// interface_t interfazSeleccionada;
// setDeviceName(&interfazSeleccionada,Lista->name);
// GetMACAdapter(&interfazSeleccionada);
// cout<<"La MAC es: ";
// for(int j = 0; j<= 5 ;j++){
//     printf("%0X:", interfazSeleccionada.MACaddr[j]);
// }
// printf("%0X\n",interfazSeleccionada.MACaddr[5]);
// return 0;

// }
