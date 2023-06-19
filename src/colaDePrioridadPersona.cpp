#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona
{

  TPersona *cola;
  TPersona *ids;

  nat max;
  nat pos;
  bool inver;
};

TFecha obtenerFechaPrioridad(TPersona persona)
{
  return fechaTEvento(primerEventoDeTPersona(persona));
}

void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp)
{
  while (pos > 1)
  {
    nat padre = pos / 2;

    if (!cp->inver)
    {
      if ((compararTFechas(obtenerFechaPrioridad(cp->cola[padre]), obtenerFechaPrioridad(cp->cola[pos])) == 1))
      {
        TPersona aux = cp->cola[pos];
        cp->cola[pos] = cp->cola[padre];
        cp->cola[padre] = aux;

        pos = padre;
      }
      else
      {
        break;
      }
    }
    else
    {
      if ((compararTFechas(obtenerFechaPrioridad(cp->cola[padre]), obtenerFechaPrioridad(cp->cola[pos])) == -1))
      {
        TPersona aux = cp->cola[pos];
        cp->cola[pos] = cp->cola[padre];
        cp->cola[padre] = aux;

        pos = padre;
      }
      else
      {
        break;
      }
    }
  }
}

void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp)
{
  while (pos <= cp->pos / 2)
  {

    nat hijo = 2 * pos;
    if ((hijo + 1 <= cp->pos) && (compararTFechas(obtenerFechaPrioridad(cp->cola[hijo + 1]), obtenerFechaPrioridad(cp->cola[hijo])) == -1))
    {
      hijo++;
    }

    if (!cp->inver)
    {
      if (compararTFechas(obtenerFechaPrioridad(cp->cola[pos]), obtenerFechaPrioridad(cp->cola[hijo])) == 1)
      {
        TPersona aux = cp->cola[hijo];

        cp->cola[hijo] = cp->cola[pos];
        cp->cola[pos] = aux;
        pos = hijo;
      }
      else
      {
        break;
      }
    }
    else
    {
      if (compararTFechas(obtenerFechaPrioridad(cp->cola[pos]), obtenerFechaPrioridad(cp->cola[hijo])) == -1)
      {
        TPersona aux = cp->cola[hijo];

        cp->cola[hijo] = cp->cola[pos];
        cp->cola[pos] = aux;
        pos = hijo;
      }
      else
      {
        break;
      }
    }
  }
}

TColaDePrioridadPersona crearCP(nat N)
{

  TColaDePrioridadPersona nueva = new rep_colaDePrioridadPersona();
  nueva->cola = new TPersona[N + 1];
  nueva->ids = new TPersona[N + 1];
  nueva->max = N;
  nueva->inver = false;
  nueva->pos = 0;

  for (nat i = 0; i <= N; i++)
  {
    nueva->cola[i] = NULL;
    nueva->ids[i] = NULL;
  }
  return nueva;
}

void invertirPrioridad(TColaDePrioridadPersona &cp)
{

  for (nat i = 1; i <= cp->pos / 2; i++)
  {
    TPersona mini = cp->cola[i];

    cp->cola[i] = cp->cola[cp->pos - i - 1];
    cp->cola[cp->pos - i - 1] = mini;
    cp->inver = !cp->inver;

    filtrado_descendente(cp->pos - i, cp);
  }
}

/**/

void liberarCP(TColaDePrioridadPersona &cp)
{
  for (nat i = 1; i <= cp->max; i++)
  {
    if (cp->ids[i] != NULL)
    {
      liberarTPersona(cp->ids[i]);
    }
  }

  delete[] cp->cola;
  delete[] cp->ids;
  delete cp;
  cp = NULL;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp)
{

  if (cp->pos <= cp->max)
  {
    cp->pos++;
    cp->cola[cp->pos] = persona;
    cp->ids[idTPersona(persona)] = persona;

    filtrado_ascendente(cp->pos, cp);
  }
}

bool estaVaciaCP(TColaDePrioridadPersona cp)
{ // implementar cantidad ??
  return cp->pos < 1;
}

TPersona prioritaria(TColaDePrioridadPersona cp)
{
  return cp->cola[1];
}

void eliminarPrioritaria(TColaDePrioridadPersona &cp)
{
  if (!estaVaciaCP(cp))
  {

    TPersona per = prioritaria(cp);
    cp->ids[idTPersona(per)] = NULL;

    if (cp->pos > 1)
    {

      cp->cola[1] = cp->cola[cp->pos]; // cambio por el ultimo

      liberarTPersona(per);

      filtrado_descendente(1, cp);
    }
    else
    {
      liberarTPersona(per);
    }
    cp->pos--;
  }
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp)
{
  return cp->ids[id] != NULL;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp)
{
  return obtenerFechaPrioridad(cp->ids[id]);
}

/*

     TPersona padre = cp->cola[pos];
   cp->cola[pos] = cp->cola[pos/2];
   cp->cola[pos/2] = padre;
   pos = pos/2;
   */

/*void filtrado_descendente(nat n, nat pos, TColaDePrioridadPersona &cp)
{

  while (pos < n)
  {
    if (2 * pos <= n)
    {

      nat hijo = 2 * pos;

      if ((hijo + 1 <= n) && (compararTFechas(obtenerFechaPrioridad(cp->cola[hijo + 1]), obtenerFechaPrioridad(cp->cola[hijo])) == -1))
      {

        hijo++;
      }

      if (compararTFechas(obtenerFechaPrioridad(cp->cola[pos]), obtenerFechaPrioridad(cp->cola[hijo])) == 1)
      {
        TPersona aux = cp->cola[hijo];

        cp->cola[hijo] = cp->cola[pos];
        cp->cola[pos] = aux;
        pos = hijo;
      }
      else
      {
        break;
      }
    }
  }
}

while (2 * pos <= cp->pos)
  {

    nat hijo = 2 * pos;

    if ((hijo + 1 <= cp->pos) && (compararTFechas(obtenerFechaPrioridad(cp->cola[hijo + 1]), obtenerFechaPrioridad(cp->cola[hijo])) == -1))
    {
      hijo++;
    }

    if (compararTFechas(obtenerFechaPrioridad(cp->cola[hijo]), obtenerFechaPrioridad(cp->cola[pos])) == -1)
    {
      TPersona aux = cp->cola[pos];

      cp->cola[pos] = cp->cola[hijo];
      cp->cola[hijo] = aux;
      pos = hijo;
    }
    else
    {
      break;
    }
  }

nat hijoIzq = 2 * pos + 1;
  nat hijoDer = 2 * pos + 2;
  nat posMayor = pos;

  // Comparar la fecha de prioridad de la persona en la posición actual con las de los hijos
  if (hijoIzq < cp->pos)
  {

    TFecha fechaActual = obtenerFechaPrioridad(cp->cola[pos]);
    TFecha fechaIzq = obtenerFechaPrioridad(cp->cola[hijoIzq]);

    bool cumplePrioridad = cp->inver ? (fechaIzq > fechaActual) : (fechaIzq < fechaActual);
    if (cumplePrioridad)
    {
      posMayor = hijoIzq;
    }
  }

  if (hijoDer < cp->pos)
  {
    TFecha fechaActual = obtenerFechaPrioridad(cp->cola[pos]);
    TFecha fechaDer = obtenerFechaPrioridad(cp->cola[hijoDer]);
    bool cumplePrioridad = cp->inver ? (fechaDer > fechaActual) : (fechaDer < fechaActual);
    if (cumplePrioridad)
    {
      posMayor = hijoDer;
    }
  }

  if (posMayor != pos)
  {
    // Intercambiar elementos
    TPersona temp = cp->cola[pos];
    cp->cola[pos] = cp->cola[posMayor];
    cp->cola[posMayor] = temp;

    // Continuar el filtrado descendente en la posición del hijo que se intercambió
    filtrado_descendente(posMayor, cp);
  }
*/
