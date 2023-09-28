#include <stdio.h>
#include <stdlib.h>
/*

Codigo de un árbol usando el algoritmo de Siklossy . Incluye:
-Inserción de nodos: AgregarHijo
-Búsqueda: buscar
-Dar la cantidad de nodos: contarNodos
-Altura: altura

*/

typedef struct Nodo {
    int valor;
    struct Nodo* xor_link;          
    struct Nodo* siguienteHijo;     
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
        padre->xor_link = hijo; // Si el padre no tiene hijos, este es el hijo izquierdo
    } else if (!padre->siguienteHijo) {
        padre->siguienteHijo = hijo; // Si ya tiene un hijo izquierdo, este es el hijo derecho
    } else {
        // El nodo padre ya tiene dos hijos
        printf("El nodo ya tiene dos hijos.\n");
        return;
    }
    hijo->xor_link = XOR(padre, NULL); // El hijo apunta solo al padre por ahora
}

int contarNodos(Nodo* nodo, Nodo* prev) {
    if (!nodo) return 0;

    int count = 1; // Por el nodo actual

    // Contar nodos en el subárbol del hijo derecho.
    count += contarNodos(nodo->siguienteHijo, nodo);

    // Usar el enlace XOR para obtener el hijo izquierdo.
    Nodo* hijoIzq = XOR(prev, nodo->xor_link);
    
    // Contar nodos en el subárbol del hijo izquierdo.
    count += contarNodos(hijoIzq, nodo);

    return count;
}

Nodo* buscar(Nodo* nodo, int valor, Nodo* prev) {
    if (!nodo) return NULL;
    if (nodo->valor == valor) return nodo;

    Nodo* hijoIzq = XOR(prev, nodo->xor_link);
    Nodo* resultado = buscar(hijoIzq, valor, nodo); // Buscar en el hijo izquierdo

    if (resultado) return resultado;

    return buscar(nodo->siguienteHijo, valor, nodo); // Buscar en el hijo derecho
}

int altura(Nodo* nodo, Nodo* prev) {
    if (!nodo) return 0;

    Nodo* hijoIzq = XOR(prev, nodo->xor_link);
    int altIzq = altura(hijoIzq, nodo);
    int altDer = altura(nodo->siguienteHijo, nodo);

    return 1 + (altIzq > altDer ? altIzq : altDer);
}

int main() {
    Nodo* raiz = crearNodo(10);
    Nodo* hijo1 = crearNodo(5);
    Nodo* hijo2 = crearNodo(6);
    Nodo* hijo3 = crearNodo(7);

    agregarHijo(raiz, hijo1);
    agregarHijo(raiz, hijo2);
    agregarHijo(hijo1, hijo3);

    printf("Raiz: %d\n", raiz->valor);
    printf("Nodos totales: %d\n", contarNodos(raiz, NULL));
    
    Nodo* buscado = buscar(raiz, 6, NULL);
    if (buscado) {
        printf("Nodo encontrado con valor: %d\n", buscado->valor);
    } else {
        printf("Nodo no encontrado.\n");
    }

    printf("Altura del arbol: %d\n", altura(raiz, NULL));

    return 0;
}
