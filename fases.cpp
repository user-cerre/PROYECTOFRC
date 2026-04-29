
#include "fases.h"

void faseDeEstablecimientoMaestro(interface_t *iface, unsigned char *mac_dst, unsigned char *type, apacket_t &recepcion){
    bool enc = false;
    enviarTramaDeControl(iface, mac_dst, type, 05, '0', 'R');
    while(!enc){
        recepcion = ReceiveFrame(iface);
        if(recepcion.packet != nullptr){
            if(recepcion.packet[15] == 06 && recepcion.packet[12] == type[0] && recepcion.packet[16] == '0' && recepcion.packet[13] == 2 && recepcion.packet[14] == 'R'){//ACK, el mismo número de grupo y enviado por el esclavo
                enc = true;
                cout<<"R R ACK 0"<<endl;
            }
        }
    }//Aqui se llama a transferencia maestro
}
void faseDeEstablecimientoEsclavo(interface_t *iface, unsigned char *type){
    apacket_t recepcion;
    char car = 0;
    unsigned char mac_dst[6];
    while(car != 27){
        if(kbhit()){
            car = getch();
        }else{
            //Establecimiento
            recepcion = ReceiveFrame(iface);
            if (recepcion.packet != nullptr){
                if(recepcion.packet[15] == 05 && recepcion.packet[12] == type[0] && recepcion.packet[13] == 1 && recepcion.packet[14] =='R' && recepcion.packet[16] == '0'){
                    cout<<"R R ENQ 0"<<endl;
                    for(int i = 0; i<6 ; i++){
                        mac_dst[i]= recepcion.packet[i+6];
                    }
                    enviarTramaDeControl(iface, mac_dst, type, 06, '0', 'R');

                    //Aquí va la transferencia de esclavo
                    faseDeTransferenciaEsclavo(iface, mac_dst, type, car);
                }
            }
            
        }
    }
}

void faseDeTransferenciaMestro(interface_t *iface, unsigned char *mac_dst, unsigned char *type, apacket_t &recepcion){//Revisar como unir las fases entre ellas
    char cad[255];
    char tramaN = '0';
    bool enc = false;
    ifstream lectura("EProtoc.txt");
    if(lectura.is_open()){
        while(!lectura.eof()){
            lectura.read(cad, 254);
            cad[lectura.gcount()] = '\0';
            if(lectura.gcount() > 0){
                enviarTramaDeDatos(iface, mac_dst, type, 02, tramaN, 'R', cad, lectura.gcount());
                cout<<"E R STX "<<tramaN<<" "<< (int)calcularBCE(cad)<<endl;
                // cout<<"<<<<<"<<endl;
                while(!enc){
                    recepcion = ReceiveFrame(iface);
                    if(recepcion.packet != nullptr){
                        if(recepcion.packet[15] == 06 && recepcion.packet[12] == type[0] && recepcion.packet[16] == tramaN && recepcion.packet[13] == 2 && recepcion.packet[14] == 'R'){//ACK, el mismo número de grupo y enviado por el esclavo
                            enc = true;
                            cout<<"<<<<<<<<<"<<endl;//! ERROR AQUÍ, NUNCA ENTRA SOLO EN EL FINAL
                            cout<<"R R ACK "<<recepcion.packet[16]<<endl;
                        }
                    }
                }
                if(tramaN == '0'){
                    tramaN = '1';
                }else{
                    tramaN = '0';
                }
            }
        }
        lectura.close();
    }
}
void faseDeTransferenciaEsclavo(interface_t *iface, unsigned char *mac_dst, unsigned char *type, char &car){
    bool enc = false;
    apacket_t recepcion;
    char tramaN = '0';
    ofstream escritura;

    escritura.open("RProto.txt");
    if(escritura.is_open()){
        while(!enc){
            recepcion = ReceiveFrame(iface);
            if(recepcion.packet != nullptr){
                if(recepcion.packet[15] == 02 && recepcion.packet[12] == type[0] && recepcion.packet[13] == 1 && recepcion.packet[14] =='R' && recepcion.packet[16] == tramaN){
                    char cad[recepcion.packet[17]+ 1];
                    for (int i = 0; i< recepcion.packet[17]; i++){
                        cad[i] = recepcion.packet[18+i];
                    }
                    cad[recepcion.packet[17]]= '\0';
                    cout <<"R R STX"<<" "<<tramaN<<" "<<(int) recepcion.packet[recepcion.packet[17]+ 18]<<" "<<(int)calcularBCE(cad)<<endl; 

                    if(calcularBCE(cad) == recepcion.packet[recepcion.packet[17]+ 18]){
                        escritura.write(cad, recepcion.packet[17]);
                        enviarTramaDeControl(iface, mac_dst, type, 06, tramaN, 'R');
                        if(tramaN == '0'){
                            tramaN = '1';
                        }else {
                            tramaN = '0';
                        }
                    }
                }
                if(recepcion.packet[15] == 04 && recepcion.packet[12] == type[0] && recepcion.packet[13] == 1 && recepcion.packet[14] =='R' && recepcion.packet[16] == '0'){
                    cout<<"R R EOT 0"<<endl;
                    enc = true;
                    escritura.close();
                    enviarTramaDeControl(iface, mac_dst, type, 06, '0', 'R');
                    car = 27;
                }
            }
        }
    }
}

void faseDeCierre(interface_t *iface, unsigned char *mac_dst, unsigned char *type){
    enviarTramaDeControl(iface, mac_dst, type, 04, '0', 'R');
    bool enc = false;
    apacket_t recepcion;
    while(!enc){
        recepcion = ReceiveFrame(iface);
        if(recepcion.packet != nullptr){
            if(recepcion.packet[15] == 06 && recepcion.packet[12] == type[0] && recepcion.packet[16] == '0' && recepcion.packet[13] == 2 && recepcion.packet[14] == 'R'){//ACK, el mismo número de grupo y enviado por el esclavo
                enc = true;
                cout<<"R R ACK "<<recepcion.packet[16]<<endl;
            }
        }
    }
}