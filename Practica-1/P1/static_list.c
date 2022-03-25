/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 25 / 03 / 22
 */

#include "static_list.h"

void createEmptyList (tList* lista) {
    lista->lastPos = LNULL; // La última posición de la lista se asigna a nulo
}

bool isEmptyList(tList L){
    return L.lastPos == LNULL; // Si la última posición de la lista es nulo, la lista está vacía
}

tPosL first (tList lista) {
    return 0; // Devuelve la primera posición de la lista
}

tPosL last (tList lista) {
    return lista.lastPos; // Devuelve la última posición de la lista
}

tPosL next(tPosL posicion, tList lista) {
    if(posicion == last(lista)) { // Si la posición de la lista es la última, devuelve nulo, ya que no hay siguiente
        return LNULL;
    } else { // De lo contrario, devuelve la posición siguiente
        return ++posicion;
    }
}

tPosL previous(tPosL posicion, tList lista) {
    return --posicion; // Devuelve la posición anterior a la posición dada en la lista
}

bool insertItem (tItemL elemento, tPosL posicion, tList *lista) {
    tPosL i; // Define una variable de tipo tPosL para almacenar una posición
    if(lista->lastPos == LIST_SIZE_LIMIT - 1) { // Si la lista ya está llena no se puede insertar, y se devuelve false
        return false;
    } else { // Se procede a la inserción del elemento
        lista->lastPos++; // Se incrementa en 1 la cantidad de elementos en la lista
        if(posicion == LNULL) { // Si no se ha especificado posición
            lista->elemento[lista->lastPos] = elemento; // El elemento se inserta al final de la lista
        } else { // Si se ha especificado posición
            for(i = lista->lastPos; i >= posicion + 1; i--) { // Recorre la lista hasta la posición dada
                lista->elemento[i] = lista->elemento[i - 1]; // Moviendo de uno en uno los elementos de la lista
            } // Para introducir el elemento dado en la posición deseada
            lista->elemento[posicion] = elemento;
        } // La inserción fue exitosa, se devuelve verdadero
        return true;
    }
}

void deleteAtPosition(tPosL pos, tList* lista){
    tPosL i; // Declara una variable de tipo tPosL para almacenar una posición
	lista->lastPos--; // Reduce en un 1 el tamaño de la lista, ya que se va a eliminar un elemento
    for(i = pos; i <= lista->lastPos; i++){ // Se recorre la lista hasta la posición dada
		lista->elemento[i] = lista->elemento[i+1]; // Se reubican los elementos en la lista
    }
}

tItemL getItem (tPosL posicion, tList lista) {
    return lista.elemento[posicion]; // Devuelve el elemento que ocupe la posición dada en la lista
}

void updateItem (tItemL elemento, tPosL posicion, tList* lista) {
	// Cambia el valor guardado en la posición dada de la lista por el nuevo valor introducido
    lista->elemento[posicion] = elemento;
}

tPosL findItem (tProductId producto, tList lista) {
    for(int i = 0; i < lista.lastPos; i++) { // Recorre la lista de principio a fin, elemento a elemento
        if(!strcmp(lista.elemento[i].productId, producto)) // Si el elemento introducido coincide con el consultado
            return i; // Devuelve su posición, ya que es el elemento buscado
    } // Si no se ha encontrado, devuelve nulo
    return LNULL;
}

void deleteList (tList* lista) {
	lista->lastPos = LNULL; // Se asigna la variable que guarda la última posición a nulo (0), por lo que la lista estará vacía
}