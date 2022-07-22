#include "Conjunto.h"


template <class T>
Conjunto<T>::Conjunto(){
    _raiz = nullptr;
    _longitud = 0;
}

template <class T>
Conjunto<T>::~Conjunto() {
    destruir(_raiz);
}

template <class T>
void Conjunto<T>::destruir(Nodo* n) {
    if (n != nullptr) {
        destruir(n->izq);
        destruir(n->der);
        delete n;
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    return perteneceRecursivo(_raiz, clave);
}

template<class T>
bool Conjunto<T>::perteneceRecursivo(Nodo *nodo, const T& clave) const {
    if (nodo == nullptr) {
        return false;
    }
    if (nodo->valor == clave){
        return true;
    } else {
        if (nodo->valor < clave){
            return perteneceRecursivo(nodo->der, clave);
        } else {
            return perteneceRecursivo(nodo->izq, clave);
        }
    }
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(!pertenece(clave)){
        Nodo* nuevo_nodo = new Nodo();
        nuevo_nodo->valor = clave;
        if (_longitud == 0){
            _raiz = nuevo_nodo;
        } else {
            bool insertado = false;
            Nodo* iterador = _raiz;
            while(!insertado){
                if(clave > iterador->valor){
                    if(iterador->der != nullptr){
                        iterador = iterador->der;
                    } else {
                        iterador->der = nuevo_nodo;
                        iterador->der->padre = iterador;
                        insertado = true;
                    }
                } else {
                    if (iterador->izq != nullptr) {
                        iterador = iterador->izq;
                    } else {
                        iterador->izq = nuevo_nodo;
                        iterador->izq->padre = iterador;
                        insertado = true;
                    }
                }
            }
        }
        _longitud++;
    }
}


template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (pertenece(clave)) {
        if (_longitud == 1) {
            delete _raiz;
            _raiz = nullptr;
        } else {
            removerRecursivo(_raiz, clave);
        }
        _longitud--;
    }
}
template<class T>
void Conjunto<T>::removerRecursivo(Nodo* nodo,const T& valor){
    if(nodo->valor == valor){
        if(esHoja(nodo)){
            if(nodo == nodo->padre->izq){
                nodo->padre->izq = nullptr;
            } else {
                nodo->padre->der = nullptr;
            }
            delete nodo;
        } else {
            if(nodo->der != nullptr){
                nodo->valor = minimoRecursivo(nodo->der);
                removerRecursivo(nodo->der, nodo->valor);
            } else {
                nodo->valor = maximoRecursivo(nodo->izq);
                removerRecursivo(nodo->izq, nodo->valor);
            }
        }
    } else {
        if(nodo->valor > valor){
            removerRecursivo(nodo->izq, valor);
        } else {
            removerRecursivo(nodo->der, valor);
        }
    }
}

template<class T>
const T& Conjunto<T>::minimoRecursivo(Nodo* nodo) const {
    while (nodo->izq != nullptr){
        nodo = nodo->izq;
    }
    return nodo->valor;
}

template<class T>
const T& Conjunto<T>::maximoRecursivo(Nodo* nodo) const {
    while (nodo->der != nullptr){
        nodo = nodo->der;
    }
    return nodo->valor;
}

template<class T>
bool Conjunto<T>::esHoja(Nodo* nodo){
    return nodo->der == nullptr && nodo->izq == nullptr;
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    if(pertenece(clave)){
        Nodo* iterador = _raiz;
        while(iterador->valor != clave){
            if(clave > iterador->valor){
                iterador = iterador->der;
            } else {
                iterador = iterador->izq;

            }
        }
        return siguienteRecursivo(iterador);
    }
}

template <class T>
const T& Conjunto<T>::siguienteRecursivo(Nodo* nodo){
        if (nodo->der != nullptr){
            return minimoRecursivo(nodo->der);
        }
        Nodo* padre = nodo->padre;
        while (padre != nullptr && nodo == padre->der){
            nodo = padre;
            padre = padre->padre;
        }
        return padre->valor;
    }

template <class T>
const T& Conjunto<T>::minimo() const {
    return minimoRecursivo(_raiz);
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return maximoRecursivo(_raiz);
}


template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinalRecursivo(_raiz);
}

template <class T>
unsigned int Conjunto<T>::cardinalRecursivo(Nodo* nodo) const{
    if(nodo == nullptr){
        return 0;
    } else {
        return 1 + cardinalRecursivo(nodo->der) + cardinalRecursivo(nodo->izq);
    }
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
}



