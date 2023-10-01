#include <stdio.h>
#include <stdlib.h>

/************************************************************************************
 * CodigoConArchOp.c
 * Tf, Kypers, Martu, Mate
 * 
 * Este programa crea y busca valores en un arbol binario con enlaces mediante las 
 * vinculaciones de Siklossy (De Morgan). Adicionalmente cuenta los nodos y la
 * altura del arbol en cuestion.
 * 
************************************************************************************/

// Estuctura del nodo
typedef struct Nodo {
    int valor;
    struct Nodo* xor_left_parent;  // Padre XOR Hijo Izquierdo
    struct Nodo* xor_right_parent; // Padre XOR Hijo Derecho
} Nodo;

//*********************************************************************************//

//Syntaxis de Siklossy mediante XOR
Nodo* XOR(Nodo* a, Nodo* b) {
    return (Nodo*)((size_t)a ^ (size_t)b); // A xor B , operaciona nivel bit
}

//*********************************************************************************//

//Creacion de nodo, asigna memoria, carga el valor y los punteros a hijos en NULL
Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->xor_left_parent = NULL;
    nuevo->xor_right_parent = NULL;
    return nuevo; //Retorna el puntero al nodo
}

//*********************************************************************************//

//Puente para obtener el hijo izq. Manda el puntero a izq y del padre
Nodo* obtenerHijoIzquierdo(Nodo* nodo, Nodo* padre) {
    //Retorna el puntero al valor del hijo
    return XOR(nodo->xor_left_parent, padre);
}

//*********************************************************************************//

//Puente para obtener el hijo der. Manda el puntero a der y del padre
Nodo* obtenerHijoDerecho(Nodo* nodo, Nodo* padre) {
    //Retorna el puntero al valor del hijo
    return XOR(nodo->xor_right_parent, padre); 
}

//*********************************************************************************//

//Insercion de nodo en arbol mediante 
void insertar(Nodo** nodo, Nodo* prevLeft, Nodo* prevRight, int valor) {
    
    //Si Nodo == NULL -> Creo nodo
    if (!(*nodo)) {
        *nodo = crearNodo(valor);
        (*nodo)->xor_left_parent = prevLeft;
        (*nodo)->xor_right_parent = prevRight;
        return;
    }

    //Si el valor del nodo es menor
    if (valor < (*nodo)->valor) {
        //Obtengo el puntero al hijo izquierdo
        Nodo* leftChild = obtenerHijoIzquierdo(*nodo, prevLeft);

        //Me muevo al hijo izquiedo
        insertar(&leftChild, *nodo, NULL, valor);

        //Pongo el puntero que apunte al hijo izq
        (*nodo)->xor_left_parent = XOR(prevLeft, leftChild);
    } 

    //Si el el valor del nodo es mayor
    else {
        //Obtengo el puntero al hijo derecho
        Nodo* rightChild = obtenerHijoDerecho(*nodo, prevRight);

        //Me muevo al hijo derecho
        insertar(&rightChild, NULL, *nodo, valor);

        //Pongo el puntero que apunte al hijo derecho
        (*nodo)->xor_right_parent = XOR(prevRight, rightChild);
    }
}

//*********************************************************************************//

// Extraccion de numeros de archivo
void cargarDatosDesdeArchivo(Nodo** raiz) {
    FILE* archivo = fopen("datos.txt", "r");

    //En caso de no encontrar archivo, display error
    if (!archivo) { 
        perror("No se pudo abrir el archivo");
        return;
    }

    //while que rescata los contenidos de un archivo y los inserta en un arbol
    int valor;
    while (fscanf(archivo, "%d", &valor) == 1) {
        insertar(raiz, NULL, NULL, valor);
    }

    fclose(archivo);
}

//*********************************************************************************//

//Buscar por valor, 
Nodo* buscar(Nodo* nodo, int valor, Nodo* prevLeft, Nodo* prevRight) {
    //En caso nulo, retorna NULL
    if (!nodo) return NULL;

    //Cuando encuentra el nodo con el valor, retorna su puntero
    if (nodo->valor == valor) return nodo;

    // Si el valor es menor busca en el hijo izquierdo mediante el metodo de Siklossy
    if (valor < nodo->valor){
        return buscar(obtenerHijoIzquierdo(nodo, prevLeft), valor, nodo, NULL);
    }
    else{
        return buscar(obtenerHijoDerecho(nodo, prevRight), valor, NULL, nodo);
    }
}

//*********************************************************************************//

//Funcion cuenta nodos, el nodo suma uno a sumatoria hasta encontrar nodo hoja
int contarNodos(Nodo* nodo, Nodo* prevLeft, Nodo* prevRight) {
    //Si nodo == NULL, retorna suma 0
    if (!nodo) return 0;

    //por recursividad va sumando a count hasta llegar a totalidad de nodos en arbol
    int count = 1;
    count += contarNodos(obtenerHijoIzquierdo(nodo, prevLeft), nodo, NULL);
    count += contarNodos(obtenerHijoDerecho(nodo, prevRight), NULL, nodo);

    return count;
}

//*********************************************************************************//

//Busca la altura de los subarboles adyacentes
int altura(Nodo* nodo, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo) return 0;

    //Busco alturas de ambos subarboles
    int altIzq = altura(obtenerHijoIzquierdo(nodo, prevLeft), nodo, NULL);
    int altDer = altura(obtenerHijoDerecho(nodo, prevRight), NULL, nodo);
    
    //Sentencia if comprimida: Si altIzq > altDer retorna altIzq, caso contratio retorna
    //altDer
    return 1 + (altIzq > altDer ? altIzq : altDer);
}

//*********************************************************************************//


//Main importa archivo
int main() {
    //Nodo root
    Nodo* raiz = NULL;

    //Carga de datos
    cargarDatosDesdeArchivo(&raiz); 

    //Contador de nodos
    printf("Nodos totales: %d\n", contarNodos(raiz, NULL, NULL));

    //Buscar nodo por valor mas un condicional
    Nodo* buscado = buscar(raiz, 5, NULL, NULL);
    if (buscado) {
        printf("Nodo encontrado con valor: %d\n", buscado->valor);
    } else {
        printf("Nodo no encontrado.\n");
    }

    //Contador de niveles
    printf("Altura del Arbol: %d\n", altura(raiz, NULL, NULL));

    return 0;
}

