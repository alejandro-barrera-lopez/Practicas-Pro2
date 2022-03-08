/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 08 / 03 / 22
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define LIST_SIZE_LIMIT 25
#define LNULL -1

typedef int tPosL;

typedef struct {
    tItemL elemento[LIST_SIZE_LIMIT];
    tPosL lastPos;
} tList;

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

#endif