class Nodo {
    constructor(valor) {
        this.valor = valor;
        this.link = null;  // XOR del hijo y hermano
    }
}

function XOR(a, b) {
    return a ^ b;
}

function crearNodo(valor) {
    return new Nodo(valor);
}

function agregarHijo(padre, hijo) {
    if (!padre.link) {
        padre.link = hijo;
    } else {
        let hermano = padre.link;
        padre.link = XOR(hermano, hijo);
        hijo.link = XOR(hijo.link, hermano);
    }
}

function contarNodos(nodo, prev = 0) {
    if (!nodo) return 0;

    let next = XOR(prev, nodo.link);

    return 1 + contarNodos(nodo.link, nodo) + contarNodos(next, nodo);
}

function altura(nodo, prev = 0) {
    if (!nodo) return 0;

    let next = XOR(prev, nodo.link);
    let h1 = 1 + altura(nodo.link, nodo);
    let h2 = 1 + altura(next, nodo);
    
    return Math.max(h1, h2);
}

// Prueba
let raiz = crearNodo(10);
let hijo1 = crearNodo(5);
let hijo2 = crearNodo(6);
let hijo3 = crearNodo(7);

agregarHijo(raiz, hijo1);
agregarHijo(hijo1, hijo2);
agregarHijo(hijo2, hijo3);

console.log(`Raíz: ${raiz.valor}`);
console.log(`Nodos totales: ${contarNodos(raiz)}`);
console.log(`Altura del árbol: ${altura(raiz)}`);
