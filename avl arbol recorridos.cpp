#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// Definición de la estructura de un nodo de árbol AVL
struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

    Nodo(int valor) {
        dato = valor;
        izquierda = NULL;
        derecha = NULL;
        altura = 1;
    }
};

// Función para obtener la altura de un nodo
int altura(Nodo* nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

// Función para obtener el balance de un nodo
int balance(Nodo* nodo) {
    if (nodo == NULL)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// Función para realizar una rotación hacia la derecha
Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    // Realizar rotación
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

// Función para realizar una rotación hacia la izquierda
Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    // Realizar rotación
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar alturas
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

// Función para insertar un nodo en el árbol AVL
Nodo* insertarNodo(Nodo* raiz, int valor) {
    // Paso 1: Realizar la inserción normal de un árbol binario de búsqueda
    if (raiz == NULL)
        return new Nodo(valor);

    if (valor < raiz->dato)
        raiz->izquierda = insertarNodo(raiz->izquierda, valor);
    else if (valor > raiz->dato)
        raiz->derecha = insertarNodo(raiz->derecha, valor);
    else // No permitir duplicados
        return raiz;

    // Paso 2: Actualizar la altura del nodo actual
    raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));

    // Paso 3: Obtener el factor de balance y realizar las rotaciones si es necesario
    int factorBalance = balance(raiz);

    // Rotaciones
    // Caso izquierda-izquierda
    if (factorBalance > 1 && valor < raiz->izquierda->dato)
        return rotacionDerecha(raiz);

    // Caso derecha-derecha
    if (factorBalance < -1 && valor > raiz->derecha->dato)
        return rotacionIzquierda(raiz);

    // Caso izquierda-derecha
    if (factorBalance > 1 && valor > raiz->izquierda->dato) {
        raiz->izquierda = rotacionIzquierda(raiz->izquierda);
        return rotacionDerecha(raiz);
    }

    // Caso derecha-izquierda
    if (factorBalance < -1 && valor < raiz->derecha->dato) {
        raiz->derecha = rotacionDerecha(raiz->derecha);
        return rotacionIzquierda(raiz);
    }

    // Si no se requieren rotaciones, devolver el nodo sin cambios
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

