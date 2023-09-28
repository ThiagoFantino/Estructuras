#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int valor;
    struct Nodo* xor_link;   // Apunta al nodo anterior XOR nodo siguiente
} Nodo;

Nodo* XOR(Nodo* a, Nodo* b) {
    return (Nodo*)((size_t)a ^ (size_t)b);
}

Nodo* insertar(Nodo* cabeza, int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->xor_link = XOR(cabeza, NULL);

    if (cabeza != NULL) {
        Nodo* siguiente = XOR(cabeza->xor_link, NULL);
        cabeza->xor_link = XOR(nuevo, siguiente);
    }

    return nuevo; // Retorna el nuevo nodo que es ahora la nueva cabeza
}

void imprimirLista(Nodo* cabeza) {
    Nodo* prev = NULL;
    Nodo* actual = cabeza;
    
    while (actual) {
        printf("%d ", actual->valor);
        Nodo* siguiente = XOR(prev, actual->xor_link);
        prev = actual;
        actual = siguiente;
    }
    printf("\n");
}

int main() {
    Nodo* lista = NULL;  // Inicialmente, la lista está vacía
    lista = insertar(lista, 1);
    lista = insertar(lista, 2);
    lista = insertar(lista, 3);

    imprimirLista(lista);

    return 0;
}
