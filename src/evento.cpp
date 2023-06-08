#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_evento {

    TFecha fecha;
    int id;
    char descripcion[MAX_DESCRIPCION];
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;

    nuevoEvento = new rep_evento;

    nuevoEvento->fecha = fecha;
    nuevoEvento->id = id;
    strcpy(nuevoEvento->descripcion, descripcion);

    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
     printf("Evento %d: %s\n", evento->id, evento->descripcion);
    printf("Fecha: ");
    imprimirTFecha(evento->fecha);
}

void liberarTEvento(TEvento &evento) {
      liberarTFecha(evento->fecha);
    delete evento;
    evento = NULL;
}

int idTEvento(TEvento evento) {
    int res = 0;

    res = evento->id;

    return res;
}

TFecha fechaTEvento(TEvento evento) {
    TFecha fecha = NULL;

    fecha = evento->fecha;

    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    aumentarTFecha(evento->fecha, dias);
}

TEvento copiarTEvento(TEvento evento) {
   TEvento CpEvento = crearTEvento(evento->id, evento->descripcion, copiarTFecha(evento->fecha));

    return CpEvento;
    }

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
