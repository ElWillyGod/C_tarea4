#include "../include/personasLDE.h"
#include "string.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////
typedef struct rep_nodo *nodo;

struct rep_nodo
{
    TPersona persona;

    rep_nodo *sig;
    rep_nodo *ant;
};

struct rep_personasLDE
{
    rep_nodo *ini;
    rep_nodo *fin;

    nat tamanio;
};

TPersonasLDE crearTPersonasLDE()
{
    TPersonasLDE listaPersona = new rep_personasLDE;

    listaPersona->ini = NULL;
    listaPersona->fin = NULL;
    listaPersona->tamanio = 0;

    return listaPersona;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos)
{
    /*seguramente se pueda mejorar*/
    nat i;

    nodo nuevoNodo = new rep_nodo;
    nodo actual;

    nuevoNodo->persona = persona;
    nuevoNodo->ant = NULL;
    nuevoNodo->sig = NULL;

    actual = personas->ini;

    if (actual == NULL)
    { // vacia
        personas->ini = nuevoNodo;
        personas->fin = nuevoNodo;
    }
    else if (pos == 1)
    { // inicio
        nuevoNodo->sig = personas->ini;
        personas->ini->ant = nuevoNodo;
        personas->ini = nuevoNodo;
    }
    else
    {

        if (pos > personas->tamanio)
        { /*al final*/
            nuevoNodo->ant = personas->fin;
            personas->fin->sig = nuevoNodo;
            personas->fin = nuevoNodo;
        }
        else
        { /*en el medio*/
            i = 1;

            while (i < pos)
            {
                actual = actual->sig;
                i++;
            }
            nuevoNodo->sig = actual;
            nuevoNodo->ant = actual->ant;

            actual->ant->sig = nuevoNodo;
            actual->ant = nuevoNodo;
        }
    }
    personas->tamanio++;
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE)
{
    nodo elementoAEliminar;

    while (personasLDE->ini != NULL)
    {
        elementoAEliminar = personasLDE->ini;

        personasLDE->ini = personasLDE->ini->sig;

        liberarTPersona(elementoAEliminar->persona);
        delete elementoAEliminar;
    }

    delete personasLDE;
    personasLDE = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas)
{
    nodo actual = personas->ini;

    while (actual != NULL)
    {
        imprimirTPersona(actual->persona);
        actual = actual->sig;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas)
{
    return personas->tamanio;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas)
{
    if (personas->tamanio > 0)
    {
        nodo elementoAEliminar = personas->ini;

        personas->ini = personas->ini->sig;

        if (personas->ini == NULL)
        {
            personas->fin = NULL;
        }
        else
        {
            personas->ini->ant = NULL;
        }

        liberarTPersona(elementoAEliminar->persona);
        delete elementoAEliminar;

        personas->tamanio--;
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas)
{
    if (personas->tamanio > 0)
    {
        nodo elementoAEliminar = personas->fin;

        personas->fin = personas->fin->ant;

        if (personas->fin == NULL)
        {
            personas->ini = NULL;
        }
        else
        {

            personas->fin->sig = NULL;
        }

        liberarTPersona(elementoAEliminar->persona);
        delete elementoAEliminar;

        personas->tamanio--;
    }
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id)
{
    nodo actual = personas->ini;

    while ((actual != NULL) && (idTPersona(actual->persona) != id))
    {
        actual = actual->sig;
    }
    return actual != NULL;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id)
{
    nodo actual = personas->ini;

    while (idTPersona(actual->persona) != id)
    {
        actual = actual->sig;
    }

    return actual->persona;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2)
{
    TPersonasLDE resultado = crearTPersonasLDE();

    resultado->ini = personas1->ini;
    resultado->fin = personas2->fin;

    if (personas1->ini == NULL)
    { // si es vacio el inicio cambia

        resultado->ini = personas2->ini;
    }
    else if (personas2->ini != NULL)
    { // si el segundo no es nulll se hace el ajustes de punteros al medio

        personas1->fin->sig = personas2->ini;
        personas2->ini->ant = personas1->fin;
    }
    else
    { // si es null cambia el fin, que originalmente era de p2 a el de p1
        resultado->fin = personas1->fin;
    }

    resultado->tamanio = personas1->tamanio + personas2->tamanio;

    delete personas1;
    delete personas2;

    return resultado;
}

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona)
{
    insertarTPersonasLDE(personas, persona, 1);
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona)
{
    insertarTPersonasLDE(personas, persona, personas->tamanio + 1);
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas)
{
    return personas->ini->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas)
{
    return personas->fin->persona;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100])
{
   if(personas->ini != NULL){

    if (strcmp(nombreTPersona(personas->ini->persona), nombre) == 0)
    {
        eliminarInicioTPersonasLDE(personas);
    }
    else if (strcmp(nombreTPersona(personas->fin->persona), nombre) == 0)
    {
        eliminarFinalTPersonasLDE(personas);
    }
    else
    {
        nodo actual = personas->ini;

        while ((actual != NULL) && (strcmp(nombreTPersona(actual->persona), nombre) != 0))
        {
            actual = actual->sig;
        }
        if (actual != NULL)
        {
            actual->sig->ant = actual->ant;
            actual->ant->sig = actual->sig;


            liberarTPersona(actual->persona);
            delete actual;
            personas->tamanio--;
        }
    }
    }
}

bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100])
{
    nodo indice = personas->ini;

    while((indice != NULL) && strcmp(nombreTPersona(indice->persona), nombre) != 0) {
        indice = indice->sig;
    }
    return indice != NULL;   
}

TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100])
{
    nodo  indice = personas->ini;

    while (strcmp(nombreTPersona(indice->persona), nombre) != 0) {
        indice = indice->sig;
    }
  
    return indice->persona;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
