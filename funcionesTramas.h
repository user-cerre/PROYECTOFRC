#include "gestionPuerto.h"
#include "linkLayer.h"
#ifndef FUNCIONESTRAMAS_H
#define FUNCIONESTRAMAS_H
using namespace std;

unsigned char protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type);

void protocoloDescubrimientoEsclava(interface_t *iface, unsigned char *mac_src, unsigned char *type, int numGrupo);



#endif