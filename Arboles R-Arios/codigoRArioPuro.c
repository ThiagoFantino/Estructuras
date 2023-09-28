#include <stdio.h>
#include <stdlib.h>

#define R 3  // Suponiendo un árbol 3-ario como ejemplo

typedef struct Nodo {
    int valor;
    struct Nodo* xor_parent_children;  // Padre XOR Arreglo de hijos
    struct Nodo** children;            // Arreglo directo de hijos
} Nodo;

Nodo* XOR(Nodo* a, Nodo** b) {
    return (Nodo*)((size_t)a ^ (size_t)b);
}

Nodo* crearNodo(int valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->xor_parent_children = NULL;
    nuevo->children = (Nodo**)malloc(R * sizeof(Nodo*));
    for (int i = 0; i < R; i++) {
        nuevo->children[i] = NULL;
    }
    return nuevo;
}

void agregarHijo(Nodo* padre, Nodo* hijo, int pos) {
    if (pos >= R || padre->children[pos]) {
        printf("Posición no válida o ya ocupada.\n");
        return;
    }
    padre->children[pos] = hijo;
    hijo->xor_parent_children = XOR(padre, hijo->children);
}

Nodo* obtenerPadre(Nodo* nodo) {
    return XOR(nodo->xor_parent_children, nodo->children);
}

Nodo* buscar(Nodo* nodo, int valor) {
    if (!nodo) return NULL;
    if (nodo->valor == valor) return nodo;

    Nodo* encontrado = NULL;
    for (int i = 0; i < R && !encontrado; i++) {
        encontrado = buscar(nodo->children[i], valor);
    }
    return encontrado;
}

int contarNodos(Nodo* nodo) {
    if (!nodo) return 0;

    int count = 1;
    for (int i = 0; i < R; i++) {
        count += contarNodos(nodo->children[i]);
    }
    return count;
}

// La función altura para un árbol r-ario sería más compleja que en el binario, pero 
// aquí hay una versión simplificada:

int altura(Nodo* nodo) {
    if (!nodo) return 0;

    int maxAltura = 0;
    for (int i = 0; i < R; i++) {
        int altActual = altura(nodo->children[i]);
        if (altActual > maxAltura) {
            maxAltura = altActual;
        }
    }
    return 1 + maxAltura;
}

int main() {
    Nodo* raiz = crearNodo(10);
    Nodo* hijo1 = crearNodo(5);
    Nodo* hijo2 = crearNodo(6);
    Nodo* hijo3 = crearNodo(7);

    agregarHijo(raiz, hijo1, 0);
    agregarHijo(raiz, hijo2, 1);
    agregarHijo(raiz, hijo3, 2);

    printf("Nodos totales: %d\n", contarNodos(raiz));
    
    Nodo* buscado = buscar(raiz, 6);
    if (buscado) {
        printf("Nodo encontrado con valor: %d\n", buscado->valor);
    } else {
        printf("Nodo no encontrado.\n");
    }

    printf("Altura del arbol: %d\n", altura(raiz));

    return 0;
}
