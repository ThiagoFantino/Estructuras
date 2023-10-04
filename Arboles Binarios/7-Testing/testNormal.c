#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Nodo {
    int valor;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    return nuevo;
}

void insertar(Nodo** raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = crearNodo(valor);
        return;
    }

    if (valor < (*raiz)->valor) {
        insertar(&((*raiz)->izquierda), valor);
    } else {
        insertar(&((*raiz)->derecha), valor);
    }
}

int contarNodos(Nodo* nodo) {
    if (nodo == NULL) return 0;

    return 1 + contarNodos(nodo->izquierda) + contarNodos(nodo->derecha);
}

Nodo* buscar(Nodo* nodo, int valor) {
    if (nodo == NULL || nodo->valor == valor) {
        return nodo;
    }

    if (valor < nodo->valor) {
        return buscar(nodo->izquierda, valor);
    } else {
        return buscar(nodo->derecha, valor);
    }
}

int altura(Nodo* nodo) {
    if (nodo == NULL) return 0;

    int altIzq = altura(nodo->izquierda);
    int altDer = altura(nodo->derecha);

    return 1 + (altIzq > altDer ? altIzq : altDer);
}

void generarNumerosAleatorios(Nodo** raiz, int maxElementos) {
    srand(time(NULL));

    for (int i = 0; i < maxElementos; i++) {
        int valor = rand() % 1000; // Generamos números aleatorios entre 0 y 999
        insertar(raiz, valor);
    }
}

void guardarTiempoEnCSV(double tiempo) {
    FILE *fp = fopen("NormalTimes.csv", "a"); // "a" significa que se añadirá al archivo sin sobrescribir
    if (fp == NULL) {
        perror("Error al abrir el archivo");
        return;
    }
    fprintf(fp, "%f\n", tiempo);
    fclose(fp);
}

int main() {
    clock_t inicio, fin;
    double tiempo_ejecucion;

    Nodo* raiz = NULL;

    int numeroElementos = 1;
    int maxElementos = 1000000;
    inicio = clock();

    while (numeroElementos <= maxElementos) {
        ;  // Iniciamos la medición

        int valor = rand() % 1000; // Generamos números aleatorios entre 0 y 999
        insertar(&raiz, valor);
        numeroElementos++;

        if (numeroElementos % 10000 == 0) {
            
            Nodo* buscado2 = buscar(raiz, rand() % 1000 );

            fin = clock();  // Terminamos la medición
            tiempo_ejecucion = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
            guardarTiempoEnCSV(tiempo_ejecucion);
        }
    }
}
