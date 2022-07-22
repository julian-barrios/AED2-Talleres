#include "Lista.h"

Lista::Lista()  {
        longitud_= 0;
        primero_ = nullptr;
}

Lista::Lista(const Lista& l) : Lista() {
    *this = l;
}

Lista::~Lista() {
    if(primero_ != nullptr){
        Nodo *temp = primero_;
        while(temp != nullptr){
            temp = temp->siguiente;
            delete primero_;
            primero_ = temp;
        }
    }
}

Lista& Lista::operator=(const Lista& aCopiar){
    if(this->longitud() > 0) {
        int longitud = this->longitud();
        for (int i = 0; i < longitud; i++) {
            this->eliminar(0);
        }
    }
    for(int i = 0; i < aCopiar.longitud(); i++){
        int elem = aCopiar.iesimo(i);
        this->agregarAtras(elem);
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* nuevo_nodo = new Nodo();
    nuevo_nodo->valor = elem;
    nuevo_nodo->siguiente = primero_;
    primero_ = nuevo_nodo;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* nuevo_nodo = new Nodo();
    Nodo* anteultimo = primero_;
    nuevo_nodo->valor = elem;
    nuevo_nodo->siguiente = nullptr;
    if(primero_ == nullptr){
        primero_ = nuevo_nodo;
    } else {
        while(anteultimo->siguiente != nullptr){
            anteultimo = anteultimo->siguiente;
        }
        anteultimo->siguiente = nuevo_nodo;
    }
}

void Lista::eliminar(Nat i) {
    Nodo* temp = primero_;
    if (temp != nullptr && i == 0){
        primero_ = temp->siguiente;
        delete temp;
    } else {
        Nodo* prev = temp;
        temp = primero_->siguiente;
        for (int contador = 1; temp->siguiente != nullptr && contador != i; contador++){
            prev = temp;
            temp = temp->siguiente;
        }
        if (temp->siguiente == nullptr){
            prev->siguiente = nullptr;
            delete temp;
        } else {
            prev->siguiente = temp->siguiente;
            delete temp;
        }
    }
}

int Lista::longitud() const {
    int count = 0;
    Nodo* actual = primero_;
    while (actual != nullptr){
        count++;
        actual = actual->siguiente;
    }
    return count;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* actual = primero_;
    Nat contador = 0;
    while (contador < i){
        actual = actual->siguiente;
        contador++;
    }
    return actual->valor;
}

int& Lista::iesimo(Nat i) {
    Nat contador = 0;
    Nodo* actual = primero_;
    while (contador < i){
        actual = actual->siguiente;
        contador++;
    }
    return actual->valor;
}

void Lista::mostrar(ostream& o) {
}
