#include "funcionesTramas.h"


unsigned char protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type){
    unsigned char * frame = BuildHeader(mac_src, mac_dst, type);
    SendFrame(iface, frame, 0);
    printf("Esperando que se una la estación esclava...\n");
    apacket_t d  = ReceiveFrame(iface);
    const unsigned char *esclava = d.packet;
    if (d.packet != nullptr){
        esclava = d.packet + 6; //esclava apunta a la MAC de origen de la trama recibida, que se encuentra en desplazamiento = 6.
        printf("Estación encontrada. La MAC es: ");
        for(int j = 0; j<= 5 ;j++){
            printf("%0X:", esclava[j]);
        }
        printf("\n");
    }else{
        printf("No se recibió respuesta de la estación esclava.\n");
    }
    return *esclava;
}

void protocoloDescubrimientoEsclava(interface_t *iface, unsigned char *mac_src, unsigned char *type, int numGrupo){
    printf("Esperando que se una la estación maestra...\n");
    apacket_t d  = ReceiveFrame(iface);
    const unsigned char *maestra = d.packet; //maestra apunta al inicio de la trama recibida, donde está la MAC de destino.
    if (d.packet != nullptr && maestra[12] == (unsigned char)(0x30 + numGrupo)){
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
    }else{
        printf("No se recibió respuesta de la estación maestra.\n");
    }
}
