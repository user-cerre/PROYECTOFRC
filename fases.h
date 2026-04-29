
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "gestionPuerto.h"
#include "linkLayer.h"
#include "kbhit.h"
#ifndef FASES_H
#define FASES_H
using namespace std;


void faseDeEstablecimientoMaestro(interface_t *iface, unsigned char *mac_dst, unsigned char *type, apacket_t &recepcion);


void faseDeEstablecimientoEsclavo(interface_t *iface, unsigned char *type);

void faseDeTransferenciaMestro(interface_t *iface, unsigned char *mac_dst, unsigned char *type, apacket_t &recepcion);

void faseDeTransferenciaEsclavo(interface_t *iface, unsigned char *mac_dst, unsigned char *type, char &car);

void faseDeCierre(interface_t *iface, unsigned char *mac_dst, unsigned char *type);

#endif