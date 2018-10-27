#include <iostream>
#include <cstring>
#include <list>
#include "Proceso.h"
#include "CanalEjecucion.h"
#include "FormaProcesamiento.h"

using namespace std;

void limpiaPantalla(){
    for (int i = 0; i <100; ++i) {
        cout << "\n";
    }
}


int main() {
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
                list<Proceso> ListaPendientes;
                list<Proceso> ListaAsignados;

                ListaPendientes.clear();
                int pasoProcesamiento=0;
                float tiempoEsperaTotal = 0;

                while(ListaAsignados.size() != ListaProcesos.size()){
                    cout << "----------------------------"<< endl;
                    cout << "\t\t>Paso :" << pasoProcesamiento << "<" << endl;
                    cout << "----------------------------"<< endl << endl;
                    //Ingresa procesos en tiempo de llegada conforme al paso actual de ejecucion
                    for (itrProceso = ListaProcesos.begin(); itrProceso != ListaProcesos.end(); itrProceso++)  {
                        if(itrProceso->getTiempoLlegada() == pasoProcesamiento)
                            ListaPendientes.push_back(*itrProceso);
                    }

                    ListaPendientes.sort();
                    for (itrProceso = ListaPendientes.begin(); itrProceso != ListaPendientes.end(); itrProceso++)
                      itrProceso->imprimeBasico();

                    //Asignacion de procesos a canales para su ejecucion
                    itrProceso = ListaPendientes.begin();


                        for(itrCanal = ListaCanales.begin(); itrCanal != ListaCanales.end(); itrCanal++){
                            if(itrCanal->enUso() == false && ListaPendientes.size() > 0){
                                tiempoEsperaTotal= tiempoEsperaTotal + itrCanal->asignaProceso(ListaPendientes, pasoProcesamiento);
                                ListaAsignados.push_back(itrCanal->regresaProceso());
                                ListaPendientes.pop_front();
                                itrProceso = ListaPendientes.begin();
                                itrCanal->ejecutaProceso();
                            } else{
                                itrCanal->imprime();
                                itrCanal->ejecutaProceso();
                            }
                        }

                    //cout << "\n->PROCESOS FINALIZADOS = " << ListaAsignados.size() << endl << endl;
                    pasoProcesamiento++;
                }
                cout << "Tiempo de espera total = " << tiempoEsperaTotal << endl;
                cout << "Tiempo de espera promedio = " << tiempoEsperaTotal/ListaProcesos.size() << endl << endl;
            }break;

            default:
                cout << "\nHasta la vista bby B)\n";
                break;
        }
    } while(opcionMenu !=0);
}