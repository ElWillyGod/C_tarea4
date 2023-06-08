#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {

    TPersonasLDE* ListaPersonas;
    int max;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){

    TTablaPersonas tabla = new rep_tablaPersonas();

    tabla->ListaPersonas = new TPersonasLDE[max];
    
    for(int i = 0; i < max; i++){
        tabla->ListaPersonas[i] = crearTPersonasLDE();
    }

    tabla->max = max;

    return tabla;
}

void insertarPersonaEnTabla(TTablaPersonas &tabla, TPersona persona){

    int pos = funcionDeDispersion(nombreTPersona(persona)) % tabla->max;

   // TPersonasLDE lista = tabla->ListaPersonas[pos];

    insertarInicioDeTPersonasLDE(tabla->ListaPersonas[pos], persona);

    
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){

    return estaPersonaConNombreEnTPersonasLDE(tabla->ListaPersonas[funcionDeDispersion(nombre) % tabla->max],nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    return obtenerPersonaConNombreTPersonasLDE(tabla->ListaPersonas[funcionDeDispersion(nombre) % tabla->max],nombre);
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
    for(int i = 0; i< tabla->max; i ++){
        liberarTPersonasLDE(tabla->ListaPersonas[i]);
    }
    delete []tabla->ListaPersonas;
    delete tabla;
    tabla = NULL;
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
}