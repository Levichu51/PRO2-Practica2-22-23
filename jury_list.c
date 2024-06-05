
#include "jury_list.h"
#include "participant_list.h"


void createEmptyListJ(tListJ* L){
    L->lastPos = NULLJ;

    //Objetivo: Crea una Lista vacía de n elementos.
    //Salida: La Lista L vacía.
    //Precondición: -
    //Postcondición: La Lista no contiene datos
}


bool insertItemJ(tItemJ d, tListJ* L){
    tPosJ i;

    if(L->lastPos == MAX-1)
        return false;

    else{
        if (isEmptyListJ(*L) || (strcmp(d.juryName, L->dataJ[L->lastPos].juryName)) > 0) {
            L->lastPos++;
            L->dataJ[L->lastPos] = d;

        }else{
            L->lastPos++;
            for(i = L->lastPos; i > 0 && (strcmp(d.juryName, L->dataJ[i-1].juryName)) < 0; i--)
                L->dataJ[i] = L->dataJ[i-1];
            L->dataJ[i] = d;

        }
        return true;
    }
    //Objetivo: Iserta el elemento deseado en la Lista ordenado alfabéticamente. Si la p es NULLJ se añade al final de la Lista.
    //Salida: Devuelve el elemento insertado.
    //Precondición: p tiene que ser una posición válida o NULLJ.
    //Postcondición: Las posiciones anteriores de la Lista pueden haber variado.
}

tPosJ firstJ(tListJ L){
    return 0;

    //Objetivo: Devuelve el primero elemento de la Lista.
    //Salida: El primero elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosJ nextJ(tPosJ p, tListJ L){
    if (p == L.lastPos)
        return NULLJ;
    else {
        return ++p;
    }
    //Objetivo: Devuelve el elemento que está después de la posición introducida.
    //Salida: El elemento siguiente de la posición asginada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosJ lastJ(tListJ L){
    return L.lastPos;

    //Objetivo: Devuelve el último elemento de Lista.
    //Salida: El último elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosJ previousJ(tPosJ p, tListJ L){
    if (p == 0)
        return NULLJ;

    else
        return --p;
    //Objetivo: Devuelve el elemento anterior de la posición introducida.
    //Salida: El elemento anterior de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

bool isEmptyListJ(tListJ L ){
    return L.lastPos == NULLJ;

    //Objetivo: Comprueba si la Lista está vacía.
    //Salida: True o False dependiendo de si está vacía o no.
    //Precondición: -
    //Postcondición: -
}

tItemJ getItemJ(tPosJ p, tListJ L){
    return L.dataJ[p];

    //Objetivo: Obtener el elemento de la posición deseada de la Lista.
    //Salida: El elemento deseado de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosJ findItemJ(tJuryName d, tListJ L){
    tPosJ p;
    if(L.lastPos == NULLJ)
        return NULLJ;

    else if((strcmp(d, L.dataJ[0].juryName)) < 0 || (strcmp(d, L.dataJ[L.lastPos].juryName)) > 0)
        return NULLJ;

    else{
        for(p = 0; (p < L.lastPos) && (strcmp(d, L.dataJ[p].juryName)) > 0; p++);
        if(strcmp(L.dataJ[p].juryName, d) == 0)
            return p;
        else
            return NULLJ;

    }

    //Objetivo: Recorre la lista hasta encontrar el elemento intriducido.
    //Salida: La posición del elemento de la Lista que se ha asignado para buscar en ella.
    //Precondición: -
    //Postcondición: -
}

void updateItemJ(tItemJ d, tPosJ p, tListJ* L){
    L->dataJ[p] = d;

    //Objetivo: Actualiza el valor del elemento de la posición indicada.
    //Salida: El propio elemento introducido, pero actualizado.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

void deleteAtPositionJ(tPosJ p, tListJ* L){
    tPosJ q;

    for (q = p; (q < L->lastPos); q++)
        L->dataJ[q] = L->dataJ[q+1];
    L->lastPos--;


    //Objetivo: Borra el elemento de la posición indicada de la Lista.
    //Salida: -
    //Precondición: p tiene que ser una posición válida y  y el jurado en dicha posición tiene una lista de participantes vacía.
    //Postcondición: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
}


