#include <iostream>
#include <cstring>
#include <list>
#include <functional>
#include "Proceso.h"
#include "CanalEjecucion.h"
#include "FormaProcesamiento.h"
#include "GestorRam.h"
using namespace std;

void limpiaPantalla(){
    for (int i = 0; i <100; ++i) {
        cout << "\n";
    }
}

void ejecutaMonotarea(){
    int opcionMenu;
    list <Proceso> ListaProcesos;
    list <CanalEjecucion> ListaCanales;
    Proceso procesoActual;
    FormaProcesamiento formaProcesamiento;
    CanalEjecucion canalActual;
    list <Proceso>::iterator itrProceso;
    list <CanalEjecucion>::iterator itrCanal;
    do{
        cout << "\tOpciones del sistema: \n"
             << "\t1.- Lee procesos desde archivo\n"
             << "\t2.- Asigna ponderacion ejecucion\n"
             << "\t3.- Asigna cantidad de Canales\n"
             << "\t4.- Ejecuta los procesos\n"
             << "\t0.- Salir\n"
             << "--> Opcion a realizar: ";
        cin >> opcionMenu;

        while (opcionMenu <0 || opcionMenu>4){
            cout << "Ingrese opcion disponible!! 77\n";
            cout << "Opcion a realizar: ";
            cin >> opcionMenu;
        }

        switch (opcionMenu){
            case 1:{
                limpiaPantalla();
                ListaProcesos = procesoActual.getListaProcesosDeArchivo();
                cout << "Lista de procesos leidos del archivo: \n";
                for (itrProceso = ListaProcesos.begin(); itrProceso != ListaProcesos.end(); itrProceso++) {
                    itrProceso->imprimeBasico();
                }
            }break;

            case 2:{
                limpiaPantalla();
                formaProcesamiento.setOrdenProcesamiento();
                if(formaProcesamiento.getPosicionPrioridad() == 1){
                    formaProcesamiento.setPesoPrioridad();
                    cout << endl;
                    formaProcesamiento.setPesoTiempoEjecucion();
                    cout << endl;
                    formaProcesamiento.setPesoPid();
                    cout << "\n\n";
                    formaProcesamiento.imprime();
                    cout << "\n";
                    formaProcesamiento.guardaEnArchivo();
                }
                else if(formaProcesamiento.getPosicionPrioridad() == 2){
                    formaProcesamiento.setPesoTiempoEjecucion();
                    cout << endl;
                    formaProcesamiento.setPesoPrioridad();
                    cout << endl;
                    formaProcesamiento.setPesoPid();
                    cout << "\n\n";
                    formaProcesamiento.imprime();
                    cout << "\n";
                    formaProcesamiento.guardaEnArchivo();
                }

            }break;

            case 3:{
                limpiaPantalla();

                int cantCanales;
                cout << "Ingrese cantidad de canales: ";
                cin >> cantCanales;
                ListaCanales.clear();
                for( int i = 0; i< cantCanales; i++){
                    canalActual.setId(i);
                    ListaCanales.push_back(canalActual);
                }
                for (itrCanal = ListaCanales.begin(); itrCanal != ListaCanales.end(); itrCanal++)
                    itrCanal->imprime();
            }break;

            case 4:{
                limpiaPantalla();
                list<Proceso> ProcesosPendientes;
                list<Proceso> ProcesosAsignados;

                ProcesosPendientes.clear();
                int pasoProcesamiento=0;
                float tiempoEsperaTotal = 0;

                while(ProcesosAsignados.size() != ListaProcesos.size()){
                    cout << "----------------------------"<< endl;
                    cout << "\t\t>Paso :" << pasoProcesamiento << "<" << endl;
                    cout << "----------------------------"<< endl << endl;
                    //Ingresa procesos en tiempo de llegada conforme al paso actual de ejecucion
                    for (itrProceso = ListaProcesos.begin(); itrProceso != ListaProcesos.end(); itrProceso++)  {
                        if(itrProceso->getTiempoLlegada() == pasoProcesamiento)
                            ProcesosPendientes.push_back(*itrProceso);
                    }

                    ProcesosPendientes.sort();
                    for (itrProceso = ProcesosPendientes.begin(); itrProceso != ProcesosPendientes.end(); itrProceso++)
                        itrProceso->imprimeBasico();

                    //Asignacion de procesos a canales para su ejecucion
                    itrProceso = ProcesosPendientes.begin();


                    for(itrCanal = ListaCanales.begin(); itrCanal != ListaCanales.end(); itrCanal++){
                        if(itrCanal->enUso() == false && ProcesosPendientes.size() > 0){
                            tiempoEsperaTotal= tiempoEsperaTotal + itrCanal->asignaProceso(ProcesosPendientes, pasoProcesamiento);
                            ProcesosAsignados.push_back(itrCanal->regresaProceso());
                            ProcesosPendientes.pop_front();
                            itrProceso = ProcesosPendientes.begin();
                            itrCanal->ejecutaProceso();
                        } else{
                            itrCanal->imprime();
                            itrCanal->ejecutaProceso();
                        }
                    }

                    //cout << "\n->PROCESOS FINALIZADOS = " << ProcesosAsignados.size() << endl << endl;
                    pasoProcesamiento++;
                }
                cout << "\n\n--> Tiempos de espera <--\n\n";
                for (itrProceso = ProcesosAsignados.begin(); itrProceso != ProcesosAsignados.end(); itrProceso++)
                    itrProceso->imprimeCompleto();
                cout << "Tiempo de espera total = " << tiempoEsperaTotal << endl;
                cout << "Tiempo de espera promedio = " << tiempoEsperaTotal/ListaProcesos.size() << endl << endl;
            }break;

            default:
                break;
        }
    } while(opcionMenu !=0);
}

void ejecutaMultitarea(){
    int opcionMenu;
    list <Proceso> ListaProcesos;
    list <CanalEjecucion> ListaCanales;
    Proceso procesoActual;
    FormaProcesamiento formaProcesamiento;
    CanalEjecucion canalActual;
    list <Proceso>::iterator itrProceso;
    list <CanalEjecucion>::iterator itrCanal;
    GestorRam ramPantalla; //Representacion en pantalla de la ram
    do{
        cout << "\tOpciones del sistema: \n"
             << "\t1.- Lee procesos desde archivo\n"
             << "\t2.- Asigna ponderacion ejecucion\n"
             << "\t3.- Asigna cantidad de Canales\n"
             << "\t4.- Asigna ram del gestor\n"
             << "\t5.- Ejecuta los procesos\n"
             << "\t0.- Salir\n"
             << "--> Opcion a realizar: ";
        cin >> opcionMenu;

        while (opcionMenu <0 || opcionMenu>5){
            cout << "Ingrese opcion disponible!! 77\n";
            cout << "Opcion a realizar: ";
            cin >> opcionMenu;
        }

        switch (opcionMenu){
            case 1:{
                limpiaPantalla();
                ListaProcesos = procesoActual.getListaProcesosDeArchivo();
                cout << "Lista de procesos leidos del archivo: \n";
                for (itrProceso = ListaProcesos.begin(); itrProceso != ListaProcesos.end(); itrProceso++) {
                    itrProceso->imprimeConRam();
                }
            }break;

            case 2:{
                limpiaPantalla();
                formaProcesamiento.setOrdenProcesamiento();
                if(formaProcesamiento.getPosicionPrioridad() == 1){
                    formaProcesamiento.setPesoPrioridad();
                    cout << endl;
                    formaProcesamiento.setPesoTiempoEjecucion();
                    cout << endl;
                    formaProcesamiento.setPesoPid();
                    cout << "\n\n";
                    formaProcesamiento.imprime();
                    cout << "\n";
                    formaProcesamiento.guardaEnArchivo();
                }
                else if(formaProcesamiento.getPosicionPrioridad() == 2){
                    formaProcesamiento.setPesoTiempoEjecucion();
                    cout << endl;
                    formaProcesamiento.setPesoPrioridad();
                    cout << endl;
                    formaProcesamiento.setPesoPid();
                    cout << "\n\n";
                    formaProcesamiento.imprime();
                    cout << "\n";
                    formaProcesamiento.guardaEnArchivo();
                }
            }break;

            case 3:{
                limpiaPantalla();

                int cantCanales;
                cout << "Ingrese cantidad de canales: ";
                cin >> cantCanales;
                ListaCanales.clear();
                for( int i = 0; i< cantCanales; i++){
                    canalActual.setId(i);
                    ListaCanales.push_back(canalActual);
                }
                for (itrCanal = ListaCanales.begin(); itrCanal != ListaCanales.end(); itrCanal++)
                    itrCanal->imprime();
            }break;

            case 4:{
                limpiaPantalla();
                int tamañoRam;
                cout << "Ingresa tamaño de la memoria ram: ";
                cin >> tamañoRam;
                ramPantalla.setTamaño(tamañoRam);
                ramPantalla.imprime();
            }break;

            case 5:{
                limpiaPantalla();
                list<Proceso> ProcesosPendientes;
                list<Proceso> ProcesosEjecutandose;
                list<Proceso> ProcesosFinalizados;
                list<Proceso> ProcesosQueNoCaben;
                list<Proceso> ProcesosRam; //Lista que contiene los procesos que estan en RAM
                list<Proceso> ProcesosHDD;


                ProcesosPendientes.clear();
                int pasoProcesamiento=0;
                float tiempoEsperaTotal = 0;

                auto cantidadProcesos = ListaProcesos.size();
                auto cantidadProcesosFinalizados = ProcesosFinalizados.size();
                //cantidadProcesosFinalizados != cantidadProcesos
                while(cantidadProcesosFinalizados != cantidadProcesos){
                    cout << "=================================================="<< endl;
                    cout << "                    > Paso " << pasoProcesamiento << " <" << endl;
                    cout << "=================================================="<< endl << endl;

                    //Vacia la ram y el hdd si ya no hay procesos pendientes


                    if(ProcesosPendientes.empty() && !ProcesosRam.empty() && ProcesosQueNoCaben.empty()){
                        list <Proceso>::iterator itrProceso2;
                        cout << "=======> Se vacia la ram y el disco duro! <=======" << endl;
                        cout << "-> Memoria Ram = ";
                        ramPantalla.imprime();
                        cout << "->HDD = ";
                        for (itrProceso = ProcesosHDD.begin(); itrProceso != ProcesosHDD.end(); itrProceso++){
                            cout << "T" << itrProceso->getPid() << ", ";
                        }
                        cout << endl;

                        ProcesosRam.sort();
                        ProcesosHDD.sort();
                        list<Proceso> ProcesosRamOriginales;
                        //cout << "----------> Ram <----------"<< endl;
                        for (itrProceso = ProcesosRam.begin(); itrProceso != ProcesosRam.end(); itrProceso++){
                            //itrProceso->imprimeConRam();
                            for (itrProceso2 = ListaProcesos.begin(); itrProceso2 != ListaProcesos.end(); itrProceso2++){
                                if(itrProceso->getPid() == itrProceso2->getPid()) {
                                    ProcesosRamOriginales.push_back(*itrProceso2);
                                }
                            }
                        }
                        //cout << "---------------------------"<< endl;
                        //cout << "----------> HDD <----------"<< endl;
                        list<Proceso> ProcesosHDDOriginales;
                        for (itrProceso = ProcesosHDD.begin(); itrProceso != ProcesosHDD.end(); itrProceso++){
                            //itrProceso->imprimeConRam();
                            for (itrProceso2 = ListaProcesos.begin(); itrProceso2 != ListaProcesos.end(); itrProceso2++){
                                if(itrProceso->getPid() == itrProceso2->getPid())
                                    ProcesosHDDOriginales.push_back(*itrProceso2);
                            }
                        }
                        //cout << "---------------------------"<< endl;

                        ProcesosPendientes.merge(ProcesosRamOriginales);
                        ProcesosPendientes.merge(ProcesosHDDOriginales);
                        ProcesosRam.clear();
                        ProcesosHDD.clear();
                        ramPantalla.vaciar();

                        cout << "-> Memoria Ram = ";
                        ramPantalla.imprime();
                        cout << "-> HDD = ";
                        for (itrProceso = ProcesosHDD.begin(); itrProceso != ProcesosHDD.end(); itrProceso++){
                            cout << "T" << itrProceso->getPid() << ", ";
                        }
                        cout << endl << endl;
                    }

                    //Agrega elementos que no pudieron ser ejecutados en el paso anterior
                    if(!ProcesosQueNoCaben.empty()){
                        ProcesosQueNoCaben.sort();
                        list<Proceso> ProcesosQueNoCabenOriginales;
                        list <Proceso>::iterator itrProceso2;
                        for (itrProceso = ProcesosQueNoCaben.begin(); itrProceso != ProcesosQueNoCaben.end(); itrProceso++){
                            for (itrProceso2 = ListaProcesos.begin(); itrProceso2 != ListaProcesos.end(); itrProceso2++){
                                if(itrProceso->getPid() == itrProceso2->getPid())
                                    ProcesosQueNoCabenOriginales.push_back(*itrProceso2);
                            }
                        }
                        ProcesosQueNoCabenOriginales.sort();
                        ProcesosPendientes.merge(ProcesosQueNoCabenOriginales);
                    }

                    int cantidadProcesosRestantes = 0; //cantidad de procesos nuevos ingresados en el paso de ejecucion actual
                    //Ingresa procesos en tiempo de llegada conforme al paso actual de ejecucion
                    for (itrProceso = ListaProcesos.begin(); itrProceso != ListaProcesos.end(); itrProceso++)  {
                        if(itrProceso->getTiempoLlegada() == pasoProcesamiento){
                            ProcesosPendientes.push_back(*itrProceso);
                        }
                    }

                    ProcesosPendientes.sort();
                    for (itrProceso = ProcesosPendientes.begin(); itrProceso != ProcesosPendientes.end(); itrProceso++)
                        itrProceso->imprimeConRam();

                    //Asignacion de procesos a canales para su ejecucion
                    int procesosTerminados = 0;
                    for(itrCanal = ListaCanales.begin(); itrCanal != ListaCanales.end(); itrCanal++){
                        itrCanal->asignaProceso(ProcesosPendientes, pasoProcesamiento);
                        //itrCanal->ejecutaProcesoSinLiberar();
                        if(itrCanal->enUso()){
                            if(ramPantalla.cabeEnMemoria(itrCanal->regresaProceso().getRam()) || ramPantalla.yaEstaEnRam(ProcesosPendientes.begin()->getPid()) ){
                                //ramPantalla.compactar();
                                if(ramPantalla.encolarProceso(ProcesosPendientes.begin()->getPid(),ProcesosPendientes.begin()->getRam())){
                                    cout << "--> Memoria Ram = ";
                                    ramPantalla.imprime();
                                    cout << endl;
                                    ProcesosPendientes.pop_front();
                                    bool enListaEjecutandose = false;
                                    for (itrProceso = ProcesosEjecutandose.begin(); itrProceso != ProcesosEjecutandose.end(); itrProceso++){
                                        if(itrProceso->getPid() == itrCanal->regresaProceso().getPid()){
                                            itrCanal->liberaCanal();
                                            itrCanal->asignaProceso(*itrProceso);
                                            itrCanal->ejecutaProcesoSinLiberar();
                                            *itrProceso = itrCanal->regresaProceso();
                                            enListaEjecutandose = true;
                                        }
                                    }
                                    if(!enListaEjecutandose) {

                                        itrCanal->ejecutaProcesoSinLiberar();
                                        ProcesosEjecutandose.push_back(itrCanal->regresaProceso());
                                    }


                                    if(itrCanal->regresaProceso().finalizo()){
                                        procesosTerminados++;
                                        int tiempoEjecucion = itrCanal->regresaProceso().getTiempoEjecucion();
                                        int tiempoLlegada = itrCanal->regresaProceso().getTiempoLlegada();
                                        int tiempoEspera = pasoProcesamiento - tiempoEjecucion - tiempoLlegada;

                                        itrCanal->regresaProceso().setTiempoEspera(tiempoEspera);
                                        cout << "\t-----> ¡T"<< itrCanal->regresaProceso().getPid() << " SE MURIO! D: <-----" << endl << endl;

                                        ProcesosFinalizados.push_back(itrCanal->regresaProceso());
                                        ++cantidadProcesosFinalizados;
                                        itrCanal->liberaCanal();
                                        //ProcesosPendientes.pop_front();
                                        tiempoEsperaTotal += tiempoEspera;
                                    }

                                }
                            } else{

                                if(ProcesosPendientes.begin()->getRam() > ramPantalla.size()){
                                    cout << "El proceso T" << ProcesosPendientes.begin()->getPid();
                                    cout << " no se podra ejecutar! falta memoria ram :C, YA COMPRA MÁS 77" << endl;
                                    cout << "-----> T"<< ProcesosPendientes.begin()->getPid() << " ELIMINADO >:v" << endl << endl;
                                    ProcesosPendientes.pop_front();
                                    --cantidadProcesos;
                                } else{

                                    bool procesoIngresadoEnRam = false;
                                    bool sePuedeInsertar = true;
                                    ProcesosPendientes.pop_front();
                                    do {
                                        /*
                                        if(cantidadProcesosRestantes == 0  && !ramPantalla.cabeEnMemoria(itrCanal->regresaProceso().getRam())){
                                            ProcesosQueNoCaben.push_back(itrCanal->regresaProceso());
                                            itrCanal->liberaCanal();
                                            cout << "\n=====> El proceso se ejecutará en el siguiente paso! <=====\n\n";
                                            sePuedeInsertar = false;
                                            break;
                                        }
                                        */
                                        if(ProcesosRam.back().getPid() == 0){
                                            cout << "==> Se pasa el proceso T" << itrCanal->regresaProceso().getPid() << " al siguiente paso <==" << endl;
                                            bool enListaEjecutandose = false;
                                            for (itrProceso = ProcesosEjecutandose.begin(); itrProceso != ProcesosEjecutandose.end(); itrProceso++){
                                                if(itrProceso->getPid() == itrCanal->regresaProceso().getPid()){
                                                    itrCanal->liberaCanal();
                                                    itrCanal->asignaProceso(*itrProceso);
                                                    ProcesosQueNoCaben.push_back(itrCanal->regresaProceso());
                                                    itrCanal->ejecutaProcesoSinLiberar();
                                                    *itrProceso = itrCanal->regresaProceso();
                                                    enListaEjecutandose = true;
                                                }
                                            }
                                            if(!enListaEjecutandose) {
                                                ProcesosQueNoCaben.push_back(itrCanal->regresaProceso());
                                                itrCanal->ejecutaProcesoSinLiberar();
                                                ProcesosEjecutandose.push_back(itrCanal->regresaProceso());
                                            }
                                            break;
                                        }
                                        cout << "--> Memoria Ram = ";
                                        ramPantalla.imprime();
                                        cout << "¡No hay espacio para T" << itrCanal->regresaProceso().getPid() << " en ram! :C" << endl;
                                        cout << "\tSe pasa proceso: T" << ProcesosRam.back().getPid() << " a HDD" << endl;
                                        ramPantalla.quitaProceso(ProcesosRam.back().getPid());
                                        cout << "--> Memoria Ram = ";
                                        ramPantalla.imprime();
                                        ProcesosHDD.push_back(ProcesosRam.back());
                                        ProcesosRam.pop_back();
                                        cout << "--> HDD = ";
                                        for (itrProceso = ProcesosHDD.begin(); itrProceso != ProcesosHDD.end(); itrProceso++){
                                            cout << "T" << itrProceso->getPid() << ", ";
                                        }
                                        cout << endl << endl;

                                        int pidProceso = itrCanal->regresaProceso().getPid();
                                        int ramProceso = itrCanal->regresaProceso().getRam();
                                        //ramPantalla.compactar();
                                        procesoIngresadoEnRam = ramPantalla.encolarProceso(pidProceso,ramProceso);
                                        if(procesoIngresadoEnRam){
                                            cout << "--> Memoria Ram = ";
                                            ramPantalla.imprime();
                                            cout << endl;

                                            bool enListaEjecutandose = false;

                                     //AQUI
                                            if(pasoProcesamiento == 4 && itrCanal->regresaProceso().getPid()==3){

                                            }

                                            for (itrProceso = ProcesosEjecutandose.begin(); itrProceso != ProcesosEjecutandose.end(); itrProceso++){
                                                if(itrProceso->getPid() == itrCanal->regresaProceso().getPid()){
                                                    itrCanal->liberaCanal();
                                                    itrCanal->asignaProceso(*itrProceso);
                                                    itrCanal->ejecutaProcesoSinLiberar();
                                                    *itrProceso = itrCanal->regresaProceso();
                                                    enListaEjecutandose = true;

                                                    if(itrCanal->regresaProceso().finalizo()){
                                                        ProcesosQueNoCaben.clear();
                                                        procesosTerminados++;
                                                        int tiempoEjecucion = itrCanal->regresaProceso().getTiempoEjecucion();
                                                        int tiempoLlegada = itrCanal->regresaProceso().getTiempoLlegada();
                                                        int tiempoEspera = pasoProcesamiento - tiempoEjecucion - tiempoLlegada;

                                                        itrCanal->regresaProceso().setTiempoEspera(tiempoEspera);
                                                        cout << "\t-----> ¡T"<< itrCanal->regresaProceso().getPid() << " SE MURIO! D: <-----" << endl << endl;

                                                        ProcesosFinalizados.push_back(itrCanal->regresaProceso());
                                                        ++cantidadProcesosFinalizados;
                                                        itrCanal->liberaCanal();
                                                        //ProcesosPendientes.pop_front();
                                                        tiempoEsperaTotal += tiempoEspera;
                                                    }

                                                    break;
                                                }
                                            }
                                            if(!enListaEjecutandose) {
                                                itrCanal->ejecutaProcesoSinLiberar();
                                                ProcesosEjecutandose.push_back(itrCanal->regresaProceso());
                                            }
                                        }
                                    }while(!procesoIngresadoEnRam && sePuedeInsertar);

                                }
                            }
                        } else{
                            cout << "--> Memoria Ram = ";
                            ramPantalla.imprime();
                            cout << endl;
                            ProcesosPendientes.pop_front();
                        }
                    }

                    if(procesosTerminados >0){
                        int procesosEliminados = 0;
                        for (int i = 0; i <procesosTerminados ; ++i) {
                            itrProceso = ProcesosFinalizados.end();
                            for (int i = 0; i <procesosTerminados-procesosEliminados; ++i) {
                                itrProceso--;
                            }
                            if(ramPantalla.quitaProceso(itrProceso->getPid())){
                                ++procesosEliminados;
                            } else
                                cout << "No se pudo quitar de ramPantalla el proceso: T"<< itrProceso->getPid() << endl;
                        }
                        cout << "--> Memoria Ram = ";
                        ramPantalla.imprime();
                        cout << endl;
                    }

                    //Ingresa los procesos del paso actual a ProcesosRam en el orden que estan en ramPantalla
                    if(!ramPantalla.vacia()){
                        //Quita los duplicados de ramPantalla en el nuevo vector: ramSinDuplicados
                        vector<int> ramSinDuplicados = ramPantalla.getMemoriaSinDuplicados();
                        for(int i = 0; i<ramSinDuplicados.size(); ++i){
                            for(itrCanal = ListaCanales.begin(); itrCanal != ListaCanales.end(); itrCanal++)
                                if(itrCanal->regresaProceso().getPid() != 0 && itrCanal->regresaProceso().getPid() == ramSinDuplicados.at(i)){
                                    ProcesosRam.push_back(itrCanal->regresaProceso());
                                    itrCanal->liberaCanal();
                                }
                        }
                    }

                    //Imprime list<Proceso> ProcesosRam
                    cout << "--> Procesos en ram = ";
                    for (itrProceso = ProcesosRam.begin(); itrProceso != ProcesosRam.end(); itrProceso++)
                        cout << "T" << itrProceso->getPid() << ", ";
                    cout << endl << endl;
                    pasoProcesamiento++;
                }

                /*
                cout << "\n\n*********************************************"<< endl;
                for (itrProceso = ProcesosFinalizados.begin(); itrProceso != ProcesosFinalizados.end(); itrProceso++)
                    itrProceso->imprimeCompleto();
                cout << "*********************************************\n\n";
                 */

            }break;

            default:
                break;
        }
    } while(opcionMenu !=0);
}

int main() {
    int opcionMenu;
    do{
        cout << "Tipo de gestor!\n";
        cout << "1.-Monotarea\n";
        cout << "2.-Multitarea\n";
        cout << "0.-Salir\n";
        cout << "Ingrese opción: ";
        cin >> opcionMenu;

        switch (opcionMenu){
            case 1:{
                cout << "\n\n==========================================================\n\n";
                ejecutaMonotarea();
                cout << "\n\n==========================================================\n\n";
            }break;

            case 2:{
                cout << "\n\n==========================================================\n\n";
                ejecutaMultitarea();
                cout << "\n\n==========================================================\n\n";
            }break;

            default:{
                while(opcionMenu<0 || opcionMenu>2){
                    cout << "Opcion no disponible!! 77\n";
                    cout << "Ingrese opción: ";
                    cin >> opcionMenu;
                }
            }break;
        }
    }while(opcionMenu >0 && opcionMenu <= 2);
    cout << "\n\nHasta la vista beibe B)" << endl;
}