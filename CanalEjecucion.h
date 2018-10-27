//
// Created by Spat on 06/09/18.
//

#ifndef GESTORPROCESOS_CANALEJECUCION_H
#define GESTORPROCESOS_CANALEJECUCION_H

#include "Proceso.h"

using namespace std;

class CanalEjecucion {
private:
    int id;
    Proceso procesoEnEjecucion;
    int tiempoEjecucionRestante;
    bool ocupado; //0=libre 1=ocupado
public:
    CanalEjecucion() {
        ocupado = false;
    }
    void setId(int _id);
    int asignaProceso(list<Proceso> ListaProcesosPendientes, int tiempoInicioEjecucion);//Regresa el tiempo de espera
    void ejecutaProceso();
    bool enUso();
    void setOcupado(bool estado);
    void liberaCanal();
    void imprime();
    Proceso regresaProceso();
    bool terminoEjecutarProceso();
    friend bool operator < (const CanalEjecucion &canal1, const CanalEjecucion &canal2){
        return  (canal1.id < canal2.id);
    };
};


#endif //GESTORPROCESOS_CANALEJECUCION_H
