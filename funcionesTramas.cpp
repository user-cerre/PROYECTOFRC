 /**
 * Autores:
 * - Eduardo Cabello Gil
 * - Carlos Paredes Ruiz
 * Grupo de prácticas: Grupo 8 -- Jueves 10:00 - 11:30 h.
 */

#include "funcionesTramas.h"

// unsigned char* calcularBCE(interface_t *iface, unsigned char *mac_dst){
    
// }

bool establecimientoMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    bool esclavaAcepta = false;
    unsigned char *payloadEstablecimiento;
    payloadEstablecimiento[0] = 'R';
    payloadEstablecimiento[1] = 0x05; //Valor de control de ENQ
    payloadEstablecimiento[2] = 0;

    unsigned char *frameEstablecimiento = BuildFrame(iface->MACaddr, mac_dst, type, payloadEstablecimiento);
    SendFrame(iface, payloadEstablecimiento, 3);

    while(!esclavaAcepta){
        apacket_t d = ReceiveFrame(iface);
        cout << d.packet[14] << " PRUEBA" << endl;
        if(d.packet != nullptr && d.packet[15] == 0x06 && d.packet[12] == (unsigned char)(0x30 + numGrupo)){ //Compruebo si la trama que he recibido contiene la trama de control ACK y proviene de la esclava.
            esclavaAcepta = true;
        }
    }

    return esclavaAcepta;
}

void establecimientoEsclava(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    bool reciboEstablecimientoMaestra = false;
    while(!reciboEstablecimientoMaestra){
        apacket_t d = ReceiveFrame(iface);
        if(d.packet != nullptr && d.packet[15] == 0x05 && d.packet[12] == (unsigned char)(0x30 + numGrupo)){
            reciboEstablecimientoMaestra = true;
        }
    }
    if(reciboEstablecimientoMaestra){
        unsigned char *payloadAceptacion;
        payloadAceptacion[0] = 'R';
        payloadAceptacion[1] = 0x06;  //Valor de control de ACK
        payloadAceptacion[2] = 0;

        unsigned char *frameAceptacion = BuildFrame(iface->MACaddr, mac_dst, type, payloadAceptacion);
        SendFrame(iface, payloadAceptacion, 3);
    }
}

void envioInteractivoCaracteres(interface_t *iface, unsigned char *mac_dst, unsigned char *type){
    char caracter = 0;
    int numCaracteres = 0;
    while(caracter != 27){//Mientras no se pulse ESC
        if(kbhit()){//Si se ha pulsado una tecla
            caracter = getch();
            if(caracter != 27){//Si no se ha pulsado ESC, se envía el carácter introducido
                enviarCaracter(iface, caracter, iface->MACaddr, mac_dst, type);
            }
        }
        numCaracteres = recibirCaracter(iface);
        if(numCaracteres != 0){
            cout << "Se han recibido " << numCaracteres << " caracteres" << endl;
        }
    }
}

void gestionMenuMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    printf("Seleccione opción:\n ");
    printf("[F1] - Envío de caracteres interactivo\n ");
    printf("[F2] - Envío de fichero\n ");
    printf("[F3] - Protocolo de paro y espera\n ");
    printf("ESC - Salir\n ");
    char car = 0;
    while (car != 27){//Mientras no se pulse ESC
        if(kbhit()){//Si se ha pulsado una tecla
            car = getch();
            if(car == 27){
                if(kbhit()){
                    car = getch();
                    if(car == 'O'){
                        if(kbhit()){
                            car = getch();
                            switch (car)
                            {
                            case 'P':
                                printf("Has elegido Envío de caracteres interactivo\n ");
                                envioInteractivoCaracteres(iface, mac_dst, type);
                            break;
                            
                            case 'Q':
                                printf("Has elegido Envío de fichero\n ");
                                enviarFichero(*iface, mac_dst, type);
                            break;

                            case 'R':
                                printf("Has elegido Protocolo de paro y espera\n");
                                if(establecimientoMaestra(iface, mac_dst, type, numGrupo)){
                                    cout << "ÉXITO" << endl;
                                };
                            break;

                            }
                        }
                    }
                }
            }
        }
    }
}

void gestionMenuEsclava(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    printf("Seleccione opción\n ");
    printf("[F1] - Envío de caracteres interactivo\n ");
    printf("[F3] - Protocolo de paro y espera\n ");
    printf("ESC - Salir\n ");
    char car = 0;
    int contador = 0;
    int valor = 0;
    while (car != 27){
        if(kbhit()){
            car = getch();
            if(car == 27){
                if(kbhit()){
                    car = getch();
                    if(car == 'O'){
                        if(kbhit()){
                            car = getch();
                            switch (car)
                            {
                            case 'P':
                                printf("Has elegido Envío de caracteres interactivo\n ");
                                envioInteractivoCaracteres(iface, mac_dst, type);
                                break;
                            case 'R':
                                printf("Has elegido Protocolo de paro y espera\n");
                                establecimientoEsclava(iface, mac_dst, type, numGrupo);
                                break;
                            }
                        }
                    }
                }
            }
        }
        valor = recibirCaracter(iface);
        contador += valor;
        if(valor != 0){
            cout << "Nº de caracteres: " << valor << endl;
        }
    }
    if(contador > 1000){    //Si se han recibido más de 1000 caracteres, se asume que se ha enviado un fichero, y se muestra el tamaño del fichero recibido.
        cout << "Tamaño del fichero: " << contador << endl;
    }
}

void conexionDesdeMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int numGrupo){
    unsigned char * frame = BuildHeader(iface->MACaddr, mac_dst, type);
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
    const unsigned char *esclava = d.packet;    //en este vector está toda la información de la esclava, incluida su type.
    unsigned char macDst[6];    //en este vector se almacenará sólo la mac Origen de la esclava, que es el destinatario al que enviaremos los caracteres/fichero

    printf("Estación encontrada. La MAC es: ");
    int i = 0;
    for(int j = 6; j<= 11 ;j++){//Empieza en 6 porque los primeros 6 bytes de la trama son la MAC destino, y los siguientes 6 bytes (del 6 al 11) son la MAC origen, que es la que nos interesa para enviarle las tramas a la estación esclava.
        if(j < 11){
            printf("%02X:", esclava[j]);
        }else{
            printf("%02X\n", esclava[j]);
        }
        macDst[i] = esclava[j];
        i++;
    }
    printf("\n");
    gestionMenuMaestra(iface, macDst, type, numGrupo);
}

void conexionDesdeEsclava(interface_t *iface, unsigned char *type, int numGrupo){
    printf("Esperando que se una la estación maestra...\n");
    apacket_t d;
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

    const unsigned char *maestra = d.packet; 
    unsigned char macDst[6];

    printf("Estación encontrada.La MAC es: ");
    int i = 0;
    for(int j = 6; j<= 11 ;j++){
        if( j < 11){
            printf("%02X:", maestra[j]);
        }else{
            printf("%02X\n", maestra[j]);
        }
        macDst[i] = maestra[j]; //mac_dst se llena con la MAC de origen de la trama recibida, que es la MAC de la estación maestra.
        i++;
    }
    printf("\n");

    unsigned char * frame = BuildHeader(iface->MACaddr, macDst, type);
    SendFrame(iface, frame, 0);

    gestionMenuEsclava(iface, macDst, type, numGrupo);
}