    /*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 08 / 04 / 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"

#define MAX_BUFFER 255

// TODO Comprobar que non se pasa dos 100/120 caracteres de ancho

// Funciones principales del programa
/**
* Realiza la alta de un nuevo producto. Para ello, comprueba que sea valido y, si lo es,
		* lo introduce en la lista de productos
* @param productId			ID del producto a dar de alta
* @param userId				ID del usuario que sube el producto
* @param productCategory	Categoria del nuevo producto
* @param productPrice		Precio del nuevo producto
* @param lista				Lista de productos
* @return True si se ha realizado correctamente, false en caso contrario
*/
bool new (tProductId productId, tUserId userId, tProductCategory productCategory,
		  tProductPrice productPrice, tList* lista);

/**
 * Da de baja un producto. Para ello, comprueba si el producto existe y, en dicho caso,
 * procede a borrarlo
 * @param productId		Producto a dar de baja
 * @param verbose   	Booleano que indica si se imprimir información o no, para reutilizar la función en Remove()
 * @param lista			Lista de productos
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool delete (tProductId productId, bool verbose, tList* lista);

/**
 * Intenta realizar una puja por un determinado producto. Para ello, comprueba si el producto
 * existe en la lista, si el usuario vendedor es distinto al pujante y si el precio de la puja
 * es mayor al anterior precio del producto. En caso de cumplirse estas tres condiciones, se
 * realiza la puja.
 * @param productId	Producto por el cual se va a pujar
 * @param bidder	ID del usuario que hace la puja
 * @param puja		Precio de la puja
 * @param lista		Lista de productos
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool bid (tProductId productId, tUserId bidder, tProductPrice puja, tList* lista);

/**
 * Imprime un listado de los productos actuales y sus datos
 * @param lista Lista de productos
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool stats (tList* lista);

/**
 * Adjudica la puja de un producto
 * @param productId ID de la puja
 * @param lista 	Lista de productos
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool award (tProductId productId, tList* lista);

/**
 * Retira la ultima puja de un producto
 * @param productId ID del producto
 * @param seller	ID del usuario vendedor
 * @param lista 	Lista de productos
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool withdraw (tProductId productId, tUserId seller, tList* lista);

/**
 * Elimina todos los productos sin pujas
 * @param lista Lista de productos
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool Remove (tList* lista);

// Funciones auxiliares

/**
 * Imprime un mensaje de error para el comando introducido
 * @param command Car�cter correspondiente al comando del error
 * @pre El caracter de comando es uno de los 7 indicados por el enunciado (N, D, B, A, W, R, S)
 */
void printError (char command);

/**
 * Devuelve un string con el nombre del valor del enum introducido
 * @param productCategory enum introducido
 * @return Nombre correspondiente al valor del enum introducido
 */
char* getCategoryName (tProductCategory productCategory);

/**
 * Imprime por pantalla la informacion del producto introducido
 * @param item Producto a imprimir
 * @pre El producto no es nulo
 */
void imprimirInfoProducto (tItemL prod);

/**
 * Calcula la media aritmetica mediante dos parametros
 * @param suma 	Suma de los numeros a realizar la media
 * @param n 	Cantidad de numeros
 * @return Media aritmetica
 */
float calcularMedia (float, unsigned int);
/**
 * Procesa un comando formado por una línea de texto del archivo de texto correspondiente
 * @param commandNumber String con el número de comando introducido, en un String
 * @param command 		Letra correspondiente al comando
 * @param param1 		Primer parámetro del comando
 * @param param2 		Segundo parámetro del comando
 * @param param3 		Tercer parámetro del comando
 * @param param4 		Cuarto parámetro del comando
 * @param lista 		Lista de productos
 */
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3,
					char *param4, tList* lista) {

	bool ok = false; // Booleano creado para detectar si se hubo un error al ejecutar del comando
	printf("********************\n");
	switch (command) {
        case 'N': // New
			printf("%s %c: product %s seller %s category %s price %s\n",
				   commandNumber, command, param1, param2, param3, param4);
			/* productCategory: 0 -> book
								 1 -> painting
			Por lo tanto, la funcion strcmp(param3, "book") tendra las siguientes salidas:
							   "book"		-> 0 (book)
							   "painting"	-> 1 (painting) */ // TODO Esto anterior � falso, corregir
			ok = new(param1, param2, strcmp(param3, "book") == 0 ? book : painting,
				strtof(param4, NULL), lista);
            break;
        case 'S': // Stats
			printf("%s %c\n", commandNumber, command);
			ok = stats(lista);
            break;
        case 'B': // Bid
			printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
			ok = bid(param1, param2, strtof(param3, NULL), lista);
            break;
        case 'D': // Delete
			printf("%s %c: product %s\n", commandNumber, command, param1);
			ok = delete(param1, true, lista);
            break;
        case 'A': // Award
			printf("%s %c: product %s\n", commandNumber, command, param1);
			ok = award(param1, lista);
            break;
        case 'W': // Withdraw
			printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
			ok = withdraw(param1, param2, lista);
			break;
        case 'R': // Remove
			printf("%s %c\n", commandNumber, command);
			ok = Remove(lista);
            break;
        default:
            break;
    }
	if(!ok) { // En caso de error en la ejecuci�n, lo imprime
		printError(command);
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

	// Borra la lista, liberando la memoria asignada
	deleteList(&lista);
}

/**
 * Es el procedimiento principal del programa
 * @param nargs Número de argumentos introducidos por consola
 * @param args 	Array que contiene los argumentos introducidos por consola
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

char* getCategoryName (tProductCategory productCategory) {
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

void printError (char command) {
	char* commandName;
	switch (command) {
		case 'N': // New
			commandName = "New";
			break;
		case 'D': // Delete
			commandName = "Delete";
			break;
		case 'B': // Bid
			commandName = "Bid";
			break;
		case 'A': // Award
			commandName = "Award";
			break;
		case 'W': // Withdraw
			commandName = "Withdraw";
			break;
		case 'R': // Remove
			commandName = "Remove";
			break;
		case 'S': // Stats
			commandName = "Stats";
			break;
		default:
			return;
	}

	printf("+ Error: %s not possible\n", commandName);
}

void imprimirInfo (tItemL p, char* comando, bool bidder, bool bids) {
    if(bids) {

    }
    printf("* %s: product %s %s %s category %s price %.2f\n", comando, p.productId, bidder ? "bidder" : "seller",
           bidder ? peek(p.bidStack).bidder : p.seller, p.productCategory == book ? "book" : "painting", p.productPrice);
}

bool new(tProductId productId, tUserId userId, tProductCategory productCategory, tProductPrice productPrice, tList* lista) {
    tItemL prod;
    strcpy(prod.productId, productId);
    strcpy(prod.seller, userId);
    prod.productCategory = productCategory;
    prod.productPrice = productPrice;
    prod.bidCounter = 0;
    createEmptyStack(&prod.bidStack);

    if(findItem(productId, *lista) == LNULL && insertItem(prod, lista)) { // TODO Sería mellor inicializar o tItemL producto dentro do if, e comprobar con outro if o insertItem?
        printf("* New: product %s seller %s category %s price %.2f\n", productId, userId, getCategoryName(prod.productCategory), productPrice);
        return true;
    }
    return false;
}

/*bool new(tProductId productId, tUserId userId, tProductCategory productCategory, tProductPrice productPrice, tList* lista) {
	tItemL producto; // Define una variable tItemL para posteriormente almacenar el nuevo producto

	// Si el producto ya está en la lista, no se puede volver a insertar, por lo que se devuelve falso
	if(findItem(productId, *lista) != LNULL) {
		return false;
	}

	// Se copian los valores indicados para el producto
	strcpy(producto.productId, productId);
	strcpy(producto.seller, userId);
	producto.productCategory = productCategory;
	producto.productPrice = productPrice;
	producto.bidCounter = 0; // Se inicializa su contador de pujas en 0
	createEmptyStack(&producto.bidStack); // Se inicializa la pila vacia del producto

	if(insertItem(producto, lista)) { // Si el producto se insertó correctamente en la lista
		// se imprime la información respectiva a la correcta ejecución de la función
		printf("* New: product %s seller %s category %s price %.2f\n",
			   productId, userId, getCategoryName(producto.productCategory), productPrice);
	} else { // Si el producto no se insertó correctamente, devuelve falso
		return false;
	}
	return true; // Se devuelve verdadero, ya que la ejecuci�n del c�digo fue correcta
}*/

/**
 * Elimina el contenido de una pila
 * @param stack Pila a vaciar
 * @return Pila vaciada TODO ???
 */
void deleteStack (tStack stack) {
    while(!isEmptyStack(stack)) {
        pop(&stack);
    }
}

bool delete(tProductId productId, bool verbose, tList* lista) {
    tPosL pos = findItem(productId, *lista);
    tItemL prod;
    if(pos != LNULL) {
        prod = getItem(pos, *lista);
        if(verbose) {
            printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", prod.productId, prod.seller,
                   getCategoryName(prod.productCategory), prod.productPrice, prod.bidCounter);
        }
        deleteStack(prod.bidStack);
        deleteAtPosition(pos, lista);
        return true;
    }
    return false;
}

/*bool delete(tProductId productId, bool imprimirInfo, tList* lista) {
	tItemL producto; // Define una variable tItemL para despu�s almacenar el nuevo producto
	// Define una variable de tipo tPosL para almacenar la posición del producto buscado en la lista
	tPosL posicion = findItem(productId, *lista);
	if(posicion == LNULL) { // Si la posición es nula, significa que no existe en la lista,
		return false; // Por lo que se devuelve falso
	}
	// Asigna a 'producto' el valor del producto a borrar en la lista, para imprimir su información
	// y borrarlo posteriormente
	producto = getItem(posicion, *lista);
	if(imprimirInfo) {
		// Si as� se indica, imprime la información respectiva a la correcta ejecución de la función
		printf("* Delete: product %s seller %s category %s price %.2f bids %d\n",
			   producto.productId, producto.seller,getCategoryName(producto.productCategory),
			   producto.productPrice, producto.bidCounter);
	}
	deleteStack(producto.bidStack); // Borra las pujas existentes
	// Finalmente, borra el producto de la lista y devuelve verdadero
	deleteAtPosition(posicion, lista);
	return true;
}*/

bool bid(tProductId productId, tUserId bidder, tProductPrice precioPuja, tList* lista) {
    tPosL pos;
    tItemL prod;
    tItemS puja;

    if((pos = findItem(productId, *lista)) != LNULL) {
        if(strcmp(bidder, (prod = getItem(pos, *lista)).seller) != 0 && precioPuja > prod.productPrice) {
            strcpy(puja.bidder, bidder);
            puja.productPrice = precioPuja;
            if(push(puja, &prod.bidStack)) {
                prod.bidCounter++;
                updateItem(prod, pos, lista);
                printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n", prod.productId, bidder,
                       getCategoryName(prod.productCategory), precioPuja, prod.bidCounter);
                return true;
            }
        }
    }
    return false;
}

/*// TODO Arreglar este hadouken?
bool bid(tProductId productId, tUserId bidder, tProductPrice precioPuja, tList* lista) {
	// Define una variable de tipo tItemL para posteriormente almacenar el producto por el cual pujar
	tItemL producto;
	tItemS puja;
	// Define una variable tPosL y se almacena en ella la posición del producto buscado en la lista
	tPosL posicion = findItem(productId, *lista);
	if(posicion != LNULL) { // Si la posición no es nula, el producto existe en la lista
		producto = getItem(posicion, *lista); // Se almacena el producto en 'producto' desde la lista
		if(strcmp(producto.seller, bidder) != 0 && precioPuja > producto.productPrice) {
            // Si el vendedor es un usuario distinto al pujador y el precio de puja es mayor que e lanterior precio de producto
				strcpy(puja.bidder, bidder);
				puja.productPrice = precioPuja;
				producto.bidCounter++; // Se aumenta el contador de pujas del producto
				push(puja, &producto.bidStack); // TODO Se se enche a pila?
				updateItem(producto, posicion, lista); // Actualiza el producto en la lista, con sus nuevos valores
				// Imprime la información correspondiente al correcto funcionamiento del programa
				printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n",
					   productId, bidder, getCategoryName(producto.productCategory),
					   precioPuja, producto.bidCounter);
				return true; // Devuelve verdadero, ya que se ha ejecutado correctamente la funci�n
        }
	} // Si no se han cumplido las tres anteriores condiciones, devuelve falso
	return false;
}*/

void imprimirInfoProducto (tItemL prod) { // Imprime la información del producto 'item'
	// TODO Buscar alternativa a if
    printf("Product %s seller %s category %s price %.2f", prod.productId,
           prod.seller, getCategoryName(prod.productCategory), prod.productPrice);
    if(prod.bidCounter == 0) {
        printf(". No bids\n");
    } else {
        printf(" bids %d top bidder %s\n", prod.bidCounter, peek(prod.bidStack).bidder);
    }

}

void imprimirEstadisticas (unsigned int contador[2], float sumaPrecios[2]) {
	printf("\nCategory  Products    Price  Average\n"); // Cabecera
	printf("Book      %8d %8.2f %8.2f\n", // Imprime las estadísticas de los libros
		   contador[0], sumaPrecios[0], calcularMedia(sumaPrecios[0], contador[0]));
	printf("Painting  %8d %8.2f %8.2f\n", // Imprime las estadísticas de los cuadros de pintura
		   contador[1], sumaPrecios[1], calcularMedia(sumaPrecios[1], contador[1]));
}

// TODO Facer cabecera
void imprimirTopBid (tItemL producto) {
	if(producto.bidCounter == 0) {
		printf("Top bid not possible\n");
	} else {
		tItemS puja = peek(producto.bidStack);
		float precioPuja = puja.productPrice;
		float precioProducto = producto.productPrice;

		printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
			   producto.productId, producto.seller, getCategoryName(producto.productCategory),
			   precioProducto, puja.bidder, precioPuja, (precioPuja - precioProducto)/precioProducto * 100);
	}
}

// TODO Facer cabecera @pre ten pujas. Ou non?
float incremento (tItemL producto) {
	if(producto.bidCounter == 0) {
		return 0;
	}
	tItemS puja = peek(producto.bidStack);
	return (puja.productPrice - producto.productPrice) / producto.productPrice * 100;
}

bool stats(tList* lista) {
    tPosL pos;
    tItemL prod;
    float totalPrecios[2] = {0, 0}; // Posición 0 -> book. Posición 1 -> painting
    unsigned int numProductos[2] = {0, 0}; // Posición 0 -> book. Posición 1 -> painting
    tItemL topBid;
    topBid.bidCounter = 0;

    if(!isEmptyList(*lista)) {
        for(pos = first(*lista); pos != LNULL; pos = next(pos, *lista)) {
            prod = getItem(pos, *lista);
            totalPrecios[prod.productCategory] += prod.productPrice;
            numProductos[prod.productCategory]++;
            if(prod.bidCounter > 0 && incremento(prod) > incremento(topBid)) {
                topBid = prod;
            }
            imprimirInfoProducto(prod);
        }
        imprimirEstadisticas(numProductos, totalPrecios);
        imprimirTopBid(topBid);
        return true;
    }
    return false;
}

bool estats(tList* lista) {
	tPosL pos; // Inicializa una variable de tipo tPosL para almacenar la posición del elemento a buscar
	tItemL prod; // Inicializa una variable de tipo tItemL para almacenar el elemento a buscar
	tItemL mejorPuja; // Producto con el mayor incremento porcentual entre su mejor puja y su precio original
	unsigned int contador[2] = {0, 0}; /* Declara e inicializa a 0 un contador para libros, y otro para pinturas
	contador[0] -> Contador de libros
	contador[1] -> Contador de pinturas */
	float sumaPrecios[2] = {0, 0}; /* Declara e inicializa a 0 un contador para la suma de precios de libros,
	y otro para pinturas
	sumaPrecios[0] -> Suma de los precios de los libros
	sumaPrecios[1] -> Suma de los precios de las pinturas */
	mejorPuja.bidCounter = 0;

	if (!isEmptyList(*lista)) { // Si la lista no está vacía
		pos = first(*lista); // Se inicializa 'pos' con el valor de la posición inicial de la lista
		// Cambiar while por for
		while (pos != LNULL) { // Este bucle recorre la lista desde la posición inicial hasta la final
            prod = getItem(pos, *lista); // Se asignan a 'item' los valores del elemento buscado en la lista

			imprimirInfoProducto(prod); // Imprime la información individual del producto

			if(prod.bidCounter > 0) {
				if (incremento (prod) > incremento(mejorPuja)) {
					mejorPuja = prod;
				}
			}

			contador[prod.productCategory]++; // Se aumenta el contador de libros/pinturas
			sumaPrecios[prod.productCategory] += prod.productPrice; // Se suma el precio del libro/pintura al sumador

			pos = next(pos, *lista); // Pasa a la siguiente posición de la lista
		}
		// TODO Funcion para comprobar se un producto non ten pujas?
		/* Imprime las estadísticas de todos los productos de la lista, segregados en libros y pinturas */
		imprimirEstadisticas(contador, sumaPrecios);
		imprimirTopBid(mejorPuja);
		return true; // Devuelve verdadero, ya que la ejecuci�n fue correcta
	} else { // La lista no está vacía, por lo que devuelve falso
		return false;
	}
}

bool award (tProductId productId, tList* lista) {
    tPosL pos;
    tItemL prod;
    tItemS pujaMax;

    if((pos = findItem(productId, *lista)) != LNULL) {
        prod = getItem(pos, *lista);
        if(!isEmptyStack(prod.bidStack)) {
            pujaMax = peek(prod.bidStack);
            printf("* Award: product %s bidder %s category %s price %.2f\n", productId, pujaMax.bidder,
                   prod.productCategory == book ? "book" : "painting", pujaMax.productPrice);
            deleteStack(prod.bidStack);
            deleteAtPosition(pos, lista);
            return true;
        }
    }
    return false;
}

/*bool award (tProductId productId, tList* lista) {
	tPosL pos = findItem(productId, *lista);
	if(pos != LNULL) { // Si hay un productId con el mismo ID en la lista
		tItemL producto = getItem(pos, *lista);
		if(!isEmptyStack(producto.bidStack)) { // Si la lista de pujas del producto no est� vac�a
			tItemS pujaGanadora = peek(producto.bidStack);
			// Imprime informaci�n sobre el comando realizado
			printf("* Award: product %s bidder %s category %s price %.2f\n", productId,
				   pujaGanadora.bidder, getCategoryName(producto.productCategory),
				   pujaGanadora.productPrice);
			delete(productId, false, lista); // Se borra el producto de la lista
			return true;
		}
	}
	return false; // Si no se cumplieron las condiciones anteriores, devuelve falso
}*/

bool withdraw (tProductId productId, tUserId bidder, tList* lista) {
    tPosL pos = findItem(productId, *lista);
    tItemL prod;
    tItemS puja;
    if(pos != LNULL) {
        prod = getItem(pos, *lista);
        if(prod.bidCounter > 0) {
            puja = peek(prod.bidStack);
            if(strcmp(bidder, puja.bidder) == 0) {
                printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n", productId, bidder,
                       getCategoryName(prod.productCategory), puja.productPrice, prod.bidCounter);
                pop(&prod.bidStack);
                prod.bidCounter--;
                updateItem(prod, pos, lista);
                return true;
            }
        }
    }
    return false;
    }

bool weithdraw (tProductId productId, tUserId seller, tList* lista) {
	tPosL pos = findItem(productId, *lista);

	if (pos != LNULL) { /* Si el producto existe en la lista (TODO facer funcion para comprobar se está na lista un producto?)*/
		tItemL producto = getItem(pos, *lista);
		// Si la pila de pujas no est� vac�a y el nombre del vendedor coincide con el introducido,
		// se sigue la ejecuci�n
		if (!isEmptyStack(producto.bidStack) || (strcmp(producto.seller, seller) == 0)) {
			tItemS puja = peek(producto.bidStack); // Se obtiene la �ltima puja del producto

			// Se imprime la informaci�n de la operaci�n
			printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n", productId,
				   puja.bidder, getCategoryName(producto.productCategory), puja.productPrice,
				   producto.bidCounter);
			pop(&producto.bidStack); // Elimina la ultima puja
			producto.bidCounter--; // Decrementa el contador de pujas
			updateItem(producto, pos, lista);
			return true; // La ejecuci�n ha sido correcta, por lo que se devuelve verdadero
		}
	}
	return false; // No se ha cumplido al menos una de las tres condiciones, por lo que se devuelve falso
}

bool Remove (tList* lista) {
    tPosL pos;
    tItemL prod;
    int removedProducts = 0;

    for(pos = first(*lista); pos != LNULL; pos = next(pos, *lista)) {
        prod = getItem(pos, *lista);
        if(prod.bidCounter == 0) {
            printf("Removing product %s seller %s category %s price %.2f bids %d\n", prod.productId, prod.seller,
                   getCategoryName(prod.productCategory)s, prod.productPrice, prod.bidCounter);
            deleteAtPosition(pos, lista);
            removedProducts++;
        }
    }
    return removedProducts > 0;
}

bool Reemove (tList* lista) {
	tItemL producto;
	tPosL pos;
	bool productRemoved = false;

	// TODO: Solo borra un producto sin pujas, ten que borralos todos
	if(!isEmptyList(*lista)) {
		pos = first(*lista);
		while(pos != LNULL) { // Mientras la lista no est� vac�a
			producto = getItem(pos, *lista);

			if(producto.bidCounter == 0) { // Si el producto no tiene ninguna puja
				delete(producto.productId, false, lista); // Lo elimina de la lista
				// Y se imprime la informacion del proceso
				printf("Removing product %s seller %s category %s price %.2f bids %d\n",
					   producto.productId, producto.seller, getCategoryName(producto.productCategory),
					   producto.productPrice, producto.bidCounter);
				productRemoved = true;
				pos = first(*lista);
			} else {
				pos = next(pos, *lista);
			}
		}
	}
	return productRemoved;
}