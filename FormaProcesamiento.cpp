//
// Created by Spat on 06/09/18.
//

#include "FormaProcesamiento.h"
#include <utility>
#include <iostream>
using namespace std;

void FormaProcesamiento::guardaEnArchivo() {
    ofstream archivo("/Users/oscar/Documents/Escuela/Otoño 2018/Sistemas Operativos/Programas/GestorProcesos/FormaProcesamiento.txt");
    archivo << pesoTiempoEjecucion << endl;
    archivo << pesoPrioridad << endl;
    archivo << pesoPid << endl;
    archivo << posicionTiempoEjecucion << endl;
    archivo << posicionPrioridad<< endl;
    archivo << posicionPid<< endl;
}

void FormaProcesamiento::setPesoTiempoEjecucion() {
    int opcionSeleccionada;
    cout << "Tiempo de ejecucion:\n"
         << "1.- pesado\n"
         << "2.- ligero\n";
    cout << "Ingrese opcion: ";
    cin >> opcionSeleccionada;
    if(opcionSeleccionada==1)
        pesoTiempoEjecucion = "pesado";
    if(opcionSeleccionada==2)
        pesoTiempoEjecucion = "ligero";
}

void FormaProcesamiento::setPesoPrioridad() {
    int opcionSeleccionada;
    cout << "Prioridad:\n"
         << "1.- pesado\n"
         << "2.- ligero\n"
         << "Ingrese opcion: ";
    cin >> opcionSeleccionada;
    if(opcionSeleccionada==1)
        pesoPrioridad = "pesado";
    if(opcionSeleccionada==2)
        pesoPrioridad = "ligero";
}

void FormaProcesamiento::setPesoPid() {
    int opcionSeleccionada;
    cout << "PID:\n"
         << "1.- ascendente\n"
         << "2.- descendente\n"
         << "Ingrese opcion: ";
    cin >> opcionSeleccionada;
    if(opcionSeleccionada==1)
        pesoPid = "ascendente";
    if(opcionSeleccionada==2)
        pesoPid = "descendente";
}

void FormaProcesamiento::imprime() {
    if(posicionPrioridad == 1){
        cout << "Prioridad: " << pesoPrioridad<< endl
             << "Tiempo de ejecucion: " << pesoTiempoEjecucion<< endl
             << "Pid: " << pesoPid << endl;
    }
    else if(posicionPrioridad == 2){
        cout << "Tiempo de ejecucion: " << pesoTiempoEjecucion << endl
             << "Prioridad: " << pesoPrioridad << endl
             << "Pid: " << pesoPid << endl;
    }
}

string FormaProcesamiento::getPesoTiempoEjecucion() {
    return pesoTiempoEjecucion;
}

string FormaProcesamiento::getPesoPrioridad() {
    return pesoPrioridad;
}

string FormaProcesamiento::getPesoPid() {
    return pesoPid;
}

void FormaProcesamiento::setOrdenProcesamiento() {
    int posicion;

    cout << "¿Que criterio desea evaluar primero?\n"
         << "1.- Tiempo de ejecucion\n"
         << "2.- Prioridad\n"
         << "Ingrese opcion: ";
        cin >> posicion;
    cout << endl;
    while(posicion <1 || posicion >2){
        cout << "Ingresa una opción valida!! 77\n"
             << "Ingrese opcion: ";
        cin >> posicion;
        cout << endl;
    }

    if(posicion == 1){
        posicionTiempoEjecucion = 1;
        posicionPrioridad = 2;
        posicionPid = 3;
        cout << "Orden de procesamiento:\n"
             << "1.- Tiempo de ejecucion\n"
             << "2.- Prioridad\n"
             << "3.- Pid\n\n";
    }
    else if(posicion == 2){
        posicionTiempoEjecucion = 2;
        posicionPrioridad = 1;
        posicionPid = 3;
        cout << "Orden de procesamiento:\n"
             << "1.- Prioridad\n"
             << "2.- Tiempo de ejecucion\n"
             << "3.- Pid\n\n";
    }
}

int FormaProcesamiento::getPosicionPrioridad() {
    return posicionPrioridad;
}

