/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 29 / 04 / 22
 */

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "types.h"
#include "bid_stack.h"
#include <stdlib.h>		// Por malloc() y free()
#include <stdbool.h>	// Para utilizar el tipo 'bool'
#include <string.h>		// Por strcmp()

#define LNULL NULL

typedef struct { // Datos de un elemento de la lista de productos
	tUserId seller;
	tProductId productId;
	tProductCategory productCategory;
	tProductPrice productPrice;
	tBidCounter bidCounter;
	tStack bidStack;
} tItemL;

typedef struct tNode* tPosL;

struct tNode {
	tItemL dato;
	tPosL siguiente;
};

typedef tPosL tList;

/**
 * Crea una lista vacía y la inicializa
 * @return Una lista vacía
 * @param lista Lista a comprobar
 * @post La salida sin datos
 */
void createEmptyList (tList*);

/**
 * Determina si la lista esta vacía
 * @param lista Lista a comprobar
 * @return True si la lista esta vacía, false en caso contrario
 */
bool isEmptyList (tList);

/**
 * Devuelve la posición del primer elemento de la lista
 * @param  lista que contiene el elemento
 * @return Posición del primer elemento
 * @pre La lista no esta vacía
 */
tPosL first (tList);

/**
 * Devuelve la posición del ultimo elemento de la lista
 * @param lista Lista que contiene el elemento
 * @return Posición del primer elemento
 * @pre La lista no esta vacía
 */
tPosL last (tList);

/**
 * Devuelve la posición en la lista del elemento siguiente al actual
 * @param posicion Posición actual
 * @param lista Lista que contiene el elemento
 * @return Posición del elemento siguiente, o nulo si es el ultimo
 * @pre La lista no esta vacía
 * @pre La posición actual es una posición valida de la lista
 */
tPosL next(tPosL, tList);

/**
 * Devuelve la posición en la lista del elemento anterior al actual
 * @param posicion Posición actual
 * @param lista Lista que contiene el elemento
 * @return Posición del elemento anterior, o nulo si es el primero
 * @pre La lista no esta vacía
 * @pre La posición actual es una posición valida de la lista
 */
tPosL previous(tPosL, tList);

/**
 * Añade un elemento a la lista de forma ordenada por el campo productId
 * @param elemento Elemento a añadir a la lista
 * @param lista Lista
 * @return Lista con el elemento insertado
 * @return True si se ha conseguido insertar, false en caso contrario
 * @pre La posición a introducir es valida o nula
 * @post Las posiciones anteriores a la del elemento insertado pueden haber variado
 */
bool insertItem (tItemL, tList*);

/**
 * Elimina de la lista un elemento con cierta posición
 * @param posicion Posición del elemento a eliminar
 * @param lista Lista de la que eliminar el elemento
 * @return Lista sin el elemento correspondiente
 * @pre La posición a introducir es valida
 * @post Las posiciones posteriores a la del elemento eliminado pueden haber variado
 */
void deleteAtPosition (tPosL, tList*);

/**
 * Devuelve el elemento en la posición indicada de la lista
 * @param posicion Posición del elemento buscado
 * @param lista Lista donde realizar la búsqueda
 * @return Elemento en la posición indicada de la lista
 * @pre La posición a introducir es valida y el producto en dicha posición tiene una pila de pujas vacía
 * @post Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado
 */
tItemL getItem (tPosL, tList);

/**
 * Modifica el contenido de un elemento de la lista
 * @param elemento El nuevo elemento a modificar
 * @param posicion La posición del elemento modificar
 * @param lista Lista en la que modificar el elemento
 * @pre La posición a introducir es valida
 */
void updateItem (tItemL, tPosL, tList*);

/**
 * Busca el primer elemento con cierto contenido en la lista
 * @param producto Elemento a buscar
 * @param lista Lista donde buscarlo
 * @return Posición donde se encuentra el elemento buscado, o nulo si no se encuentra
 */
tPosL findItem (tProductId, tList);

#endif
