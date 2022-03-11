/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 03 / 03 / 22
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdlib.h>		// Por malloc() y free()
#include <stdbool.h>	// Para utilizar el tipo 'bool'
#include <string.h>		// Por strcmp()

#define LIST_SIZE_LIMIT 25
#define LNULL NULL

typedef struct tNode* tPosL;

struct tNode {
	tItemL dato;
	tPosL siguiente;
};

typedef tPosL tList;

void createEmptyList (tList*);

bool isEmptyList (tList);

tPosL first (tList);

tPosL last (tList);

tPosL next(tPosL, tList);

tPosL previous(tPosL, tList);

bool insertItem (tItemL, tPosL, tList*);

void deleteAtPosition (tPosL, tList*);

tItemL getItem (tPosL, tList);

void updateItem (tItemL, tPosL, tList*);

tPosL findItem (tProductId, tList);

void deleteList(tList* L);

#endif
