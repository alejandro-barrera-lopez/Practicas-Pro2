/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: ** / ** / **
 */

#include "static_list.h"

void createEmptyList (tList* lista) {
    lista->lastPos = LNULL;
}

bool isEmptyList(tList L){
    return L.lastPos == LNULL;
}

tPosL first (tList lista) {
    return 0;
}

tPosL last (tList lista) {
    return lista.lastPos;
}

tPosL next(tPosL posicion, tList lista) {
    if(posicion == last(lista)) {
        return LNULL;
    } else { // TODO Pódome saltar este else?
        return ++posicion;
    }
}

tPosL previous(tPosL posicion, tList lista) {
    return --posicion;
}

bool insertItem (tItemL elemento, tPosL posicion, tList *lista) {
    tPosL i;
    if(lista->lastPos == LIST_SIZE_LIMIT - 1) {
        return false;
    } else { // TODO Pódome saltar este else?
        if(posicion == LNULL) {
            lista->elemento[lista->lastPos++] = elemento;
        } else {
            for(i = lista->lastPos; i >= posicion + 1; i--) {
                lista->elemento[i] = lista->elemento[i + 1];
            }
            lista->elemento[posicion] = elemento;
        }
        lista->lastPos++;
        return true;
    }
}

void deleteAtPosition(tPosL p, tList* L){
    tPosL i;
    L->lastPos--;
    for(i=p; i <= L->lastPos; i++){
        L->elemento[i] = L->elemento[i+1];
    }

}

tItemL getItem (tPosL posicion, tList lista) {
    return lista.elemento[posicion];
}

void updateItem (tItemL elemento, tPosL posicion, tList* lista) {
    lista->elemento[posicion] = elemento;
}

tPosL findItem (tProductId producto, tList lista) {
    for(int i = 0; i < lista.lastPos; i++) {
        if(!strcmp(lista.elemento[i].productId, producto))
            return i;
    }
    return LNULL;
}