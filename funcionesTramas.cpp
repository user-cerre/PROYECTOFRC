#include "funcionesTramas.h"


void protocoloDescubrimientoMaestra(interface_t *iface, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    bool contestacionEsclava = false;
    apacket_t d;
    unsigned char mac_dst[6];
    printf("Esperando que se una la estación esclava...\n");
    while(!contestacionEsclava){ 
        d = ReceiveFrame(iface);
        if(d.packet != nullptr){
            if ( d.packet[12] == type[0]){
                if (d.packet[13] == type[1]){
                    contestacionEsclava = true;
                    for(int i = 0; i < 6; i++){
                        mac_dst[i] = d.packet[i + 6]; //mac_dst se llena con la MAC de destino de la trama recibida, que es la MAC de la estación esclava.
                    }
                    unsigned char *frame = BuildHeader(iface->MACaddr, mac_dst, type);
                    SendFrame(iface, frame, 0);
                    printf("Estación encontrada. La MAC es: ");
                    for(int j = 0; j < 6 ; j++){
                        if (j < 5){
                            printf("%02X:", d.packet[j+6]);
                        } else {
                            printf("%02X", d.packet[j+6]);
                        }
                    }
                    printf("\n");
                    cout<< "Selleccione el modo de envío de caracteres: "<<endl;
                    cout<< "[F1] Envío de caracteres por teclado"<<endl;
                    //AQUÍ LLAMA A LA INTERACTIVIDAD DEL ESCLAVO
                }
            }
        }
    }
    
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
}

void respuesta(interface_t *iface, unsigned char *type){
    
}

void respuestaEsclava(interface_t *iface, unsigned char *type){
    
}