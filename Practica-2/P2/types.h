/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 29 / 04 / 22
 */

#ifndef PRO2_2022_P2_TYPES_H
#define PRO2_2022_P2_TYPES_H

#define NAME_LENGTH_LIMIT 10


typedef char tUserId[NAME_LENGTH_LIMIT];

typedef char tProductId[NAME_LENGTH_LIMIT];

typedef enum {book, painting} tProductCategory;

typedef float tProductPrice;

typedef int tBidCounter;

#endif //PRO2_2022_P2_TYPES_H
