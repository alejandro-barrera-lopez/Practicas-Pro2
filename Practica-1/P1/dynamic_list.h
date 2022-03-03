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
#include <stdlib.h> // TODO include aqui ou no .c?

#define LIST_SIZE_LIMIT 25
#define LNULL NULL

// TODO Volver a facer a lista dinamica e comprobar se esta ben a definicion
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

// TODO updateItem tList con puntero ou sin puntero???
void updateItem (tItemL, tPosL, tList*);

tPosL findItem (tProductId, tList);

#endif
