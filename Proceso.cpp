//
// Created by Spat on 06/09/18.
//

#include <fstream>
#include "Proceso.h"
using namespace std;

int Proceso::getPid() {
    return pid;
}

int Proceso::getTiempoLlegada() {
    return tiempoLlegada;
}

int Proceso::getTiempoEjecucion() {
    return tiempoEjecucion;
}

void Proceso::imprimeBasico() {
    cout << "Pid:" << pid << endl
         << "Tiempo de llegada:" << tiempoLlegada << endl
         << "Tiempo de ejecucion:" << tiempoEjecucion << endl
         << "Prioridad:" << prioridad << endl << endl;
}

void Proceso::imprimeCompleto() {
    cout << "Pid:" << pid << endl
         << "Tiempo de llegada:" << tiempoLlegada << endl
         << "Tiempo de ejecucion:" << tiempoEjecucion << endl
         << "Prioridad:" << prioridad << endl
         << "Tiempo espera:" << tiempoEspera << endl
         //<< "Tiempo finalizacion:" << tiempoFinalizacion << endl
         << "Estado:" << estado << endl << endl;
}

list<Proceso> Proceso::getListaProcesosDeArchivo() {
    list<Proceso> listaProcesos;

    ifstream archivoLeeProcesos("/Users/oscar/Documents/Escuela/Otoño 2018/Sistemas Operativos/Programas/GestorProcesos/Procesos.txt");

    if(archivoLeeProcesos.fail()){
        cout << "No se pudo abrir el archivo"<< endl;
    }
    else{
        Proceso procesoActual;
        string textoActual;
        while (!archivoLeeProcesos.eof()){
            getline(archivoLeeProcesos,textoActual);
            procesoActual.pid = stoi(textoActual);
            getline(archivoLeeProcesos,textoActual);
            procesoActual.tiempoLlegada = stoi(textoActual);
            getline(archivoLeeProcesos,textoActual);
            procesoActual.tiempoEjecucion = stoi(textoActual);
            getline(archivoLeeProcesos,textoActual);
            procesoActual.prioridad = stoi(textoActual);
            getline(archivoLeeProcesos,textoActual);
            listaProcesos.push_back(procesoActual);
        }
        cout << "Se han leido los procesos con exito! :D\n\n";
     }
    return listaProcesos;
}

void Proceso::reduceTiempoEjecucion() {
    if(tiempoEjecucion == 0){
        this->estado=2;
    } else {
        tiempoEjecucion = tiempoEjecucion-1;
        this->estado = 1;
    }
}

bool Proceso::finalizado() {
    return estado == 2;
}

void Proceso::setEstado(int estado) {
    this->estado =estado;
}

bool operator < (const Proceso &procesoA, const Proceso &procesoB) {
    ifstream archivoFormaProceso("/Users/oscar/Documents/Escuela/Otoño 2018/Sistemas Operativos/Programas/GestorProcesos/FormaProcesamiento.txt");
    string pesoTiempoEjecucion, pesoPrioridad, pesoPid;
    int posicionTiempoEjecucion;// posicionPrioridad, posicionPid;

    getline(archivoFormaProceso,pesoTiempoEjecucion);
    getline(archivoFormaProceso,pesoPrioridad);
    getline(archivoFormaProceso,pesoPid);
    archivoFormaProceso >> posicionTiempoEjecucion;
    //archivoFormaProceso >> posicionPrioridad;
    //archivoFormaProceso >> posicionPid;

    if(posicionTiempoEjecucion == 1){
        if(pesoTiempoEjecucion == "pesado"){
            if(procesoA.tiempoEjecucion == procesoB.tiempoEjecucion) {
                if(pesoPrioridad == "pesado"){
                    if(procesoA.prioridad == procesoB.prioridad) {
                        if(pesoPid == "descendente"){
                            return  (procesoB.pid < procesoA.pid);
                        } else
                            return  (procesoA.pid < procesoB.pid);
                    }
                    else
                        return  (procesoB.prioridad < procesoA.prioridad);
                }
                else{//pesoPrioridad = ligero
                    if(procesoA.prioridad == procesoB.prioridad) {
                        if(pesoPid == "descendente"){
                            return  (procesoB.pid < procesoA.pid);
                        } else
                            return  (procesoA.pid < procesoB.pid);
                    }
                    else
                        return procesoA.prioridad < procesoB.prioridad;
                }
            }
            else
                return  (procesoB.tiempoEjecucion < procesoA.tiempoEjecucion);
        }
        else if(pesoTiempoEjecucion == "ligero"){
            if(procesoA.tiempoEjecucion == procesoB.tiempoEjecucion) {
                if(pesoPrioridad == "pesado"){
                    if(procesoA.prioridad == procesoB.prioridad) {
                        if(pesoPid == "descendente"){
                            return  (procesoA.pid < procesoB.pid);
                        } else
                            return  (procesoB.pid < procesoA.pid);
                    }
                    else
                        return  (procesoB.prioridad < procesoA.prioridad);
                }
                else{// pesoPrioridad  = ligero
                    if(procesoA.prioridad == procesoB.prioridad) {
                        if(pesoPid == "descendente"){
                            return  (procesoA.pid < procesoB.pid);
                        } else
                            return  (procesoB.pid < procesoA.pid);
                    }
                    else
                        return procesoA.prioridad < procesoB.prioridad;
                }
            }
            else
                return (procesoA.tiempoEjecucion < procesoB.tiempoEjecucion);
        }
    }


    else if(posicionTiempoEjecucion == 2){
        if(pesoPrioridad == "pesado"){
            if(procesoA.prioridad == procesoB.prioridad) {
                if(pesoTiempoEjecucion == "pesado"){
                    if(procesoA.tiempoEjecucion == procesoB.tiempoEjecucion) {
                        if(pesoPid == "descendente"){
                            return  (procesoB.pid < procesoA.pid);
                        } else
                            return  (procesoA.pid < procesoB.pid);
                    }
                    else
                        return  (procesoB.tiempoEjecucion < procesoA.tiempoEjecucion);
                }
                else{//pesoTiempoEjecucion = Ligero
                    if(procesoA.tiempoEjecucion == procesoB.tiempoEjecucion) {
                        if(pesoPid == "descendente"){
                            return  (procesoB.pid < procesoA.pid);
                        } else
                            return  (procesoA.pid < procesoB.pid);
                    }
                    else
                        return procesoA.tiempoEjecucion < procesoB.tiempoEjecucion;
                }
            }
            else
                return  (procesoB.prioridad < procesoA.prioridad);
        }
        else if(pesoPrioridad == "ligero"){
            if(procesoA.prioridad == procesoB.prioridad) {
                if(pesoTiempoEjecucion == "pesado"){
                    if(procesoA.tiempoEjecucion == procesoB.tiempoEjecucion) {
                        if(pesoPid == "descendente"){
                            return  (procesoB.pid < procesoA.pid);
                        } else
                            return  (procesoA.pid < procesoB.pid);
                    }
                    else
                        return  (procesoB.tiempoEjecucion < procesoA.tiempoEjecucion);
                }
                else{//pesoTiempoEjecucion = Ligero
                    if(procesoA.tiempoEjecucion == procesoB.tiempoEjecucion) {
                        if(pesoPid == "descendente"){
                            return  (procesoB.pid < procesoA.pid);
                        } else
                            return  (procesoA.pid < procesoB.pid);
                    }
                    else
                        return procesoA.tiempoEjecucion < procesoB.tiempoEjecucion;
                }
            }
            else
                return (procesoA.prioridad < procesoB.prioridad);
        }
    }
}

void Proceso::setTiempoEspera(int tiempoEspera) {
    this->tiempoEspera = tiempoEspera;
}

int Proceso::getTiempoEspera() {
    return tiempoEspera;
}

bool operator==(const Proceso &procesoA, const Proceso &procesoB) {
    return procesoA.pid == procesoB.pid;
}
