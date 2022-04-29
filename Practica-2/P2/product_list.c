/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 29 / 04 / 22
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
	tPosL pos = lista; // Define e inicializa una variable tPosL con la posición del primer elemento de la lista
	// Recorre la lista hasta el final
	while (pos->siguiente != LNULL) {
        pos = pos->siguiente;
	}
	return pos; // Devuelve la posición final de la lista
}

tPosL next (tPosL pos, tList lista) {
	return pos->siguiente;
}

tPosL previous (tPosL pos, tList lista) { // Ben
	tPosL aux; // Declara una variable de tipo tPosL
	if(pos == lista) { // Si es la primera posición devuelve nulo
		return LNULL;
	}
	// Recorre la lista desde el principio hasta llegar al elemento anterior al dado
	for(aux = lista; aux->siguiente != pos; aux = aux->siguiente);
	return aux; // Devuelve el elemento anterior al dado
}

bool createNode (tPosL* pos) {
	*pos = malloc(sizeof(struct tNode)); // Reserva memoria en el sistema para una posición de la lista
	return *pos != LNULL; // Devuelve true si se asignó correctamente, o false si no
}

bool insertItem (tItemL producto, tList* lista) {
	tPosL pos1, pos2; // Declara dos variables de tipo tPosL para almacenar posiciones en la lista

	if(!createNode(&pos1)) { // Si la memoria no se pudo asignar correctamente, devuelve falso
		return false;
	} else {
        // Se copian los datos de la nueva posición de la lista en 'pos1'
		pos1->dato = producto;
		pos1->siguiente = LNULL;
		if(isEmptyList(*lista)) { // Si la lista esta vacía
			*lista = pos1; // Se inserta el elemento en la primera posición
		} else if (strcmp(producto.productId, (*lista)->dato.productId) < 0) {
            // Si el productId del producto a insertar es alfabéticamente menor al primer productId de la lista,
            // se inserta el elemento en la primera posición de la lista
			pos1->siguiente = *lista;
			*lista = pos1;
            /* Si no, se recorre la lista hasta alcanzar la posición alfabética adecuada para el nuevo producto,
             * y se inserta en dicha posición */
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

void deleteAtPosition (tPosL posicion, tList* lista) {
	tPosL pos; // Declara una variable de tipo tPosL, para almacenar una posición en la lista
	if(posicion == *lista) { // Si la posición introducida está al principio de la lista
		*lista = (*lista)->siguiente; // Cambia el inicio de la lista a la siguiente posición, eliminando así la primera
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

tItemL getItem (tPosL pos, tList lista) {
	return pos->dato; // Devuelve el elemento situado en la posición dada
}

void updateItem (tItemL producto, tPosL pos, tList* lista) {
    pos->dato = producto; // Actualiza el elemento situado en la posición indicada, sustituyéndolo por el introducido
}

tPosL findItem (tProductId producto, tList lista) {
	tPosL pos = lista; // Define una variable de tipo tPosL y le asigna el valor de la lista
	while((pos != LNULL) && strcmp(producto, pos->dato.productId) !=0 ) { // Mientras no encuentre el elemento a buscar
		pos = pos->siguiente; // Se pasa a la siguiente posición de la lista
	} // Finalmente, devuelve la posición del item dado, o nulo si no se ha encontrado
	return pos;
}