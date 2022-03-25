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

/**
 * Realiza la alta de un nuevo producto. Para ello, comprueba que sea valido y, si lo es,
 * lo introduce en la lista de productos
 * @param productId			ID del producto a dar de alta
 * @param userId			ID del usuario que sube el producto
 * @param productCategory	Categoria del nuevo producto
 * @param productPrice		Precio del nuevo producto
 * @param lista				Lista de productos
 */
void new(tProductId, tUserId, tProductCategory, tProductPrice, tList*);

/**
 * Da de baja un producto. Para ello, comprueba si el producto existe y, en dicho caso,
 * procede a borrarlo
 * @param productId	Producto a dar de baja
 * @param lista		Lista de productos
 */
void delete(tProductId, tList*);

/**
 * Intenta realizar una puja por un determinado producto. Para ello, comprueba si el producto
 * existe en la lista, si el usuario vendedor es distinto al pujante y si el precio de la puja
 * es mayor al anterior precio del producto. En caso de cumplirse estas tres condiciones, se
 * realiza la puja.
 * @param productId	Producto por el cual se va a pujar
 * @param bidder	ID del usuario que hace la puja
 * @param puja		Precio de la puja
 * @param lista		Lista de productos
 */
void bid(tProductId, tUserId, tProductPrice, tList*);

/**
 * Imprime un listado de los productos actuales y sus datos
 * @param lista Lista de productos
 */
void stats(tList*);

/**
 * Devuelve un string con el nombre del valor del enum introducido
 * @param productCategory enum introducido
 * @return Nombre correspondiente al valor del enum introducido
 */
char* pCategoryToString (tProductCategory);

/**
 * Imprime por pantalla la informacion del producto introducido
 * @param item Producto a imprimir
 * @pre El producto no es nulo
 */
void imprimirInfoProducto (tItemL);

/**
 * Calcula la media aritmetica mediante dos parametros
 * @param suma Suma de los numeros a realizar la media
 * @param n Cantidad de numeros
 * @return Media aritmetica
 */
float calcularMedia (float, unsigned int);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList* lista) {

	printf("********************\n");
	switch (command) {
		case 'N': // New
			printf("%s %c: product %s seller %s category %s price %s\n",
				   commandNumber, command, param1, param2, param3, param4);
			 /* productCategory: 0 -> book
			 					 1 -> painting
			 Por lo tanto, la funcion strcmp(param3, "book") tendra las siguientes salidas:
								"book"		-> 0 (book)
								"painting"	-> 1 (painting) */
			new(param1, param2, strcmp(param3, "book") == 0 ? book : painting,
				strtof(param4, NULL), lista);
			break;
		case 'S': // Stats
			printf("%s %c\n", commandNumber, command);
			stats(lista);
			break;
		case 'B': // Bid
			printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
			bid(param1, param2, strtof(param3, NULL), lista);
			break;
		case 'D': // Delete
			printf("%s %c: product %s\n", commandNumber, command, param1);
			delete(param1, lista);
			break;
		default:
			break;
	}
}

void readTasks(char *filename) {
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
	deleteList(&lista);
}

int main(int nargs, char **args) {
	char *file_name = "new.txt";

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

/**
 * Devuelve un string con el nombre del valor del enum introducido
 * @param productCategory enum introducido
 * @return
 */
char* pCategoryToString (tProductCategory productCategory) {
	return productCategory == 0 ? "book" : "painting";
}

float calcularMedia (float suma, unsigned int n){
	// Para evitar una division entre 0, comprueba si n es distinto a 0
	if(n == 0) { // En dicho caso, devuelve 0
		return 0;
	} else { // Sino, devuelve la media aritmetica correspondiente
		return suma/(float)n;
	}
}

void new(tProductId productId, tUserId userId, tProductCategory productCategory, tProductPrice productPrice, tList* lista) {
	tItemL producto;

	if(findItem(productId, *lista) != LNULL) {
		printf("+ Error: New not possible\n");
		return;
	}

	strcpy(producto.productId, productId);
	strcpy(producto.seller, userId);
	producto.productCategory = productCategory;
	producto.productPrice = productPrice;
	producto.bidCounter = 0;

	if(insertItem(producto, LNULL, lista)) {
		printf("* New: product %s seller %s category %s price %.2f\n",
			   productId, userId, pCategoryToString(producto.productCategory), productPrice);
	} else {
		printf("+ Error: New not possible\n");
	}
}


void delete(tProductId productId, tList* lista) {
	tPosL posicion = findItem(productId, *lista);
	tItemL producto;
	if(posicion == LNULL) {
		printf("+ Error: Delete not possible\n");
		return;
	}
	producto = getItem(posicion, *lista);
	printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", producto.productId, producto.seller,
		   pCategoryToString(producto.productCategory), producto.productPrice, producto.bidCounter);
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
		   pCategoryToString(producto.productCategory), producto.productPrice, producto.bidCounter);
}

void imprimirInfoProducto (tItemL item) {
	printf("Product %s seller %s category %s price %.2f bids %d\n", item.productId,
		   item.seller, pCategoryToString(item.productCategory), item.productPrice, item.bidCounter);
}

void imprimirEstadisticas (unsigned int contador[2], float sumaPrecios[2]) {
	printf("\nCategory  Products    Price  Average\n"); // Cabecera
	printf("Book      %8d %8.2f %8.2f\n",
		   contador[0], sumaPrecios[0], calcularMedia(sumaPrecios[0], contador[0]));
	printf("Painting  %8d %8.2f %8.2f\n",
		   contador[1], sumaPrecios[1], calcularMedia(sumaPrecios[1], contador[1]));
}

/**
 * Imprime un listado de los productos actuales y sus datos
 * @param lista Lista de productos
 */
void stats(tList* lista) {
	tPosL pos;
	tItemL item;
	unsigned int contador[2] = {0, 0};
	// contador[0] -> Contador de libros
	// contador[1] -> Contador de pinturas
	float sumaPrecios[2] = {0, 0};
	// sumaPrecios[0] -> Suma de los precios de los libros
	// sumaPrecios[1] -> Suma de los precios de las pinturas

	if (!isEmptyList(*lista)) {
		pos = first(*lista);
		while (pos != LNULL) {
			item = getItem(pos, *lista);
			contador[item.productCategory]++;
			sumaPrecios[item.productCategory] += item.productPrice;
			imprimirInfoProducto(item);

			pos = next(pos, *lista);
		}

		imprimirEstadisticas(contador, sumaPrecios);
	} else {
		printf("+ Error: Stats not possible\n");
	}
}