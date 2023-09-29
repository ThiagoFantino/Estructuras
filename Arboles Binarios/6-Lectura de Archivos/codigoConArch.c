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

int main() {
    Nodo* raiz = NULL;

    cargarDatosDesdeArchivo(&raiz);

    printf("Nodos totales: %d\n", contarNodos(raiz, NULL, NULL));

    Nodo* buscado = buscar(raiz, 5, NULL, NULL);
    if (buscado) {
        printf("Nodo encontrado con valor: %d\n", buscado->valor);
    } else {
        printf("Nodo no encontrado.\n");
    }

    printf("Altura del Arbol: %d\n", altura(raiz, NULL, NULL));

    return 0;
}
