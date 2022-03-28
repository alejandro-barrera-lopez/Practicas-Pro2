/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"

#define MAX_BUFFER 255

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

/**
 * Procesa un comando formado por una línea de texto del archivo de texto correspondiente
 * @param commandNumber Contador de los comandos introducidos, se refiere al número de comando, en un String
 * @param command Letra correspondiente al comando
 * @param param1 Primer parámetro del comando
 * @param param2 Segundo parámetro del comando
 * @param param3 Tercer parámetro del comando
 * @param param4 Cuarto parámetro del comando
 * @param lista Lista de productos
 */
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
        case 'A':
            break;
        case 'W':
            break;
        case 'R':
            break;
        default:
            break;
    }
}

/**
 * Lee las órdenes del programa desde un archivo de texto
 * @param filename Nombre del archivo por el que se leerán las órdenes
 */
void readTasks(char *filename) {
	tList lista; // Define la lista
	createEmptyList(&lista); // Inicializa la lista vacia

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

/**
 * Es el procedimiento principal del programa
 * @param nargs Número de argumentos introducidos por consola
 * @param args Array que contiene los argumentos introducidos por consola
 * @return Código de ejecución del programa
 */
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

char* pCategoryToString (tProductCategory productCategory) {
	if(productCategory == book) { // Si la categoría es libro, devuelve un string "book"
		return "book";
	} else { // Sino, devuelve "painting"
		return "painting";
	}
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
	tItemL producto; // Define una variable tItemL para posteriormente almacenar el nuevo producto

	// Si el producto ya está en la lista, no se puede volver a insertar, por lo que se imprime un mensaje de error
	if(findItem(productId, *lista) != LNULL) {
		printf("+ Error: New not possible\n");
		return;
	}

	// Se copian los valores indicados para el producto
	strcpy(producto.productId, productId);
	strcpy(producto.seller, userId);
	producto.productCategory = productCategory;
	producto.productPrice = productPrice;
	producto.bidCounter = 0; // Y se inicializa el contador de pujas en 0

	if(insertItem(producto, lista)) { // Si el producto se insertó correctamente en la lista
		// se imprime la información respectiva a la correcta ejecución de la función
		printf("* New: product %s seller %s category %s price %.2f\n",
			   productId, userId, pCategoryToString(producto.productCategory), productPrice);
	} else { // Si el producto no se insertó correctamente, imprime un mensaje de error
		printf("+ Error: New not possible\n");
	}
}

void delete(tProductId productId, tList* lista) {
	tItemL producto; // Define una variable tItemL para posteriormente almacenar el nuevo producto
	// Se define una variable de tipo tPosL para almacenar la posición del producto buscado en la lista
	tPosL posicion = findItem(productId, *lista);
	if(posicion == LNULL) { // Si la posición es nula, significa que no existe en la lista,
		printf("+ Error: Delete not possible\n"); // por lo que se imprime un mensaje de error
		return;
	}
	// Se asigna a 'producto' el valor del producto a borrar en la lista, para imprimir su información
	// y borrarlo posteriormente
	producto = getItem(posicion, *lista);
	// Imprime la información respectiva a la correcta ejecución de la función
	printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", producto.productId, producto.seller,
		   pCategoryToString(producto.productCategory), producto.productPrice, producto.bidCounter);
	// Finalmente, borra el producto de la lista
	deleteAtPosition(posicion, lista);
}

void bid(tProductId productId, tUserId bidder, tProductPrice puja, tList* lista) {
	tItemL producto; // Define una variable de tipo tItemL para posteriormente almacenar el producto por el cual pujar
	// Se define una variable tPosL y se almacena en ella la posición del producto buscado en la lista
	tPosL posicion = findItem(productId, *lista);
	if(posicion != LNULL) { // Si la posición no es nula, el producto existe en la lista
		producto = getItem(posicion, *lista); // Se almacena el producto en 'producto' desde la lista
		if(strcmp(producto.seller, bidder) != 0) { // Si el vendedor es un usuario distinto al pujador
			if(puja > producto.productPrice) { // Si el precio de puja es mayor que el anterior precio del producto
				producto.productPrice = puja; // El nuevo precio será el de la puja
				producto.bidCounter++; // Se aumenta el contador de pujas del producto
				updateItem(producto, posicion, lista); // Actualiza el producto en la lista, con sus nuevos valores
				// Imprime la información correspondiente al correcto funcionamiento del programa
				printf("* Bid: product %s seller %s category %s price %.2f bids %d\n", producto.productId, producto.seller,
					   pCategoryToString(producto.productCategory), producto.productPrice, producto.bidCounter);
				// Termina la función
				return;
			}
		}
	} // Si no se han cumplido las tres anteriores condiciones, imprime un mensaje de error
	printf("+ Error: Bid not possible\n");
}

void imprimirInfoProducto (tItemL item) { // Imprime la información del producto 'item'
	printf("Product %s seller %s category %s price %.2f bids %d\n", item.productId,
		   item.seller, pCategoryToString(item.productCategory), item.productPrice, item.bidCounter);
}

void imprimirEstadisticas (unsigned int contador[2], float sumaPrecios[2]) {
	printf("\nCategory  Products    Price  Average\n"); // Cabecera
	printf("Book      %8d %8.2f %8.2f\n", // Imprime las estadísticas de los libros
		   contador[0], sumaPrecios[0], calcularMedia(sumaPrecios[0], contador[0]));
	printf("Painting  %8d %8.2f %8.2f\n", // Imprime las estadísticas de los cuadros de pintura
		   contador[1], sumaPrecios[1], calcularMedia(sumaPrecios[1], contador[1]));
}

void stats(tList* lista) {
	tPosL pos; // Inicializa una variable de tipo tPosL para almacenar la posición del elemento a buscar
	tItemL item; // Inicializa una variable de tipo tItemL para almacenar el elemento a buscar
	unsigned int contador[2] = {0, 0}; /* Declara e inicializa a 0 un contador para libros, y otro para pinturas
	contador[0] -> Contador de libros
	contador[1] -> Contador de pinturas */
	float sumaPrecios[2] = {0, 0}; /* Declara e inicializa a 0 un contador para la suma de precios de libros,
	y otro para pinturas
	umaPrecios[0] -> Suma de los precios de los libros
	sumaPrecios[1] -> Suma de los precios de las pinturas */

	if (!isEmptyList(*lista)) { // Si la lista no está vacía
		pos = first(*lista); // Se inicializa 'pos' con el valor de la posición inicial de la lista
		while (pos != LNULL) { // Este bucle recorre la lista desde la posición inicial hasta la final
			item = getItem(pos, *lista); // Se asignan a 'item' los valores del elemento buscado en la lista
			contador[item.productCategory]++; // Se aumenta el contador de libros/pinturas
			sumaPrecios[item.productCategory] += item.productPrice; // Se suma el precio del libro/pintura al sumador
			imprimirInfoProducto(item); // Imprime la información individual del producto
			pos = next(pos, *lista); // Pasa a la siguiente posición de la lista
		}
		imprimirEstadisticas(contador, sumaPrecios); /* Imprime las estadísticas de todos los productos de la lista,
														segregados en libros y pinturas */
	} else { // La lista no está vacía, por lo que se imprime un mensaje de error
		printf("+ Error: Stats not possible\n");
	}
}