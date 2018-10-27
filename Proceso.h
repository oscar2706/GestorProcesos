//
// Created by Spat on 06/09/18.
//

#ifndef GESTORPROCESOS_PROCESO_H
#define GESTORPROCESOS_PROCESO_H

#include <iostream>
#include <list>
#include <cstring>
#include "FormaProcesamiento.h"
using namespace std;

class Proceso {
private:
    int pid;
    int tiempoLlegada;
    int tiempoEjecucion;
    //int tiempoFinalizacion;
    int tiempoEspera;
    int prioridad;
    int estado;//0 en espera, 1 en ejecucion 2 finalizado
public:
    Proceso() {
        estado = 0;
        tiempoEspera=0;
    }
    int getPid();
    int getTiempoLlegada();
    int getTiempoEspera();
    int getTiempoEjecucion();
    bool finalizado();
    void reduceTiempoEjecucion();
    void imprimeBasico();
    void imprimeCompleto();
    void setTiempoEspera(int tiempoEspera);
    void setEstado(int estado);
    list<Proceso> getListaProcesosDeArchivo();
    friend bool operator < (const Proceso &procesoA, const Proceso &procesoB);
    friend bool operator == (const Proceso &procesoA, const Proceso &procesoB);
};

#endif //GESTORPROCESOS_PROCESO_H
