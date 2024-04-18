#include <iostream>
#include <queue>
using namespace std;


struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int valor) {
        dato = valor;
        izquierda = NULL;
        derecha = NULL;
    }
};

Nodo* insertarNodo(Nodo* raiz, int valor) {
    if (raiz == NULL) {
        return new Nodo(valor);
    } else {
        if (valor < raiz->dato)
            raiz->izquierda = insertarNodo(raiz->izquierda, valor);
        else
            raiz->derecha = insertarNodo(raiz->derecha, valor);
    }
    return raiz;
}

// Función para recorrido preorden
void preOrden(Nodo* raiz) {
    if (raiz == NULL)
        return;

    cout << raiz->dato << " ";
    preOrden(raiz->izquierda);
    preOrden(raiz->derecha);
}

// Función para recorrido inorden
void inOrden(Nodo* raiz) {
    if (raiz == NULL)
        return;

    inOrden(raiz->izquierda);
    cout << raiz->dato << " ";
    inOrden(raiz->derecha);
}

// Función para recorrido posorden
void posOrden(Nodo* raiz) {
    if (raiz == NULL)
        return;

    posOrden(raiz->izquierda);
    posOrden(raiz->derecha);
    cout << raiz->dato << " ";
}

// Función para recorrido por anchura (nivel por nivel)
void anchura(Nodo* raiz) {
    if (raiz == NULL)
        return;

    queue<Nodo*> cola;
    cola.push(raiz);

    while (!cola.empty()) {
        Nodo* nodoActual = cola.front();
        cola.pop();
        cout << nodoActual->dato << " ";

        if (nodoActual->izquierda != NULL)
            cola.push(nodoActual->izquierda);

        if (nodoActual->derecha != NULL)
            cola.push(nodoActual->derecha);
    }
}

int main() {
    int numeroNodos;
    cout << "Ingrese el número de nodos del árbol: ";
    cin >> numeroNodos;

    Nodo* raiz = NULL;
    cout << "Ingrese los valores de los nodos:" << endl;
    for (int i = 0; i < numeroNodos; ++i) {
        int valor;
        cin >> valor;
        raiz = insertarNodo(raiz, valor);
    }

    // Mostrar recorridos
    cout << "Recorrido Preorden: ";
    preOrden(raiz);
    cout << endl;

    cout << "Recorrido Inorden: ";
    inOrden(raiz);
    cout << endl;

    cout << "Recorrido Posorden: ";
    posOrden(raiz);
    cout << endl;

    cout << "Recorrido por Anchura: ";
    anchura(raiz);
    cout << endl;

  
    delete raiz;

    return 0;
}
