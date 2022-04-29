/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 29 / 04 / 22
 */

#include "bid_stack.h"

void createEmptyStack (tStack* pila) {
	pila->final = SNULL; // Inicializa la posición del final de la lista como nulo (0 en esta implementación)
}

bool push (tItemS elemento, tStack* pila) {
	if (pila->final == BID_MAX_SIZE) { // Si el tamaño máximo de la pila ya ha sido alcanzado
		return false; // El elemento no se inserta y se devuelve falso
	} else { // Si no, se inserta el elemento en la última posición del vector (cima) y se incrementa esta
		pila->vector[pila->final++] = elemento;
		return true; // Finalmente, se devuelve true para indicar que se ha insertado
	}
}

void pop (tStack* pila) {
	pila->final--; // Se decrementa la posición de la cima, eliminando el elemento situado en ella
}

tItemS peek (tStack pila) {
	return pila.vector[pila.final - 1]; // Devuelve el elemento situado en la cima de la pila
}

bool isEmptyStack (tStack pila) {
	return pila.final == SNULL; // La lista esta vacía si, y solo si, la ultima posición es nula (0)
}