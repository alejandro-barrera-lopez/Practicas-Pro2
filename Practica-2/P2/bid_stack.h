/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 29 / 04 / 22
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

typedef struct { // Define el TAD que almacenará las pujas de un producto
	tItemS vector[BID_MAX_SIZE]; // Vector en el que se guardan los elementos de la lista
	tPosS final; // Posición de la cima (última posición del vector)
} tStack;

/**
 * Crea una pila vacía
 * @param tStack Pila que va a ser iniciada
 * @return La pila iniciada
 * @pre La pila no tiene elementos
 */
void createEmptyStack (tStack* pila);

/**
 * Inserta un elemento en la cima de una pila.
 * @param elemento Elemento a ser insertado en la pila
 * @param pila Pila en la que se inserta el elemento
 * @return La pila con el nuevo elemento insertado
 * @return True si el elemento fue apilado; false en caso contrario
 */
bool push (tItemS elemento, tStack* pila);

/**
 * Elimina de la pila el elemento situado en la cima
 * @param pila Pila de la que se va a eliminar el elemento
 * @return La pila sin el elemento situado en la cima
 * @pre La pila no esta vacía
 */
void pop (tStack* pila);

/**
 * Recupera el elemento de la cima de la pila sin eliminarlo
 * @param pila Pila a utilizar
 * @return El elemento situado en la cima
 * @pre La pila no esta vacía
 */
tItemS peek (tStack pila);

/**
 * Determina si una pila esta vacía o no
 * @param pila Pila a analizar
 * @return True si la pila esta vacía; false en caso contrario
 */
bool isEmptyStack (tStack pila);

#endif