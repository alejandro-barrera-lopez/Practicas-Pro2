/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 03 / 03 / 22
 */

#ifndef PRO2_2022_P1_TYPES_H
#define PRO2_2022_P1_TYPES_H

#define NAME_LENGTH_LIMIT 10

typedef char tUserId[NAME_LENGTH_LIMIT];

typedef char tProductId[NAME_LENGTH_LIMIT];

typedef enum {book, painting} tProductCategory;

typedef float tProductPrice;

typedef int tBidCounter;

typedef struct tItemL {
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
} tItemL;


#endif //PRO2_2022_P1_TYPES_H
