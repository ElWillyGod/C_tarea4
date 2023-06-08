#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_fecha {
    nat dia, mes, anio;
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;

    nuevaFecha = new rep_fecha;

    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;

    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
     delete fecha;
    fecha = NULL;
}

void imprimirTFecha(TFecha fecha) {
        printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);

}

bool AnioBisiesto(nat anio)
{

    return (anio % 400 == 0 || (anio % 4 == 0 && anio % 100 != 0));
}
nat diaMes(nat mes, nat anio)
{

    nat diasDelMes;

    if ((mes % 2 == 0 && (mes < 8 && mes != 2)) || (mes % 2 != 0 && mes >= 9))
    {

        diasDelMes = 30;
    }
    else if (mes != 2)
    {

        diasDelMes = 31;
    }
    else if (mes == 2 && AnioBisiesto(anio))
    {

        diasDelMes = 29;
    }
    else
    {

        diasDelMes = 28;
    }

    return diasDelMes;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    fecha->dia += dias;

    while (fecha->dia > diaMes(fecha->mes, fecha->anio))
    {

        fecha->dia -= diaMes(fecha->mes, fecha->anio);
        fecha->mes++;

        if (fecha->mes > 12)
        {
            fecha->mes = 1;
            fecha->anio++;
        }
    }

}

int compararTFechas(TFecha fecha1, TFecha fecha2) {
    int res = 1;

    if (fecha1->anio < fecha2->anio)
    {
        res = -1;
    }
    else if (fecha1->anio == fecha2->anio)
    {
        if (fecha1->mes < fecha2->mes)
        {
            res = -1;
        }
        else if (fecha1->mes == fecha2->mes)
        {
            if (fecha1->dia < fecha2->dia)
            {
                res = -1;
            }
            else if (fecha1->dia == fecha2->dia)
            {
                res = 0;
            }
        }
    }

    return res;
}

TFecha copiarTFecha(TFecha fecha) {
 TFecha CpFecha = crearTFecha(fecha->dia, fecha->mes, fecha->anio);

    return CpFecha;
    }

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
