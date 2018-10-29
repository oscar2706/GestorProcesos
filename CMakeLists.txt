cmake_minimum_required(VERSION 3.10)
project(GestorProcesos)

set(CMAKE_CXX_STANDARD 11)

add_executable(GestorProcesos main.cpp Proceso.cpp Proceso.h CanalEjecucion.cpp CanalEjecucion.h FormaProcesamiento.cpp FormaProcesamiento.h GestorRam.cpp GestorRam.h)