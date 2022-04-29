/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Alejandro Barrera López 			 	LOGIN 1: alejandro.barrera
 * AUTHOR 2: Álvaro Dolz del Castellar Castiñeira 	LOGIN 2: a.dolzdelcastellar1
 * GROUP: 4.4
 * DATE: 29 / 04 / 22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product_list.h"

#define MAX_BUFFER 255

// Funciones principales del programa

/**
* Realiza la alta de un nuevo producto. Para ello, comprueba que sea valido y, si lo es,
* lo introduce en la lista de productos
* @param productId			ID del producto a dar de alta
* @param userId				ID del usuario que sube el producto
* @param productCategory	Categoría del nuevo producto
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
 * @param lista			Lista de productos
 * @post Antes de eliminar un producto, se deberá de vaciar su pila de pujas
 * @post Si existe un producto con el productId introducido, debe de quedar eliminado de la lista.
 * @return True si se ha realizado correctamente, false en caso contrario
 */
bool delete (tProductId productId, tList* lista);

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

/**
 * Imprime un mensaje de error para el comando introducido
 * @param command Carácter correspondiente al comando del error
 * @pre El carácter de comando es uno de los 7 indicados por el enunciado (N, D, B, A, W, R, S)
 */
void printError (char command) {
	char* commandName;
	switch (command) {
		case 'N': // New
			commandName = "New";      break;
		case 'D': // Delete
			commandName = "Delete";   break;
		case 'B': // Bid
			commandName = "Bid";      break;
		case 'A': // Award
			commandName = "Award";    break;
		case 'W': // Withdraw
			commandName = "Withdraw"; break;
		case 'R': // Remove
			commandName = "Remove";   break;
		case 'S': // Stats
			commandName = "Stats";    break;
		default:
			return;
	}
	printf("+ Error: %s not possible\n", commandName);
}

/* NOTA: Las siguientes dos funciones (deleteList y deleteStack) se han implementado a sabiendas fuera de
   product_list y bid_stack, respectivamente, para respetar la especificación proporcionada en el enunciado. */

/**
 * Borra la lista, libera la memoria ocupada y restablece su tamaño y posición a 0
 * @param lista Lista a borrar
 * @return La lista vacía, por parámetro
 */
void deleteList (tList* lista) {
    tPosL posicion; // Define una variable de tipo tPosL para almacenar una posición

    while(*lista != LNULL) { // Mientras la lista no sea igual a nulo, es decir, mientras no esté vacía
        // Se recorre cada elemento de la lista y se va liberando la memoria asignada a él
        posicion = *lista;
        *lista = (*lista)->siguiente;
        free(posicion);
    }
}

/**
 * Elimina el contenido de una pila
 * @param stack Pila a vaciar
 * @post La pila tiene que quedar vacía
 * @return Pila vaciada, por parámetro
 */
void deleteStack (tStack* pila) {
    // Mientras la pila no esté vacía, borra el elemento cima
    while(!isEmptyStack(*pila)) {
        pop(pila);
    }
}

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
			ok = delete(param1, lista);
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
	if(!ok) { // En caso de error en la ejecución, lo imprime
		printError(command);
	}
}

/**
 * Lee las órdenes del programa desde un archivo de texto
 * @param filename Nombre del archivo por el que se leerán las órdenes
 */
void readTasks(char *filename) {
	tList lista; // Define la lista
	createEmptyList(&lista); // Inicializa la lista vacía

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

/**
 * Devuelve un string con el nombre del valor del enum introducido
 * @param productCategory enum introducido
 * @return Nombre correspondiente al valor del enum introducido
 */
char* getCategoryName (tProductCategory productCategory) {
	if(productCategory == book) { // Si la categoría es libro, devuelve un string "book"
		return "book";
	} else { // Sino, devuelve "painting"
		return "painting";
	}
}

/**
 * Calcula la media aritmética mediante dos parámetros
 * @param suma 	Suma de los números a realizar la media
 * @param n 	Cantidad de números
 * @return Media aritmética
 */
float calcularMedia (float suma, unsigned int n){
	// Para evitar una división entre 0, comprueba si 'n' es distinto a 0
	if(n == 0) { // En dicho caso, devuelve 0
		return 0;
	} else { // Si no, devuelve la media aritmética correspondiente
		return suma/(float)n;
	}
}

bool new(tProductId productId, tUserId userId, tProductCategory productCategory,
         tProductPrice productPrice, tList* lista) {
    // Se define una variable 'prod' del tipo tItemL, para almacenar la información del producto a insertar
    tItemL prod;
    // Se copian los datos del producto a insertar en la variable 'prod'
    strcpy(prod.productId, productId);
    strcpy(prod.seller, userId);
    prod.productCategory = productCategory;
    prod.productPrice = productPrice;
    // Se inicializa el contador de pujas a 0, y se crea una pila de pujas para el producto
    prod.bidCounter = 0;
    createEmptyStack(&prod.bidStack);

    // Si el producto a insertar no existe en la lista de pujas, y se inserta correctamente
    if(findItem(productId, *lista) == LNULL && insertItem(prod, lista)) {
        // Se imprimen los datos de la inserción, y se devuelve verdadero porque la ejecución fue correcta
        printf("* New: product %s seller %s category %s price %.2f\n",
               productId, userId, getCategoryName(prod.productCategory), productPrice);
        return true;
    }
    // No se cumplieron las condiciones para el new, se devuelve falso
    return false;
}

bool delete(tProductId productId, tList* lista) {
    // Se crea una variable 'prod' para almacenar el producto a borrar,
    // y otra 'pos' para almacenar su posición en la lista de productos
    tPosL pos;
    tItemL prod;
    // Si el producto existe en la lista
    if((pos = findItem(productId, *lista)) != LNULL) {
        // Se dá valor a la variable 'prod' con los datos del producto
        prod = getItem(pos, *lista);
        // Se vacía la pila de pujas del producto (en caso de ya estar vacía no hace nada), y se borra el producto
        // de la lista de productos. Finalmente, se imprime un mensaje informativo y se devuelve verdadero
        deleteStack(&prod.bidStack);
        deleteAtPosition(pos, lista);
        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", prod.productId, prod.seller,
               getCategoryName(prod.productCategory), prod.productPrice, prod.bidCounter);
        return true;
    }
    // El producto no se pudo eliminar, se devuelve falso
    return false;
}

bool bid(tProductId productId, tUserId bidder, tProductPrice precioPuja, tList* lista) {
    // Se define una variable 'prod' para almacenar el producto al que pujar,
    // y otra 'pos' para almacenar su posición en la lista de productos
    tPosL pos;
    tItemL prod;
    // Se define una variable 'puja' para posteriormente almacenar los datos de una puja
    tItemS puja;
    tProductPrice anteriorPrecio;

    // Si el producto existe en la lista, y el vendedor no tiene el mismo tUserId que el pujador
    if((pos = findItem(productId, *lista)) != LNULL && strcmp((prod = getItem(pos, *lista)).seller, bidder) != 0) {
        // Si el producto no tiene pujas, el anterior precio será su productPrice.
        if(prod.bidCounter == 0) {
            anteriorPrecio = prod.productPrice;
        } else {
            // Si tiene pujas, el anterior precio a evaluar será la anterior puja (y, por lo tanto, la más alta)
            anteriorPrecio = peek(prod.bidStack).productPrice;
        }
        // Si el precio de la nueva puja supera al anterior precio establecido
        if(precioPuja > anteriorPrecio) {
            // Se copian en 'puja' los datos de la nueva puja
            strcpy(puja.bidder, bidder);
            puja.productPrice = precioPuja;
            // Si la puja es insertada correctamente en la pila
            if(push(puja, &prod.bidStack)) {
                // Se incrementa el contador de pujas, y se actualiza el producto en la lista con los nuevos datos
                prod.bidCounter++;
                updateItem(prod ,pos, lista);
                // Imprime un mensaje informativo y devuelve verdadero
                printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n", prod.productId, bidder,
                       getCategoryName(prod.productCategory), precioPuja, prod.bidCounter);
                return true;
            }
        }
    }
    // No se ha realizado la puja, se devuelve falso
    return false;
}

/**
 * Imprime por pantalla la información del producto introducido
 * @param item Producto a imprimir
 * @pre El producto no es nulo
 */
void imprimirInfoProducto (tItemL prod) { // Imprime la información del producto 'item'
    printf("Product %s seller %s category %s price %.2f", prod.productId,
           prod.seller, getCategoryName(prod.productCategory), prod.productPrice);
    if(prod.bidCounter == 0) {
        printf(". No bids\n");
    } else {
        printf(" bids %d top bidder %s\n", prod.bidCounter, peek(prod.bidStack).bidder);
    }

}

/**
 * imprime por pantalla una tabla con las estadísticas de los productos en subasta
 * @param contador      El número de elementos de cada categoría
 * @param sumaPrecios   La suma de todos los precios de los elementos de cada categoría
 */
void imprimirEstadisticas (unsigned int contador[2], float sumaPrecios[2]) {
	printf("\nCategory  Products    Price  Average\n"); // Cabecera
	printf("Book      %8d %8.2f %8.2f\n", // Imprime las estadísticas de los libros
		   contador[0], sumaPrecios[0], calcularMedia(sumaPrecios[0], contador[0]));
	printf("Painting  %8d %8.2f %8.2f\n", // Imprime las estadísticas de los cuadros de pintura
		   contador[1], sumaPrecios[1], calcularMedia(sumaPrecios[1], contador[1]));
}

/**
 * Devuelve el incremento de la última puja de un producto en relación a su precio original
 * @param producto Producto a evaluar
 * @return El incremento porcentual de la mayor puja con respecto al precio de salida
 */
float incremento (tItemL producto) {
    if(producto.bidCounter == 0)
        return 0;
    tItemS puja = peek(producto.bidStack);
    return (puja.productPrice - producto.productPrice) / producto.productPrice * 100;
}

/**
 * Imprime la información de la puja
 * @param producto Producto del cual imprimir información
 * @pre La puja introducida es la mayor puja de la lista, o en caso de no haber, un placeholder con bidCounter = 0
 */
void imprimirTopBid (tItemL producto) {
    // Si la puja no es la mayor (es un placeholder con bidCounter = 0), se imprime que no hay top bid
	if(producto.bidCounter == 0) {
		printf("Top bid not possible\n");
	// Si es la mayor puja, se
    } else {
        // Se obtienen los datos de la última puja
		tItemS puja = peek(producto.bidStack);
		float precioPuja = puja.productPrice;
		float precioProducto = producto.productPrice;
        // Se imprime la información sobre el producto y su última puja
		printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
			   producto.productId, producto.seller, getCategoryName(producto.productCategory),
			   precioProducto, puja.bidder, precioPuja, incremento(producto));
	}
}

bool stats(tList* lista) {
    // Se define una variable 'prod' para posteriormente almacenar un producto tItemL,
    // y otra 'pos' para almacenar su posición en la lista de productos
    tPosL pos;
    tItemL prod;
    float totalPrecios[2] = {0, 0}; // Posición 0 -> book. Posición 1 -> painting
    unsigned int numProductos[2] = {0, 0}; // Posición 0 -> book. Posición 1 -> painting
    /* Se crea un tItemL para almacenar la mayor puja, y se inicializa su contador de pujas a 0 para que actúe
       de placeholder en caso de no haber pujas */
    tItemL topBid;
    topBid.bidCounter = 0;
    // Si la lista no está vacía
    if(!isEmptyList(*lista)) {
        // Se recorre la lista producto a producto
        for(pos = first(*lista); pos != LNULL; pos = next(pos, *lista)) {
            prod = getItem(pos, *lista);
            // Se suma el precio del actual producto en la posición del array correspondiente a su categoría
            totalPrecios[prod.productCategory] += prod.productPrice;
            // Se incrementa el contador del actual producto en su posición correspondiente
            numProductos[prod.productCategory]++;
            // Si el producto tiene pujas y su incremento es mayor, pasa a ser el topBid
            if(prod.bidCounter > 0 && incremento(prod) > incremento(topBid)) {
                topBid = prod;
            }
            // Se imprime la información del producto
            imprimirInfoProducto(prod);
        }
        // Se imprimen las estadísticas generales y la información sobre el top bid, y se devuelve verdadero
        imprimirEstadisticas(numProductos, totalPrecios);
        imprimirTopBid(topBid);
        return true;
    }
    // La lista estaba vacía, por lo que no se pudo mostrar ningún producto y se devuelve falso
    return false;
}

bool award (tProductId productId, tList* lista) {
    tPosL pos;      // Almacenará la posición del producto al que evaluar
    tItemL prod;    // Almacenará el producto al que evaluar
    tItemS pujaMax; // Almacenará la puja premiada

    // Si el producto existe en la lista
    if((pos = findItem(productId, *lista)) != LNULL) {
        // 'prod' toma el valor del producto
        prod = getItem(pos, *lista);
        // Si el producto tiene al menos una puja, se selecciona la puja máxima y se imprime su información
        if(!isEmptyStack(prod.bidStack)) {
            pujaMax = peek(prod.bidStack);
            printf("* Award: product %s bidder %s category %s price %.2f\n", productId, pujaMax.bidder,
                   getCategoryName(prod.productCategory), pujaMax.productPrice);
            deleteAtPosition(pos, lista);
            // Devuelve verdadero
            return true;
        }
    }
    // Si el producto introducido no se pudo premiar, se devuelve falso
    return false;
}

bool withdraw (tProductId productId, tUserId bidder, tList* lista) {
    tPosL pos;   // Almacenará la posición del producto al que evaluar
    tItemL prod; // Almacenará el producto al que evaluar
    tItemS puja; // Almacenará la puja a eliminar

    // Si el producto existe en la lista, 'prod' toma su valor
    if((pos = findItem(productId, *lista)) != LNULL) {
        prod = getItem(pos, *lista);
        // Si el producto tiene al menos una puja, 'puja' toma el valor de la puja máxima (la última)
        if(prod.bidCounter > 0) {
            puja = peek(prod.bidStack);
            // Si el nombre del último pujador y del nombre introducido en la función coinciden
            if(strcmp(bidder, puja.bidder) == 0) {
                // Se imprime un mensaje informativo
                printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n", productId, bidder,
                       getCategoryName(prod.productCategory), puja.productPrice, prod.bidCounter);
                // Se elimina la última puja, se decrementa el contador de pujas del producto
                pop(&prod.bidStack);
                prod.bidCounter--;
                // Y se actualiza el producto en la lista
                updateItem(prod, pos, lista);
                // Finalmente, se devuelve verdadero
                return true;
            }
        }
    }
    // Si no se pudo evaluar la puja, se devuelve falso
    return false;
}

bool Remove (tList* lista) {
    // Se define una variable 'prod' para posteriormente almacenar un producto,
    // y otra 'pos' para almacenar su posición en la lista de productos
    tPosL pos;
    tItemL prod;
    // Se definen dos variables booleanas
    bool isLastPos;
    bool productRemoved = false;

    if(!isEmptyList(*lista)) {
        // Recorre la lista desde la primera posición hasta la última (teniendo en cuenta que,
        // si se elimina una posición, la siguiente cambia
        for(pos = first(*lista); !isEmptyList(*lista) && !isLastPos;) {
            // Guarda en 'isLastProd' si la actual posición evaluada es la última en la lista
            isLastPos = (pos == last(*lista));
            prod = getItem(pos, *lista);
            // Si el producto no tiene pujas
            if(prod.bidCounter == 0) {
                // Guarda en 'productRemoved' que se eliminó al menos un producto, y se imprime un mensaje informativo
                productRemoved = true;
                printf("Removing product %s seller %s category %s price %.2f bids %d\n", prod.productId, prod.seller,
                       getCategoryName(prod.productCategory), prod.productPrice, prod.bidCounter);
                // Si el elemento ocupa la primera posición
                if(pos == first(*lista)) {
                    // Se pasa a la siguiente posición después de borrarlo de la lista
                    deleteStack(&prod.bidStack);
                    deleteAtPosition(pos, lista);
                    pos = next(pos, *lista);
                } else {
                    // Si no, solo lo elimina de la lista
                    deleteStack(&prod.bidStack);
                    deleteAtPosition(pos, lista);
                }
            } else {
                // El producto tiene pujas, por lo que no se elimina y se pasa a la siguiente posición de la lista
                pos = next(pos, *lista);
            }
        }
    }
    // Devuelve true si se ha eliminado al menos un producto, y false en caso contrario
    return productRemoved;
}