/**
 * Autores:
 * - Eduardo Cabello Gil
 * - Carlos Paredes Ruiz
 * Grupo de prácticas: Grupo 8 -- Jueves 10:00 - 11:30 h.
 */

#include "gestionPuerto.h"

void enviarCaracter(interface_t *iface, char dato, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type){
    unsigned char *payload = (unsigned char *)malloc(sizeof(unsigned char));
    //Almacenamos el carácter a enviar en el payload de la trama, que en este caso será un único byte.
    payload[0] = dato;

    //Construimos la trama Ethernet
    unsigned char * frame = BuildFrame(mac_src, mac_dst, type, payload);
    
    //Enviamos la trama a través de la interfaz seleccionada, indicando que el tamaño del payload es de 1 byte.
    SendFrame(iface, frame, 1);
    //Liberamos la memoria del payload, ya que BuildFrame hace una copia del payload que le pasamos, por lo que no necesitamos mantenerlo en memoria después de enviar la trama.
    free(payload);
}

int recibirCaracter(interface_t *iface){
    apacket_t d  = ReceiveFrame(iface);
    int i = 14;
    //Si hay algo en el payload de la trama recibida, lo devolvemos como carácter recibido. En caso contrario, devolvemos 0 para indicar que no se ha recibido ningún carácter.
    if (d.packet != nullptr && d.packet[14] > 0){
        printf("Recibido: ");
        while(i < d.header.len){
            printf("%c", d.packet[i]);
            i++;
        }
        printf("\n");
    }
    return i-14;
}

void enviarFichero(interface_t *iface, unsigned char *mac_dst, unsigned char *type){
    ifstream file("envio.txt");
    char texto[254];
    unsigned char *trama;
    if(file.is_open()){
        while (!file.eof()){
            file.read(texto, 254);
            if(file.gcount()!= 0){
                texto[file.gcount()]= '\0';
                trama = BuildFrame(iface->MACaddr, mac_dst, type, (unsigned char *)texto);
                SendFrame(iface, trama, file.gcount());
            }
        }
        file.close();
    }
}
/**
 * DIreccion es un caracter
 * COntrol un caracter
 * Número de trama '0' o '1' como carácter
 * Longitud un numero entre 1 y 254(el tamaño maximo de la trama)
 * Campo datos variables
 * BCE fijo
 */

void mostrarTrama(int control,int tramaN, int direccion){
    string mostrar = "E ";
    mostrar += direccion;
    switch(control){
        case 04:
            mostrar+=" EOT ";
        break;
        case 05:
            mostrar+=" ENQ ";
        break;
        case 06:
            mostrar+=" ACK ";
        break; 
        case 21:
            mostrar+=" NACK ";
        break;
    }
    mostrar+=tramaN;
    cout<<mostrar<<endl;
}

void enviarTramaDeControl(interface_t *iface, unsigned char *mac_dst, unsigned char *type, int control, char tramaN, char direccion){
    unsigned char payload[3];
    payload[0] = direccion;
    payload[1] = control;
    payload[2] = tramaN;

    unsigned char *trama = BuildFrame(iface->MACaddr, mac_dst, type, payload);
    SendFrame(iface, trama, sizeof(payload));
    mostrarTrama(control,tramaN,direccion);
    
    free(trama);
}

void enviarTramaDeDatos(interface_t * iface, unsigned char *mac_dst, unsigned char *type, int control, char tramaN, char direccion, char *cad, int longitud, bool e){
    unsigned char payload [longitud + 5];
    payload[0] =direccion;
    payload[1] = control;
    payload[2] = tramaN;
    payload[3] = longitud;
    for(int i = 0; i < longitud; i++){
        payload[i+4] = (unsigned char) cad[i];
    }

    payload[longitud + 4] = calcularBCE(cad);

    if (e){
        payload[4] = 135;//ç
    }
    unsigned char *trama = BuildFrame(iface->MACaddr, mac_dst, type, payload);

    SendFrame(iface, trama, sizeof(payload));
    free(trama);
}
