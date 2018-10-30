//
// Created by Spat on 27/10/18.
//

#ifndef GESTORPROCESOS_GESTORRAM_H
#define GESTORPROCESOS_GESTORRAM_H

#include <vector>
#include <string>
#include "Proceso.h"
class GestorRam {
private:
    int tamaño;
    bool llena;
    vector<int> Memoria;
public:
    GestorRam();
    bool encolarProceso(int proceso, int memoriaSolicitada);
    int memoriaDisponible();
    bool cabeEnMemoria(int memoriaSolicitada);
    bool quitaProceso(int pidProcesoAQuitar);
    bool yaEstaEnRam(int pidProceso);
    void compactar();
    void setTamaño(int _tamaño);
    void imprime();
    vector<int> getMemoriaSinDuplicados();
    void vaciar();
    bool vacia();
    int size();
};


#endif //GESTORPROCESOS_GESTORRAM_H
