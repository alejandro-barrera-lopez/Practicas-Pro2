/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: ** / ** / **
 */

#include "dynamic_list.h"

void createEmptyList (tList* L) {
	*L = LNULL;
}

bool isEmptyList (tList L) {
	return L == LNULL;
}

tPosL first (tList L) {
	return L;
}

tPosL last (tList L) {
	tPosL p;

	for(p = L; p->next != LNULL; p = p->next);

	return p;
}

tPosL previous (tPosL p, tList L) {
	tPosL q;

	if(p==L)
		return LNULL;
	else
		for(q = L; q->next != p; q = q->next);

	return q;
}

tPosL next (tPosL p, tList L) {
	return p->next;
}


bool createNode(tPosL* p) {
	*p = malloc(sizeof(struct tNode));
	return *p != LNULL;
}

bool insertItem (tItemL d, tPosL p, tList* L) {
	tPosL q, r;

	if(!createNode(&q))
		return false;
	else
	{
		q->data = d;
		q->next = LNULL;

		if(*L == LNULL)
			*L = q;
		else if (p == LNULL)
		{
			for(r = *L; r->next != LNULL; r = r->next);
			r->next = q;
		}
		else if (p == *L)
		{
			q->next = p;
			*L = q;
		}
		else
		{
			q->data = p->data;
			p->data = d;
			q->next = p->next;
			p->next = q;
		}
		return true;
	}
}



void deleteAtPosition(tPosL p, tList* L) {
	tPosL q;

	if(p == *L) {
		*L = (*L)->next;
	}else if(p->next == LNULL){
		for(q = *L; q->next != p; q = q->next);
		q->next = LNULL;
	}else{
		q = p->next;
		p->data = q->data;
		p->next = q->next;
		p = q;
	}
	free(p);
}

tItemL getItem (tPosL p, tList L) {
	return p->data;
}

void updateItem (tItemL d, tPosL p, tList* L) {
	p->data = d;
}

tPosL findItem (tProductId d, tList L) {
	tPosL p = L;

	while((p!=LNULL)&&strcmp(d, p->data.productId)!=0){
		p = p->next;
	}
	return p;
}