#include "funcionesTramas.h"


unsigned char protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    unsigned char * frame = BuildHeader(mac_src, mac_dst, type);
    SendFrame(iface, frame, 0);
    printf("Esperando que se una la estación esclava...\n");
    apacket_t d = ReceiveFrame(iface);
    bool contestacionEsclava = false;

    while(!contestacionEsclava){ 
        if(d.packet == nullptr){
            continue;
        }
        while(d.packet[12] != (unsigned char)(0x30 + numGrupo) && !contestacionEsclava){
            d = ReceiveFrame(iface);
            if(d.packet[13] == 0x02){
                contestacionEsclava = true;
            }
        }
    }
    const unsigned char *esclava = d.packet;

    esclava = d.packet + 6; //esclava apunta a la MAC de origen de la trama recibida, que se encuentra en desplazamiento = 6.
    printf("Estación encontrada. La MAC es: ");
    for(int j = 0; j<= 5 ;j++){
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
        if(d.packet == nullptr){
            continue;
        }
        if(d.packet[12] != (unsigned char)(0x30 + numGrupo)){
            d = ReceiveFrame(iface);
            if(d.packet[13] == 0x01){
                contestacionMaestra = true;
            }
        }
    }
    const unsigned char *maestra = d.packet; //maestra apunta al inicio de la trama recibida, donde está la MAC de destino.
    
    printf("Estación encontrada.La MAC es: ");
    for(int j = 0; j<= 5 ;j++){
        printf("%0X:", maestra[j]);
    }
    printf("\n");
    unsigned char mac_dst[6];
    for(int i = 0; i < 6; i++){
        mac_dst[i] = maestra[i]; //mac_dst se llena con la MAC de destino de la trama recibida, que es la MAC de la estación maestra.
    }
    unsigned char * frame = BuildHeader(mac_src, mac_dst, type);
    SendFrame(iface, frame, 0);
}
