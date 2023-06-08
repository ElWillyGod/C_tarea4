#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_agendaLS {
      TEvento evento;
    TAgendaLS sig;
    
};

TAgendaLS crearAgendaLS() {
  TAgendaLS Agenda = NULL;

    return Agenda;
    }

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    TAgendaLS nodo = new rep_agendaLS;

    nodo->evento = evento;
    nodo->sig = NULL;

    if ((agenda == NULL) || (compararTFechas(fechaTEvento(evento), fechaTEvento(agenda->evento)) == -1))
    {

        nodo->sig = agenda;
        agenda = nodo;
    }
    else
    {

        TAgendaLS aux = agenda;

        while ((aux->sig != NULL) && (compararTFechas(fechaTEvento(aux->sig->evento), fechaTEvento(evento)) == -1))
        {
            aux = aux->sig;
        }

        if (aux->sig != NULL)
        {
            nodo->sig = aux->sig;
        }
        aux->sig = nodo;
    }
    
}


void imprimirAgendaLS(TAgendaLS agenda) {
     while (agenda != NULL)
    {

        imprimirTEvento(agenda->evento);
        agenda = agenda->sig;
    }
    
}

void liberarAgendaLS(TAgendaLS &agenda) {
     TAgendaLS auxilar;

    while (agenda != NULL)
    {
        auxilar = agenda;

        liberarTEvento(agenda->evento);

        agenda = agenda->sig;
        delete auxilar;
    }

    agenda = NULL;
    
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return (agenda == NULL);
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
  TAgendaLS res, nuevo;

    if (agenda == NULL)
    {
        res = NULL;
    }
    else
    {
        TAgendaLS ultimo = NULL;

        while (agenda != NULL)
        {
            nuevo = new rep_agendaLS;
            nuevo->evento = copiarTEvento(agenda->evento);
            nuevo->sig = NULL;

            if (ultimo == NULL)
            {

                res = ultimo = nuevo;
            }
            else
            {

                ultimo->sig = nuevo;
                ultimo = nuevo;
            }

            agenda = agenda->sig;
        }
    }

    return res;
    
    }


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
 while ((agenda != NULL) && (idTEvento(agenda->evento) != id))
    {

        agenda = agenda->sig;
    }

    return (agenda != NULL);
}


TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
  TEvento evento;

    if (estaEnAgendaLS(agenda, id))
    {

        while (agenda != NULL)
        {
            if (idTEvento(agenda->evento) == id)
            {

                evento = agenda->evento;
                break;
            }
            agenda = agenda->sig;
        }
    }
    return evento;
    
    }

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
 if (estaEnAgendaLS(agenda, id))
    {

        TEvento eventoPosponer;

        TAgendaLS aux = agenda;
        TAgendaLS anterior = NULL;

        while (idTEvento(aux->evento) != id)
        {
            anterior = aux;
            aux = aux->sig;
        }

        eventoPosponer = aux->evento;

        if (anterior == NULL)
        {

            agenda = agenda->sig;
        }
        else
        {
            anterior->sig = aux->sig;
        }

        delete aux;

        posponerTEvento(eventoPosponer, n);
        agregarEnAgendaLS(agenda, eventoPosponer);
    }
    }

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
 while (agenda != NULL)
    {

        if (compararTFechas(fecha, fechaTEvento(agenda->evento)) == 0)
        {

            imprimirTEvento(agenda->evento);
        }

        agenda = agenda->sig;
    }
    }

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
 while ((agenda != NULL) && (compararTFechas(fechaTEvento(agenda->evento), fecha) != 0))
    {

        agenda = agenda->sig;
    }

    return (agenda != NULL);
    
    }

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    if (estaEnAgendaLS(agenda, id))
    {

        TAgendaLS aux = agenda;
        TAgendaLS anterior = NULL;

        while (idTEvento(aux->evento) != id)
        {
            anterior = aux;
            aux = aux->sig;
        }

        if (anterior == NULL)
        {

            agenda = agenda->sig;
        }
        else
        {

            anterior->sig = aux->sig;
        }

        liberarTEvento(aux->evento);
        delete aux;
    }}

///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return agenda->evento;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////