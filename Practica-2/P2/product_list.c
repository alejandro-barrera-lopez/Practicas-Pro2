/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "product_list.h"

void createEmptyList (tList* lista) {
	*lista = NULL; // La lista se asigna a nulo
}

bool isEmptyList (tList lista) {
	return lista == LNULL; // Si la lista es igual a nulo, está vacía
}

tPosL first (tList lista) {
	return lista; // Devuelve la primera posición de la lista
}

tPosL last (tList lista) {
	tPosL posicion = lista; // Define e inicializa una variable tPosL con la posición del primer elemento de la lista
	// Recorre la lista hasta el final
	while (posicion->siguiente != LNULL) {
		posicion = posicion->siguiente;
	}
	return posicion; // Devuelve la posición final de la lista
}

tPosL next (tPosL posicion, tList lista) {
	return posicion->siguiente;
}

tPosL previous (tPosL posicion, tList lista) { // Ben
	tPosL aux; // Declara una variable de tipo tPosL
	if(posicion == lista) { // Si es la primera posicion devuelve nulo
		return LNULL;
	}
	// Recorre la lista desde el principio hasta llegar al elemento anterior al dado
	for(aux = lista; aux->siguiente != posicion; aux = aux->siguiente);
	return aux; // Devuelve el elemento anterior al dado
}

bool createNode (tPosL* posicion) {
	*posicion = malloc(sizeof(struct tNode)); // Reserva memoria en el sistema para una posición de la lista
	return *posicion != LNULL; // Devuelve true si se asignó correctamente, o false si no
}

bool insertItem (tItemL producto, tList* lista) { // TODO Razonalo e facelo eu
	tPosL pos1, pos2; // Declara dos variables de tipo tPosL para almacenar posiciones en la lista

	if(!createNode(&pos1)) { // Si la memoria no se pudo asignar correctamente, devuelve falso
		return false;
	} else {
		pos1->dato = producto;
		pos1->siguiente = LNULL;
		if(isEmptyList(*lista)) { // Si la lista esta vacia
			*lista = pos1; // Se inserta el elemento en la primera posicion
		} else if (strcmp(producto.productId, (*lista)->dato.productId) < 0) {
			pos1->siguiente = *lista;
			*lista = pos1;
		} else {
			pos2 = *lista;
			while ((pos2->siguiente != LNULL) && (strcmp(pos2->siguiente->dato.productId, producto.productId) < 0)) {
				pos2 = next(pos2, *lista);
			}
			pos1->siguiente = pos2->siguiente;
			pos2->siguiente = pos1;
		}
	}
	return true;
}

void deleteAtPosition (tPosL posicion, tList* lista) { // TODO
	tPosL pos; // Declara una variable de tipo tPosL, para almacenar una posición en la lista
	if(posicion == *lista) { // Si la posición introducida está al principio de la lista
		*lista = (*lista)->siguiente; // Se cambia el inicio de la lista a la siguiente posición, eliminando así la primera
	} else if (posicion->siguiente == LNULL) { // Si es el último elemento de la lista
		for(pos = *lista; pos->siguiente != posicion; pos = pos->siguiente); // Recorre la lista hasta 'posicion'
		pos->siguiente = LNULL; // Y pasa a nulo la posición dada, eliminando así su contenido de la lista
	} else { // Si no se cumplió ninguna de las anteriores
		pos = posicion->siguiente;
		posicion->dato = pos->dato;
		posicion->siguiente = pos->siguiente;
		posicion = pos;
	} // Libera la memoria asignada para el elemento eliminado
	free(posicion);
}

tItemL getItem (tPosL posicion, tList lista) {
	return posicion->dato; // Devuelve el elemento situado en la posición dada
}

void updateItem (tItemL producto, tPosL posicion, tList* lista) {
	posicion->dato = producto; // Actualiza el elemento situado en la posición indicada, sustituyéndolo por el introducido
}

tPosL findItem (tProductId producto, tList lista) {
	tPosL pos = lista; // Define una variable de tipo tPosL y le asigna el valor de la lista
	while((pos != LNULL) && strcmp(producto, pos->dato.productId) !=0 ) { // Mientras no se encuentre el elemento a buscar
		pos = pos->siguiente; // Se pasa a la siguiente posición de la lista
	} // Finalmente, devuelve la posición del item dado, o nulo si no se ha encontrado
	return pos;
}

void deleteList (tList* lista) {
	tPosL posicion; // Define una variable de tipo tPosL para almacenar una posición

	while(*lista != LNULL) { // Mientras la lista no sea igual a nulo, es decir, mientras no esté vacía
		// Se recorre cada elemento de la lista y se va liberando la memoria asignada a él
		posicion = *lista;
		*lista = (*lista)->siguiente;
		free(posicion);
	}
}