#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

// Definici�n de la estructura de un nodo de �rbol AVL
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

// Funci�n para obtener la altura de un nodo
int altura(Nodo* nodo) {
    if (nodo == NULL)
        return 0;
    return nodo->altura;
}

// Funci�n para obtener el balance de un nodo
int balance(Nodo* nodo) {
    if (nodo == NULL)
        return 0;
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

// Funci�n para realizar una rotaci�n hacia la derecha
Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    // Realizar rotaci�n
    x->derecha = y;
    y->izquierda = T2;

    // Actualizar alturas
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

// Funci�n para realizar una rotaci�n hacia la izquierda
Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    // Realizar rotaci�n
    y->izquierda = x;
    x->derecha = T2;

    // Actualizar alturas
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

// Funci�n para insertar un nodo en el �rbol AVL
Nodo* insertarNodo(Nodo* raiz, int valor) {
    // Paso 1: Realizar la inserci�n normal de un �rbol binario de b�squeda
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

// Funci�n para recorrido preorden
void preOrden(Nodo* raiz) {
    if (raiz == NULL)
        return;

    cout << raiz->dato << " ";
    preOrden(raiz->izquierda);
    preOrden(raiz->derecha);
}

// Funci�n para recorrido inorden
void inOrden(Nodo* raiz) {
    if (raiz == NULL)
        return;

    inOrden(raiz->izquierda);
    cout << raiz->dato << " ";
    inOrden(raiz->derecha);
}

// Funci�n para recorrido posorden
void posOrden(Nodo* raiz) {
    if (raiz == NULL)
        return;

    posOrden(raiz->izquierda);
    posOrden(raiz->derecha);
    cout << raiz->dato << " ";
}

// Funci�n para recorrido por anchura (nivel por nivel)
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
    cout << "Ingrese el n�mero de nodos del �rbol: ";
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

