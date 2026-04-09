#include "gestionPuerto.h"

void EnviarCaracter(interface_t iface, char dato, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type){
    unsigned char *payload = (unsigned char *)malloc(sizeof(char));
    payload[0] = dato;
    //Construimos la trama Ethernet
    unsigned char * frame = BuildFrame(mac_src, mac_dst, type, payload);
    SendFrame(&iface, frame, 1);
    free(payload);
}

unsigned char  recibirCaracter(interface_t iface){
    apacket_t d  = ReceiveFrame(&iface);
    const unsigned char *payload = d.packet;
    if (d.packet != nullptr){
        payload = d.packet + 14;
        cout<<"Caracteres enviados: "<< "TODO" <<endl;
        return payload[0];
    }else{
        return 0;
    }
    
}
