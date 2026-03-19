#include "gestionPuerto.h"
#include "linkLayer.h"
#ifndef FUNCIONESTRAMAS_H
#define FUNCIONESTRAMAS_H
using namespace std;

void protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst);

void protocoloDescubrimientoEsclava(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst);



#endif