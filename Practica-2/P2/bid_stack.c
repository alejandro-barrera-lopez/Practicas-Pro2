/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 08 / 04 / 22
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

void deleteStack (tStack stack) {
	while(!isEmptyStack(stack)) { // Mientras la pila no est� vac�a
		pop(&stack); // Elimina su elemento cima
	}
}