#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Incluimos time.h para usar clock()

typedef struct Nodo {
    int valor;
    struct Nodo* xor_left_parent; 
    struct Nodo* xor_right_parent;
} Nodo;

Nodo* XOR(Nodo* a, Nodo* b) {
    return (Nodo*)((size_t)a ^ (size_t)b);
}

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->xor_left_parent = NULL;
    nuevo->xor_right_parent = NULL;
    return nuevo;
}

Nodo* obtenerHijoIzquierdo(Nodo* nodo, Nodo* padre) {
    return XOR(nodo->xor_left_parent, padre);
}

Nodo* obtenerHijoDerecho(Nodo* nodo, Nodo* padre) {
    return XOR(nodo->xor_right_parent, padre);
}

void insertar(Nodo** nodo, Nodo* prevLeft, Nodo* prevRight, int valor) {
    if (!(*nodo)) {
        *nodo = crearNodo(valor);
        (*nodo)->xor_left_parent = prevLeft;
        (*nodo)->xor_right_parent = prevRight;
        return;
    }

    if (valor < (*nodo)->valor) {
        Nodo* leftChild = obtenerHijoIzquierdo(*nodo, prevLeft);
        insertar(&leftChild, *nodo, NULL, valor);
        (*nodo)->xor_left_parent = XOR(prevLeft, leftChild);
    } else {
        Nodo* rightChild = obtenerHijoDerecho(*nodo, prevRight);
        insertar(&rightChild, NULL, *nodo, valor);
        (*nodo)->xor_right_parent = XOR(prevRight, rightChild);
    }
}

int contarNodos(Nodo* nodo, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo) return 0;

    int count = 1;
    count += contarNodos(obtenerHijoIzquierdo(nodo, prevLeft), nodo, NULL);
    count += contarNodos(obtenerHijoDerecho(nodo, prevRight), NULL, nodo);

    return count;
}

Nodo* buscar(Nodo* nodo, int valor, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo) return NULL;

    if (nodo->valor == valor) return nodo;

    if (valor < nodo->valor)
        return buscar(obtenerHijoIzquierdo(nodo, prevLeft), valor, nodo, NULL);
    else
        return buscar(obtenerHijoDerecho(nodo, prevRight), valor, NULL, nodo);
}

int altura(Nodo* nodo, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo) return 0;

    int altIzq = altura(obtenerHijoIzquierdo(nodo, prevLeft), nodo, NULL);
    int altDer = altura(obtenerHijoDerecho(nodo, prevRight), NULL, nodo);

    return 1 + (altIzq > altDer ? altIzq : altDer);
}

void cargarDatosDesdeArchivo(Nodo** raiz) {
    FILE* archivo = fopen("datos.txt", "r");
    if (!archivo) {
        perror("No se pudo abrir el archivo");
        return;
    }

    int valor;
    while (fscanf(archivo, "%d", &valor) == 1) {
        insertar(raiz, NULL, NULL, valor);
    }

    fclose(archivo);
}

void guardarTiempoEnCSV(double tiempo) {
    FILE *fp = fopen("tiempos_ejecucion.csv", "a"); // "a" significa que se añadirá al archivo sin sobrescribir
    if (fp == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    fprintf(fp, "%f\n", tiempo);
    fclose(fp);
}

int main() {
    clock_t inicio, fin;  // Declaramos las variables para medir el tiempo
    double tiempo_ejecucion;

    inicio = clock();  // Iniciamos la medición

    Nodo* raiz = NULL;

    int numeroElementos = 1;
    int maxElementos = 100000;
    inicio = clock();

    while (numeroElementos <= maxElementos) {
        ;  // Iniciamos la medición

        int valor = rand() % 1000; // Generamos números aleatorios entre 0 y 999
        insertar(&raiz, NULL, NULL, valor);
        numeroElementos++;

        if (numeroElementos % 10000 == 0) {
            
            Nodo* buscado2 = buscar(raiz, rand() % 1000 , NULL, NULL);

            // fin = clock();  // Terminamos la medición
            // tiempo_ejecucion = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            // guardarTiempoEnCSV(tiempo_ejecucion);

        }
    return 0;
}
