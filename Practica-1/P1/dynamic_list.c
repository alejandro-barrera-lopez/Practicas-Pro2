/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 03 / 03 / 22
 */

#include "dynamic_list.h"

void createEmptyList (tList* lista) {
	*lista = NULL;
}

bool isEmptyList (tList lista) {
	return lista == LNULL;
}

tPosL first (tList lista) {
	return lista;
}

tPosL last (tList lista) {
	tPosL posicion = lista;

	while (posicion->siguiente != LNULL) {
		posicion = posicion->siguiente;
	}
	return posicion;
}

tPosL next (tPosL posicion, tList lista) {
	return posicion->siguiente;
}

tPosL previous (tPosL posicion, tList lista) { // Ben
	tPosL aux;

	if(posicion == lista) { // Si es la primera posicion devuelve nulo
		return LNULL;
	}
	// Recorre la lista desde el principio hasta llegar al elemento anterior al dado
	for(aux = lista; aux->siguiente != posicion; aux = aux->siguiente);

	return aux;
}

bool createNode (tPosL* posicion) {
	*posicion = malloc(sizeof(struct tNode));
	return *posicion != LNULL;
}

bool insertItem (tItemL producto, tPosL posicion, tList* lista) {
	tPosL pos1, pos2;

	if(!createNode(&pos1)) { // Si la memoria se pudo asignar correctamente
		return false;
	} else {
		pos1->dato = producto;
		pos1->siguiente = LNULL;

		if(*lista == LNULL) {// Si la lista esta vacia
			*lista = pos1; // El producto insertado ocupa la primera posicion
		} else if (posicion == LNULL) { // Si no se especifica posicion, se inserta al final
			for(pos2 = *lista; pos2->siguiente != LNULL; pos2 = pos2->siguiente);
			pos2->siguiente = pos1;
		} else if (pos1 == *lista) {
			pos1->siguiente = posicion;
			*lista = pos1;
		} else {
			pos1->dato = posicion->dato;
			posicion->dato = producto;
			pos1->siguiente = posicion->siguiente;
			posicion->siguiente = pos1;
		}
		return true;
	}
}



void deleteAtPosition (tPosL posicion, tList* lista) {
	tPosL pos;

	if(posicion == *lista) {
		*lista = (*lista)->siguiente;
	} else if (posicion->siguiente == LNULL) {
		for(pos = *lista; pos->siguiente != posicion; pos = pos->siguiente);
		pos->siguiente = LNULL;
	} else {
		pos = posicion->siguiente;
		posicion->dato = pos->dato;
		posicion->siguiente = pos->siguiente;
		posicion = pos;
	}
	free(posicion);
}

tItemL getItem (tPosL posicion, tList lista) {
	return posicion->dato;
}

void updateItem (tItemL producto, tPosL posicion, tList* lista) {
	posicion->dato = producto;
}

tPosL findItem (tProductId d, tList L)
{
	tPosL p = L;

	while((p!=LNULL)&&strcmp(d, p->dato.productId)!=0){
		p = p->siguiente;
	}
	return p;
}

// TODO Reescribir man, porque foi copiado do ano pasado
void deleteList (tList* lista) {
	tPosL posicion;

	while(*lista != LNULL) {
		posicion = *lista;
		*lista = (*lista)->siguiente;
		free(posicion);
	}
}