//
// Created by Spat on 06/09/18.
//

#include "CanalEjecucion.h"

using namespace std;

int CanalEjecucion::asignaProceso(list<Proceso> ListaProcesosPendientes, int tiempoInicioEjecucion) {
    this->setOcupado(true);
    cout << "--- Canal " << id << "---\n";
    cout << "INGRESA PROCESO\n";
    list<Proceso>::iterator itrProceso;
    itrProceso = ListaProcesosPendientes.begin();

    procesoEnEjecucion = *itrProceso;
    procesoEnEjecucion.setTiempoEspera(tiempoInicioEjecucion - procesoEnEjecucion.getTiempoLlegada());
    procesoEnEjecucion.imprimeBasico();
    return procesoEnEjecucion.getTiempoEspera();
}

void CanalEjecucion::ejecutaProceso() {
    procesoEnEjecucion.reduceTiempoEjecucion();
    if(procesoEnEjecucion.getTiempoEjecucion() ==0 ){
        procesoEnEjecucion.setEstado(2);//Se marca como finalizado
        this->liberaCanal();
    }
}

void CanalEjecucion::liberaCanal() {
    ocupado = false;
}

bool CanalEjecucion::enUso() {
    return ocupado == 1;
}

void CanalEjecucion::setId(int _id) {
    id=_id;
}

void CanalEjecucion::imprime() {
    string seEstaOcupando;
    if(!ocupado)
        seEstaOcupando = "false";
    else
        seEstaOcupando = "true";
    cout << "--- Canal " << id << " ---"<< endl;
    cout << "ocupado = " << seEstaOcupando << endl;
    if(this->enUso()){
        cout << "Proceso asignado: " << procesoEnEjecucion.getPid() << endl;
    }
}

void CanalEjecucion::setOcupado(bool estado) {
    ocupado = estado;
}

Proceso CanalEjecucion::regresaProceso() {
    return procesoEnEjecucion;
}

bool CanalEjecucion::terminoEjecutarProceso() {
    return procesoEnEjecucion.finalizado();
}
