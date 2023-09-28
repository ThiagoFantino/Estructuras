#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* xor_link;
    struct Nodo* siguienteHijo;  // Usado para hijos adicionales en la lista ligada.
} Nodo;

Nodo* XOR(Nodo* a, Nodo* b) {
    return (Nodo*)((size_t)a ^ (size_t)b);
}

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->xor_link = NULL;
    nuevo->siguienteHijo = NULL;
    return nuevo;
}

void agregarHijo(Nodo* padre, Nodo* hijo) {
    if (!padre->xor_link) {
        padre->xor_link = hijo;
    } else {
        Nodo* primerHijo = padre->xor_link;
        while (primerHijo->siguienteHijo) {
            primerHijo = primerHijo->siguienteHijo;
        }
        primerHijo->siguienteHijo = hijo;
        hijo->xor_link = XOR(hijo->xor_link, padre);  // Apunta al padre.
    }
}

void imprimirHijos(Nodo* padre) {
    Nodo* hijoActual = padre->xor_link;
    while (hijoActual) {
        printf("Hijo: %d\n", hijoActual->valor);
        hijoActual = hijoActual->siguienteHijo;
    }
}

int main() {
    Nodo* raiz = crearNodo(10);
    Nodo* hijo1 = crearNodo(5);
    Nodo* hijo2 = crearNodo(6);
    Nodo* hijo3 = crearNodo(7);

    agregarHijo(raiz, hijo1);
    agregarHijo(raiz, hijo2);
    agregarHijo(raiz, hijo3);

    printf("Raíz: %d\n", raiz->valor);
    imprimirHijos(raiz);

    return 0;
}







