#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"
#include "../include/tablaPersonas.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){

TColaDePrioridadPersona resultado = crearCP(MAX_ID);

for(nat i = 0; i<n; i++){
    if(perteneceATTablaPersonas(t,nombres[i])){
        insertarEnCP(copiarTPersona(obtenerPersonaDeTTablaPersonas(t,nombres[i])), resultado);
    }
}
while (!estaVaciaCP(resultado))
{
    imprimirTPersona(prioritaria(resultado));
    eliminarPrioritaria(resultado);
}
liberarCP(resultado);
}
