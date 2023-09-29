#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* xor_left_parent;  // Padre XOR Hijo Izquierdo
    struct Nodo* xor_right_parent; // Padre XOR Hijo Derecho
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

void agregarHijo(Nodo* padre, Nodo* hijo, int esDerecho) {
    if (esDerecho) {
        hijo->xor_right_parent = padre;
        padre->xor_right_parent = XOR(hijo, padre->xor_right_parent);
    } else {
        hijo->xor_left_parent = padre;
        padre->xor_left_parent = XOR(hijo, padre->xor_left_parent);
    }
}

Nodo* obtenerHijoIzquierdo(Nodo* nodo, Nodo* padre) {
    return XOR(nodo->xor_left_parent, padre);
}

Nodo* obtenerHijoDerecho(Nodo* nodo, Nodo* padre) {
    return XOR(nodo->xor_right_parent, padre);
}

int contarNodos(Nodo* nodo, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo) return 0;

    int count = 1;
    count += contarNodos(obtenerHijoIzquierdo(nodo, prevLeft), nodo, NULL);
    count += contarNodos(obtenerHijoDerecho(nodo, prevRight), NULL, nodo);

    return count;
}

Nodo* buscar(Nodo* nodo, int valor, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo || nodo->valor == valor) return nodo;

    Nodo* encontrado = buscar(obtenerHijoIzquierdo(nodo, prevLeft), valor, nodo, NULL);
    if (!encontrado) encontrado = buscar(obtenerHijoDerecho(nodo, prevRight), valor, NULL, nodo);

    return encontrado;
}

int altura(Nodo* nodo, Nodo* prevLeft, Nodo* prevRight) {
    if (!nodo) return 0;

    int altIzq = altura(obtenerHijoIzquierdo(nodo, prevLeft), nodo, NULL);
    int altDer = altura(obtenerHijoDerecho(nodo, prevRight), NULL, nodo);

    return 1 + (altIzq > altDer ? altIzq : altDer);
}

int main() {
    Nodo* raiz = crearNodo(10);
    Nodo* hijo1 = crearNodo(5);
    Nodo* hijo2 = crearNodo(6);

    agregarHijo(raiz, hijo1, 0);  // Hijo izquierdo
    agregarHijo(raiz, hijo2, 1);  // Hijo derecho

    printf("Nodos totales: %d\n", contarNodos(raiz, NULL, NULL));

    Nodo* buscado = buscar(raiz, 5, NULL, NULL);
    if (buscado) {
        printf("Nodo encontrado con valor: %d\n", buscado->valor);
    } else {
        printf("Nodo no encontrado.\n");
    }

    printf("Altura del arbol: %d\n", altura(raiz, NULL, NULL));

    return 0;
}
