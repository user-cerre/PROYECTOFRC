#include <stdio.h>
#include <iostream>
#include "linkLayer.h"
#ifndef GESTIONPUERTO_H
#define GESTIONPUERTO_H
using namespace std;

void EnviarCaracter(interface_t iface, char dato, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type);
#endif