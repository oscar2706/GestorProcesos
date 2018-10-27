//
// Created by Spat on 06/09/18.
//

#ifndef GESTORPROCESOS_FORMAPROCESAMIENTO_H
#define GESTORPROCESOS_FORMAPROCESAMIENTO_H

#include <string>
#include <fstream>
using namespace std;

class FormaProcesamiento {
private:

    int posicionTiempoEjecucion;
    int posicionPrioridad;
    int posicionPid;
    //buscar otra palabra para el peso para evitar confusiones
    string pesoTiempoEjecucion;//pesado, ligero
    string pesoPrioridad;//pesado, ligero
    string pesoPid;//ascendente, descendente
public:
    FormaProcesamiento() {
        posicionTiempoEjecucion = 1;
        posicionPrioridad = 2;
        posicionPid = 3;
        pesoTiempoEjecucion = "";
        pesoPrioridad = "";
        pesoPid = "";
    }
    //1.- Tiempo ejecucion 2.- Prioridad 3.- PID
    void guardaEnArchivo();
    void setPesoTiempoEjecucion();
    void setPesoPrioridad();
    void setPesoPid();
    void setOrdenProcesamiento();
    void imprime();
    int getPosicionPrioridad();
    string getPesoTiempoEjecucion();
    string getPesoPrioridad();
    string getPesoPid();
};


#endif //GESTORPROCESOS_FORMAPROCESAMIENTO_H
