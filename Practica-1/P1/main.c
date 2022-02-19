/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Alejandro Barrera López LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

// TODO Preguntar se está ben feito declaralas aquí arriba
// TODO Preguntar se é mellor parsear o formato dos Strings antes ou despois das funcións
void new(tProductId, tUserId, tProductCategory, tProductPrice, tList);
void delete(tProductId, tList);
void bid(tProductId, tUserId, tProductPrice, tList);
void stats(tList);
void printProduct(tList);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {

	switch (command) {
		case 'N':
			printf("Command: %s %c %s %s %s %s\n", commandNumber, command, param1, param2, param3, param4);
			break;
		case 'S':
			printf("Command: %s %c %s %s %s %s\n", commandNumber, command, param1, param2, param3, param4);
			break;
		case 'B':
			printf("Command: %s %c %s %s %s %s\n", commandNumber, command, param1, param2, param3, param4);
			break;
		case 'D':
			printf("Command: %s %c %s %s %s %s\n", commandNumber, command, param1, param2, param3, param4);
			break;
		default:
			break;
	}
}

void readTasks(char *filename) {
	FILE *f = NULL;
	char *commandNumber, *command, *param1, *param2, *param3, *param4;
	const char delimiters[] = " \n\r";
	char buffer[MAX_BUFFER];

	f = fopen(filename, "r");

	if (f != NULL) {

		while (fgets(buffer, MAX_BUFFER, f)) {
			commandNumber = strtok(buffer, delimiters);
			command = strtok(NULL, delimiters);
			param1 = strtok(NULL, delimiters);
			param2 = strtok(NULL, delimiters);
			param3 = strtok(NULL, delimiters);
			param4 = strtok(NULL, delimiters);

			processCommand(commandNumber, command[0], param1, param2, param3, param4);
		}

		fclose(f);

	} else {
		printf("Cannot open file %s.\n", filename);
	}
}


int main(int nargs, char **args) {

	char *file_name = "new.txt";
	tList lista;
	createEmptyList(&lista);

	if (nargs > 1) {
		file_name = args[1];
	} else {
		#ifdef INPUT_FILE
		file_name = INPUT_FILE;
		#endif
	}

	readTasks(file_name);

	return 0;
}




void new(tProductId productId, tUserId userId, tProductCategory productCategory, tProductPrice productPrice, tList lista) {
	tItemL elemento;

	strcpy(elemento.productId, productId);
	strcpy(elemento.seller, userId);
	elemento.productCategory = productCategory;
	elemento.productPrice = productPrice;

	if(insertItem(elemento, LNULL, &lista)) {
		printf("* New: product %s seller %s category %s price %f", productId, userId, productCategory == 0 ? "book" : "painting", productPrice);
	} else {
		printf("+ Error: New not possible");
	}
}

void delete(tProductId productId, tList lista) {

}

// TODO Preguntar se pasa algo polo Spanglish
void bid(tProductId productId, tUserId userId, tProductPrice productPrice, tList lista) {

}

void stats(tList lista) {
	tPosL pos;
	tItemL item;
	int contadorLibros = 0, contadorPinturas = 0;
	float sumaPrecioLibros = 0, sumaPrecioPinturas = 0; // TODO Nombre das variables demasiado largo?

	printf("Category  Products    Price  Average\n"); // Cabecera
	if (!isEmptyList(lista)) {
		pos = first(lista);
		while (pos != LNULL) {
			item = getItem(pos, lista);
			printf("Product %s seller %s category %s price %.2f bids %d\n", item.productId, item.seller, item.productCategory == 0 ? "Book" : "Painting", item.productPrice, item.bidCounter);
			pos = next(pos, lista);
		}
		// Average

		printf("Book      %8d %8.2f %8.2f\n", contadorLibros, sumaPrecioLibros, sumaPrecioLibros/(float)contadorLibros);
		printf("Painting  %8d %8.2f %8.2f\n", contadorPinturas, sumaPrecioPinturas, sumaPrecioPinturas/(float)contadorPinturas);
	}
	printf(" )\n");
}