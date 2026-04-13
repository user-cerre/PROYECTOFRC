#include "funcionesTramas.h"


void protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    unsigned char broadcast[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    unsigned char * frame = BuildHeader(mac_src, broadcast, type);
    SendFrame(iface, frame, 0);

    printf("Esperando que se una la estación esclava...\n");
    
    apacket_t d;
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
    for(int i = 0; i < 6; i++){
        mac_dst[i] = d.packet[i + 6]; //mac_dst se llena con la MAC de destino de la trama recibida, que es la MAC de la estación esclava.
    }
    printf("Estación encontrada. La MAC es: ");
    for(int j = 0; j < 6 ; j++){
        printf("%02X%c", mac_dst[j], (j < 5) ? ':' : '\n');
    }
    printf("\n");
}

void protocoloDescubrimientoEsclava(interface_t *iface, unsigned char *mac_src,unsigned char *mac_dst, unsigned char *type, int numGrupo){
    printf("Esperando que se una la estación maestra...\n");

    bool contestacionMaestra = false;
    apacket_t d;

    while(!contestacionMaestra){
        d = ReceiveFrame(iface);

        if(d.packet == nullptr){
            continue;
        }

        if(d.packet[12] == (unsigned char)(0x30 + numGrupo) && d.packet[13] == 0x01){
            contestacionMaestra = true;
        }
    }

    printf("Estación encontrada.La MAC de la maestra es: ");
    for(int j = 0; j < 6 ;j++){
        mac_dst[j] = d.packet[j + 6];
        printf("%02X%c", mac_dst[j], (j < 5) ? ':' : '\n');//Esto no se ni lo que es, me lo ha autocompletado el IDE, no se ni para que sirve pero lo dejo por si acaso. Es para imprimir la MAC con formato XX:XX:XX:XX:XX:XX, y el ternario es para no imprimir ":" después del último byte de la MAC.
    }
    printf("\n");
    unsigned char *frame = BuildHeader(mac_src, mac_dst, type);
    SendFrame(iface, frame, 0);

    return *maestra;
}