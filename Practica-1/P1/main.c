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

// TODO Comentar?
// TODO Preguntar se está ben feito declaralas aquí arriba
void new(tProductId, tUserId, tProductCategory, tProductPrice, tList*);
void delete(tProductId, tList*);
void bid(tProductId, tUserId, tProductPrice, tList*);
void stats(tList*);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList* lista) {

	printf("********************\n");
	switch (command) {
		case 'N': // TODO Preguntar que facer se se introduce unha categoria incorrecta. Hai que esperar este caso?
			printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
			// productCategory: 0 -> book
			//					1 -> painting
			// Por lo tanto, la funcion strcmp(param3, "book") tendra las siguientes salidas:
			//					"book"		-> 0 (book)
			//					"painting"	-> 1 (painting)
			new(param1, param2, strcmp(param3, "book") == 0 ? book : painting, strtof(param4, NULL), lista);
			break;
		case 'S':
			printf("%s %c\n", commandNumber, command);
			stats(lista);
			break;
		case 'B':
			printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
			bid(param1, param2, strtof(param3, NULL), lista);
			break;
		case 'D':
			printf("%s %c: product %s\n", commandNumber, command, param1);
			delete(param1, lista);
			break;
		default:
			break;
	}
}

void readTasks(char *filename) {
	// TODO Borrar a declaración da lista, non sei se ten que ir aquí
	tList lista;
	createEmptyList(&lista);

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

			processCommand(commandNumber, command[0], param1, param2, param3, param4, &lista);
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

void new(tProductId productId, tUserId userId, tProductCategory productCategory, tProductPrice productPrice, tList* lista) {
	tItemL elemento;

	if(findItem(productId, *lista) != LNULL) {
		printf("+ Error: New not possible\n");
		return;
	}

	strcpy(elemento.productId, productId);
	strcpy(elemento.seller, userId);
	elemento.productCategory = productCategory;
	elemento.productPrice = productPrice;
	elemento.bidCounter = 0;

	if(insertItem(elemento, LNULL, lista)) {
		printf("* New: product %s seller %s category %s price %.2f\n", productId, userId, productCategory == 0 ? "book" : "painting", productPrice);
	} else {
		printf("+ Error: New not possible\n");
	}
}

void delete(tProductId productId, tList* lista) {
	// TODO Facer unha funcion categoryToString/getCategoryName?
	tPosL posicion = findItem(productId, *lista);
	tItemL producto;
	if(posicion == LNULL) {
		printf("+ Error: Delete not possible\n");
		return;
	}
	producto = getItem(posicion, *lista);
	printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", producto.productId, producto.seller,
		   producto.productCategory == 0 ? "book" : "painting", producto.productPrice, producto.bidCounter);
	deleteAtPosition(posicion, lista);
}

void bid(tProductId productId, tUserId bidder, tProductPrice puja, tList* lista) {
	tPosL posicion = findItem(productId, *lista);
	tItemL producto;
	if(posicion == LNULL) { // TODO Poñer posicion != LNULL e deixar as precondicions para o final? Delete igual
		printf("+ Error: Bid not possible\n");
		return;
	}
	producto = getItem(posicion, *lista);
	if(strcmp(producto.seller, bidder) == 0) { // Si el vendedor es el mismo usuario que el bidder
		printf("+ Error: Bid not possible\n");
		return;
	}
	if(puja <= producto.productPrice) {
		printf("+ Error: Bid not possible\n");
		return;
	}
	producto.productPrice = puja;
	producto.bidCounter++;

	updateItem(producto, posicion, lista);

	printf("* Bid: product %s seller %s category %s price %.2f bids %d\n", producto.productId, producto.seller,
		   producto.productCategory == 0 ? "book" : "painting", producto.productPrice, producto.bidCounter);
}

void stats(tList* lista) {
	tPosL pos;
	tItemL item;
	// Gardalo en dous arrays en vez de catro variables?
	int contadorLibros = 0, contadorPinturas = 0;
	int contador[2] = {0, 0};
	// contador[0] -> Contador de libros
	// contador[1] -> Contador de pinturas
	float sumaPrecioLibros = 0, sumaPrecioPinturas = 0; // TODO Nombre das variables demasiado largo?
	float sumaPrecios[2] = {0, 0};
	// sumaPrecios[0] -> Suma de los precios de los libros
	// sumaPrecios[1] -> Suma de los precios de las pinturas

	if (!isEmptyList(*lista)) {
		pos = first(*lista);
		while (pos != LNULL) {
			item = getItem(pos, *lista);
			printf("Product %s seller %s category %s price %.2f bids %d\n", item.productId, item.seller, item.productCategory == 0 ? "book" : "painting", item.productPrice, item.bidCounter);
			printf("Categoria = %d \n", item.productCategory);
			contador[item.productCategory]++;
			sumaPrecios[item.productCategory] += item.productPrice;
			if(item.productCategory == 0) { // Libro
				contadorLibros++;
				sumaPrecioLibros += item.productPrice;
			} else { // Pintura
				contadorPinturas++;
				sumaPrecioPinturas += item.productPrice;
			}
			pos = next(pos, *lista);
		}
		// TODO Deberia de gardar nunha variable a media?
		// Average
		printf("\nCategory  Products    Price  Average\n"); // Cabecera
//		printf("Book      %8d %8.2f %8.2f\n", contadorLibros, sumaPrecioLibros, contadorLibros == 0 ? 0 : sumaPrecioLibros/(float)contadorLibros);
//		printf("Painting  %8d %8.2f %8.2f\n", contadorPinturas, sumaPrecioPinturas, contadorPinturas == 0 ? 0 : sumaPrecioPinturas/(float)contadorPinturas);
		printf("Book      %8d %8.2f %8.2f\n", contador[0], sumaPrecios[0], contador[0] == 0 ? 0 : sumaPrecios[0]/(float)contador[0]);
		printf("Painting  %8d %8.2f %8.2f\n", contador[1], sumaPrecios[1], contador[1] == 0 ? 0 : sumaPrecios[1]/(float)contador[1]);
	} else {
		printf("+ Error: Stats not possible\n");
	}
}