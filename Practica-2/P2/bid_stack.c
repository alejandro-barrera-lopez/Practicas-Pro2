/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "bid_stack.h"

void createEmptyStack (tStack* pila) {
	pila->final = SNULL; // Inicializa la posicion del final de la lista como nulo (0 en esta implementacion)
}

bool push (tItemS elemento, tStack* pila) {
	if (pila->final == BID_MAX_SIZE) { // Si el tamaño maximo de la pila ya ha sido alcanzado
		return false; // El elemento no se inserta y se devuelve falso
	} else { // Sino, se inserta el elemento en la ultima posicion del vector (cima) y se incrementa esta
		pila->vector[pila->final++] = elemento;
		return true; // Finalmente, se devuelve true para indicar que se ha insertado
	}
}

void pop (tStack* pila) {
	pila->final--; // Se decrementa la posicion de la cima, eliminando el elemento situado en ella
}

tItemS peek (tStack pila) {
	return pila.vector[pila.final - 1]; // Devuelve el elemento situado en la cima de la pila
}

bool isEmptyStack (tStack pila) {
	return pila.final == SNULL; // La lista esta vacia si, y solo si, la ultima posicion es nula (0)
}