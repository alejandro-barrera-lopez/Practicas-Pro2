#ifndef PRO2_2022_P1_TYPES_H
#define PRO2_2022_P1_TYPES_H

// TODO Para as listas, preguntar se se pode definir aquí para non ter que poñelo en cada lista
#include <stdbool.h>
#include <string.h>

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
