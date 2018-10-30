//
// Created by Spat on 27/10/18.
//

#include "GestorRam.h"
#include <unordered_set>
using namespace std;
GestorRam::GestorRam() {
    tamaño = 0;
    llena = false;
    Memoria.clear();
}

void GestorRam::setTamaño(int _tamaño) {
    tamaño = _tamaño;
    for (int i = 0; i <tamaño; ++i) {
        Memoria.emplace_back(0);
    }
}

bool GestorRam::encolarProceso(int pidProceso, int memoriaSolicitada) {
    /*
    if(tieneHuecos()){
        compactar();
    }
     */

    bool procesoEncolado = false;
    list<string>::iterator itrRam;

    int posicionInsercion = -1;
    int tamañoBloque = 0;
    for (int i = 0; i <Memoria.size() ; ++i) {
        if(Memoria.at(i) == 0){
            tamañoBloque++;
        }
        if(tamañoBloque == memoriaSolicitada){
            posicionInsercion = i-memoriaSolicitada+1;
            break;
        }
    }

    if(posicionInsercion != -1){
        for (int j = posicionInsercion; j <posicionInsercion+memoriaSolicitada ; ++j) {
            Memoria.at(j) = pidProceso;
        }
        procesoEncolado = true;
    }

    if(!procesoEncolado && cabeEnMemoria(memoriaSolicitada) && !yaEstaEnRam(pidProceso))
        compactar();

    return procesoEncolado;
}

int GestorRam::memoriaDisponible() {
    int espacioDisponible = 0;
    for (unsigned i=0; i<Memoria.size(); i++){
        if(Memoria.at(i) == 0){
            espacioDisponible++;
        }
    }
    return espacioDisponible;
}

bool GestorRam::cabeEnMemoria(int memoriaSolicitada) {
    bool memoriaSufuciente = false;
    if(memoriaDisponible() >= memoriaSolicitada)
        memoriaSufuciente = true;
    return memoriaSufuciente;
}

void GestorRam::compactar() {

    std::vector<int>::iterator itr;

    int cantidadEliminados = 0;
    for (int i = 0; i <Memoria.size() ; ++i) {
        if(Memoria.at(i) == 0){
            Memoria.erase (Memoria.begin()+i);
            cantidadEliminados++;
            --i;
        }
    }

    /*
    for (itr = Memoria.begin() ; itr != Memoria.end(); ++itr){
        if(*itr == 0){
            Memoria.erase(itr);
        }
    }
     */

    for (int i = 0; i <cantidadEliminados; ++i) {
        Memoria.emplace_back(0);
    }

    /*
    while (Memoria.size() < tamaño){
        Memoria.emplace_back(0);
    }
     */

    cout << "\n\n****************************\n";
    cout << "Memoria compactada" << endl;
    for (itr = Memoria.begin();  itr != Memoria.end(); itr++) {
        if(*itr == 0)
            cout << "    |";
        else
            cout << " T" << *itr<< " |";
    }
    cout << "\n****************************\n\n";
}

bool GestorRam::quitaProceso(int pidProcesoAQuitar) {
    bool procesoEliminado = true;
    bool procesoEncontrado = false;
    std::vector<int>::iterator itr;
    for (unsigned i=0; i<Memoria.size(); i++){
        if(Memoria.at(i) == pidProcesoAQuitar){
            Memoria.at(i) = 0;
            procesoEncontrado = true;
        }
    }

    if (!procesoEncontrado){
        cout << "El proceso T" << pidProcesoAQuitar << ": No esta en memoria! D:" << endl;
    }

    for (unsigned i=0; i<Memoria.size(); i++){
        if(Memoria.at(i) == pidProcesoAQuitar){
             procesoEliminado = false;
        }
    }
    return procesoEliminado;
}

void GestorRam::imprime() {
    vector<int>::iterator itrRam;
    cout << "|";
    for (itrRam = Memoria.begin();  itrRam != Memoria.end(); itrRam++) {
        if(*itrRam == 0)
            cout << "    |";
        else
            cout << " T" << *itrRam << " |";
    }
    cout << endl;
}

vector<int> GestorRam::getMemoriaSinDuplicados() {
    vector<int> ramSinHuecos;
    ramSinHuecos = Memoria;
    for (unsigned i=0; i<ramSinHuecos.size(); ++i){
        if(ramSinHuecos.at(i) == 0){
            ramSinHuecos.erase(ramSinHuecos.begin()+i);
        }
    }

    unordered_set<int> mySet;
    unordered_set<int>::iterator iterator1;
    vector<int> ramSinRepetidos;
    for (int i=0; i<ramSinHuecos.size(); ++i){
        int a = ramSinHuecos.at(i);
        iterator1 = mySet.find(a);
        if(iterator1 == mySet.end()){
            mySet.insert(a);
            ramSinRepetidos.push_back(a);
        }
    }

    /*
    cout << "getMemoriaSinDuplicados = ";
    cout << "|";
    for(int i = 0; i<ramSinRepetidos.size(); ++i){
        cout << "[" << i << "]"<< ramSinRepetidos.at(i) << " |";
    }
    cout << endl;
    */
    return ramSinRepetidos;
}

void GestorRam::vaciar() {
    for (int i = 0; i <Memoria.size(); ++i) {
        Memoria.at(i) = 0;
    }
}

bool GestorRam::vacia() {
    bool vacia = true;
    for (int i = 0; i <Memoria.size() ; ++i) {
        if(Memoria.at(i) != 0){
            vacia = false;
            break;
        }
    }
    return vacia;
}

int GestorRam::size() {
    return tamaño;
}

bool GestorRam::yaEstaEnRam(int pidProceso) {
    bool enMemoria = false;
    for (unsigned i=0; i<Memoria.size(); i++){
        if(Memoria.at(i) == pidProceso){
            enMemoria = true;
            break;
        }
    }
    return enMemoria;
}

bool GestorRam::tieneHuecos() {
    bool hayHuecos = false;

    if(!vacia()){
        if(Memoria.front() == 0){
            hayHuecos = true;
        }
        else{
            for (int i = 0; i <Memoria.size() ; ++i) {
                if(Memoria.at(i) == 0 && !hayHuecos && Memoria.at(i++) != 0){
                    hayHuecos = true;
                }
            }
        }
    }
    return hayHuecos;
}

