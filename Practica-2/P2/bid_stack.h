/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"
#define BID_MAX_SIZE 25
#define SNULL 0

typedef int tPosS;

typedef struct { // Datos de un elemento de la pila de pujas de un producto
	tUserId bidder;
	tProductPrice productPrice;
} tItemS;

typedef struct { // Define el TAD que almacenar� las pujas de un producto
	tItemS vector[BID_MAX_SIZE]; // Vector en el que se guardan los elementos de la lista
	tPosS final; // Posicion de la cima / ultima posicion del vector
} tStack;

/**
 * Crea una pila vacia
 * @param tStack Pila que va a ser iniciada
 * @return La pila iniciada //TODO Preguntar se e correcto definir como return a pila aqui, ao ser void a funcion
 * @pre La pila no tiene elementos
 */
void createEmptyStack (tStack* pila);

/**
 * Inserta un elemento en la cima de una pila.
 * @param elemento Elemento a ser insertado en la pila
 * @param pila Pila en la que se inserta el elemento
 * @return La pila con el nuevo elemento insertado // TODO ???
 * @return True si el elemento fue apilado; false en caso contrario
 */
bool push (tItemS elemento, tStack* pila);

/**
 * Elimina de la pila el elemento situado en la cima
 * @param pila Pila de la que se va a eliminar el elemento
 * @return La pila sin el elemento situado en la cima // TODO ???
 * @pre La pila no esta vacia
 */
void pop (tStack* pila);

/**
 * Recupera el elemento de la cima de la pila sin eliminarlo
 * @param pila Pila a utilizar
 * @return El elemento situado en la cima
 * @pre La pila no esta vacia
 */
tItemS peek (tStack pila);

/**
 * Determina si una pila esta vacia o no
 * @param pila Pila a analizar
 * @return True si la pila esta vacia; false en caso contrario
 */
bool isEmptyStack (tStack pila);

/**
 * Elimina el contenido de una pila
 * @param stack Pila a vaciar
 * @return Pila vaciada TODO ???
 */
void deleteStack (tStack stack);

#endif
