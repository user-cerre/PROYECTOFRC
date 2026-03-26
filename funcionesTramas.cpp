#include "funcionesTramas.h"


unsigned char protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    unsigned char * frame = BuildHeader(mac_src, mac_dst, type);
    SendFrame(iface, frame, 0);
    printf("Esperando que se una la estación esclava...\n");
    apacket_t d = ReceiveFrame(iface);
    bool contestacionEsclava = false;

    while(!contestacionEsclava){ 
        d = ReceiveFrame(iface);
        if(d.packet == nullptr){
            continue;
        }
        if(d.packet[12] == (unsigned char)(0x30 + numGrupo) && d.packet[13] == 0x02){
            contestacionEsclava = true;
        }
    }
    const unsigned char *esclava = d.packet;

    printf("Estación encontrada. La MAC es: ");
    for(int j = 6; j<= 11 ;j++){
        printf("%0X:", esclava[j]);
    }
    printf("\n");
    return *esclava;
}

void protocoloDescubrimientoEsclava(interface_t *iface, unsigned char *mac_src, unsigned char *type, int numGrupo){
    printf("Esperando que se una la estación maestra...\n");
    apacket_t d = ReceiveFrame(iface);
    bool contestacionMaestra = false;
    
    while(!contestacionMaestra){
        d = ReceiveFrame(iface);
        if(d.packet == nullptr){
            continue;
        }
        if(d.packet[12] == (unsigned char)(0x30 + numGrupo) && d.packet[13] == 0x01){
            contestacionMaestra = true;
        }
    }

    const unsigned char *maestra = d.packet; //maestra apunta al inicio de la trama recibida, donde está la MAC de destino.
    
    printf("Estación encontrada.La MAC es: ");
    unsigned char mac_dst[6];
    int i = 0;
    for(int j = 6; j<= 11 ;j++){
        printf("%0X:", maestra[j]);
        mac_dst[i] = maestra[j]; //mac_dst se llena con la MAC de origen de la trama recibida, que es la MAC de la estación maestra.
        i++;
    }
    printf("\n");

    unsigned char * frame = BuildHeader(mac_src, mac_dst, type);
    SendFrame(iface, frame, 0);
}
