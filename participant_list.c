
#include "participant_list.h"


void createEmptyListP(tListP* L){
    *L = NULLP;

    //Objetivo: Crea una Lista vacía de n elementos.
    //Salida: La Lista L vacía.
    //Precondición: -
    //Postcondición: La Lista no contiene datos
}

bool createNode(tPosP* p){
    *p = malloc(sizeof (struct tNode));
    return *p != NULLP;

    //Objetivo: Crea los nodos para enlazar los elementos de la Lista
    //Salida: El puntero (nodo) para poder crear la Lista.
    //Precondición: Debe de haber una Lista inicializada.
    //Postcondición: El nodo no contiene elementos.
}

tPosP findPositionP(tListP L, tItemP d){
    tPosP p;

    p = L;
    while((p->next != NULLP) && ((strcmp(p->next->data.participantName, d.participantName)) < 0)) //recorre la lista hasta la ultima posicion y que d no sea el primer elemento
        p = p->next;
    return p;

    //Objetivo: Encontrar la posición del item introducido en la Lista.
    //Salida: La posición de este item.
    //Precondición: Debe de haber una Lista inicializada.
    //Postcondición: -

}

bool insertItemP(tItemP d, tListP* L){
    tPosP q, p;

    if (!createNode(&q))
        return false;

    else{
        q->data = d;
        q->next = NULLP;

        if (*L == NULLP)
            *L = q;

        else if ((strcmp((*L)->data.participantName, d.participantName)) > 0){
            q->next = *L;
            *L = q;
        }
        else{
            p = findPositionP(*L, d);
            q->next = p->next;
            p->next = q;
        }

        return true;
    }
    //Objetivo: Iserta el elemento deseado en la Lista ordenado alfabéticamente. Si la p es NULLP se añade al final de la Lista.
    //Salida: Devuelve el elemento insertado.
    //Precondición: p tiene que ser una posición válida o NULLP.
    //Postcondición: Las posiciones anteriores de la Lista pueden haber variado.
}

tPosP firstP(tListP L){
    return L;

    //Objetivo: Devuelve el primero elemento de la Lista.
    //Salida: El primero elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosP nextP(tPosP p, tListP L){
    return p->next;

    //Objetivo: Devuelve el elemento que está después de la posición introducida.
    //Salida: El elemento siguiente de la posición asginada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosP lastP(tListP L){
    tPosP p;

    for (p = L; p->next != NULLP; p = p->next);
    return p;

    //Objetivo: Devuelve el último elemento de Lista.
    //Salida: El último elemento de la Lista.
    //Precondición: La Lista no puede estar vacía.
    //Postcondición: -
}

tPosP previousP(tPosP p, tListP L){

    tPosP q;

    if (p == L)
        return NULLP;
    else {
        for (q = L; q->next != p; q = q->next);
        return q;
    }
    //Objetivo: Devuelve el elemento anterior de la posición introducida.
    //Salida: El elemento anterior de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

bool isEmptyListP(tListP L){
    return L == NULLP;

    //Objetivo: Comprueba si la Lista está vacía.
    //Salida: True o False dependiendo de si está vacía o no.
    //Precondición: -
    //Postcondición: -
}

tItemP getItemP(tPosP p, tListP L){
    return p->data;

    //Objetivo: Obtener el elemento de la posición deseada de la Lista.
    //Salida: El elemento deseado de la posición asignada.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

tPosP findItemP(tParticipantName d, tListP L){
    tPosP p;

    for (p = L; (p != NULLP) && strcmp(p->data.participantName, d) != 0; p = p->next);
    if(p != NULLP && strcmp(p->data.participantName, d) == 0)
        return p;
    else
        return NULLP;

    //Objetivo: Recorre la lista hasta encontrar el elemento introducido.
    //Salida: La posición del elemento de la Lista que se ha asignado para buscar en ella.
    //Precondición: -
    //Postcondición: -
}

void updateItemP(tItemP d, tPosP p, tListP* L){
    p->data = d;

    //Objetivo: Actualiza el valor del elemento de la posición indicada.
    //Salida: El propio elemento introducido, pero actualizado.
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: -
}

void deleteAtPositionP(tPosP p, tListP* L){
    tPosP q;

    if (p == *L)
        *L = (*L)->next;

    else if (p->next == NULLP) {
        for (q = *L; q->next != p; q = q->next);
        q->next = NULLP;
    }

    else{
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }

    free(p);

    //Objetivo: Borra el elemento de la posición indicada de la Lista.
    //Salida: -
    //Precondición: p tiene que ser una posición válida.
    //Postcondición: Las posiciones de los elementos de la Lista pueden haber variado.
}
