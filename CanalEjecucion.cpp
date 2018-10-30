//
// Created by Spat on 06/09/18.
//

#include "CanalEjecucion.h"

using namespace std;

int CanalEjecucion::asignaProceso(list<Proceso> ListaProcesosPendientes, int tiempoInicioEjecucion) {
    list<Proceso>::iterator itrProceso;
    itrProceso = ListaProcesosPendientes.begin();
    procesoEnEjecucion = *itrProceso;
    procesoEnEjecucion.setTiempoEspera(tiempoInicioEjecucion - procesoEnEjecucion.getTiempoLlegada());
    this->setOcupado(true);

    if(procesoEnEjecucion.getPid() == 0){
        Proceso procesoVacio;
        procesoEnEjecucion =  procesoVacio;
        cout << "--- Canal " << id+1 << "---\n";
        cout << "NO HACE NADA :v (por flojo)\n";
    } else{
        cout << "--- Canal " << id+1 << "---\n";
        cout << "INGRESA PROCESO\n";

        procesoEnEjecucion.imprimeConRam();
    }
    return procesoEnEjecucion.getTiempoEspera();
}

void CanalEjecucion::asignaProceso(Proceso procesoAsignado) {
    procesoEnEjecucion = procesoAsignado;
}

void CanalEjecucion::ejecutaProceso() {
    procesoEnEjecucion.reduceTiempoEjecucion();
    if(procesoEnEjecucion.getTiempoEjecucion() ==0 ){
        procesoEnEjecucion.setEstado(2);//Se marca como finalizo
        this->liberaCanal();
    }
}

void CanalEjecucion::ejecutaProcesoSinLiberar() {
    procesoEnEjecucion.reduceTiempoEjecucion();
    if(procesoEnEjecucion.getTiempoEjecucion() ==0 ){
        procesoEnEjecucion.setEstado(2);//Se marca como finalizo
    }
}

void CanalEjecucion::liberaCanal() {
    procesoEnEjecucion = Proceso();
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
    return procesoEnEjecucion.finalizo();
}

