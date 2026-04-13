#include "gestionPuerto.h"

void enviarCaracter(interface_t iface, char dato, unsigned char *mac_src, unsigned char *mac_dst, unsigned char *type){
    unsigned char *payload = (unsigned char *)malloc(sizeof(char));
    //Almacenamos el carácter a enviar en el payload de la trama, que en este caso será un único byte.
    payload[0] = dato;

    //Construimos la trama Ethernet
    unsigned char * frame = BuildFrame(mac_src, mac_dst, type, payload);
    
    //Enviamos la trama a través de la interfaz seleccionada, indicando que el tamaño del payload es de 1 byte.
    SendFrame(&iface, frame, 1);
    //Liberamos la memoria del payload, ya que BuildFrame hace una copia del payload que le pasamos, por lo que no necesitamos mantenerlo en memoria después de enviar la trama.
    free(payload);
}

unsigned char  recibirCaracter(interface_t iface){
    apacket_t d  = ReceiveFrame(&iface);
    const unsigned char *payload = d.packet;
    //Si hay algo en el payload de la trama recibida, lo devolvemos como carácter recibido. En caso contrario, devolvemos 0 para indicar que no se ha recibido ningún carácter.
    if (d.packet != nullptr && d.packet[14] > 0){
        payload = d.packet + 14;
        cout<<"Caracteres enviados: "<< "TODO" <<endl;
        return payload[0];
    }else{
        return 0;
    }
    
}
