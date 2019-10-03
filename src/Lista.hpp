#include "Lista.h"

template <typename T>
Lista<T>::Lista() {
    this->_prim = nullptr;
    this->_ult = nullptr;
}

template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
    Lista nueva = Lista();
    nueva = l;
    *this = nueva;
}

template <typename T>
Lista<T>::~Lista() {
    this->eliminarTodos();
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
    this->eliminarTodos();
    int longitud = aCopiar.longitud();
    for(int i = 0; i < longitud; i++) {
        T iesimo = aCopiar.iesimo(i);
        this->agregarAtras(iesimo);
    }
    return *this;
}

template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
    Nodo *pNuevoNodo = new Nodo(elem, this->_prim, nullptr);
    if(this->longitud() > 0) this->_prim->_ant = pNuevoNodo;
    else this->_ult = pNuevoNodo;
    this->_prim = pNuevoNodo;
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
    Nodo *pNuevoNodo = new Nodo(elem, nullptr, this->_ult);
    if(this->longitud() > 0) this->_ult->_sig = pNuevoNodo;
    else this->_prim = pNuevoNodo;
    this->_ult = pNuevoNodo;
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
    Nodo *pNodo = this->iesimoNodo(i);
    Nodo *ant = pNodo->_ant;
    Nodo *sig = pNodo->_sig;

    delete pNodo;
    if(ant == nullptr) {
        this->_prim = sig;
    } else {
        ant->_sig = sig;
    }

    if(sig == nullptr) {
        this->_ult = ant;
    } else {
        sig->_ant = ant;
    }
}

template<typename T>
void Lista<T>::eliminarTodos() {
    int longitud = this->longitud();
    for(int i = 0; i < longitud; i++) {
        this->eliminar(0);
    }
}

template <typename T>
int Lista<T>::longitud() const {
    Nodo *actual = this->_prim;
    int longitud = 0;

    while(actual != nullptr) {
        longitud++;
        actual = actual->_sig;
    }

    return longitud;
}

//Notar que cualquier algoritmo que use este metodo iterativamente tendra una mayor complejidad temporal que
//uno que recorra la lista manualmente.
template <typename T>
typename Lista<T>::Nodo* Lista<T>::iesimoNodo(Nat i) const {
    Nodo* actual = this->_prim;
    int posicion = 0;
    while(posicion != i) {
        actual = actual->_sig;
        posicion++;
    }

    return actual;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
    return this->iesimoNodo(i)->_valor;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
    return this->iesimoNodo(i)->_valor;
}

template <typename T>
void Lista<T>::mostrar(ostream& o) {
    int longitud = this->longitud();
    for(int i = 0; i < longitud; i++) {
        T iesimo = this->iesimo(i);
        o << iesimo;
    }
}
