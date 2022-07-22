template <typename T>
string_map<T>::string_map() {
    _raiz = new Nodo();
    _size = 0;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    char str[50];
    vector<pair<string, T>> palabras;
    claves(d._raiz, str, 0, palabras);
    for(int i = 0; i < palabras.size(); i++){
        this->insert(palabras[i]);
    }
    return *this;
}

template<typename T>
void string_map<T>::claves(Nodo* nodo, char str[], int nivel, vector<pair<string, T>> &result) const{
    if (vacio(nodo) || nodo->definicion != 0){
        str[nivel] = '\0';
        result.push_back(make_pair(str, nodo->definicion));
    }
    for (int i = 0; i < cantidadDeCaracteres; i++){
        if (nodo->siguientes[i] != nullptr){
            str[nivel] = char(i);
            claves(nodo->siguientes[i], str, nivel + 1, result);
        }
    }
}

template <typename T>
string_map<T>::~string_map(){
    destructorRecursivo(_raiz, 0);
}

template<typename T>
void string_map<T>::destructorRecursivo(Nodo* nodo, int nivel){
    if (vacio(nodo)){
        delete nodo;
        return;
    }
    for (int i = 0; i < cantidadDeCaracteres; i++) {
        if (nodo->siguientes[i] != nullptr) {
            destructorRecursivo(nodo->siguientes[i], nivel + 1);
        }
    }
    delete nodo;
}

template<typename T>
void string_map<T>::insert(const pair<string, T>& dicc) {
    auto nodo = _raiz;
    for(auto x: dicc.first){
        if(nodo->siguientes[x] == nullptr){
            nodo->siguientes[x] = new Nodo();
        }
        nodo = nodo->siguientes[x];
    }
    nodo->definicion = dicc.second;
    _size++;
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    auto nodo = _raiz;
    for(auto x: clave){
        if(nodo->siguientes[x] != nullptr){
            nodo = nodo->siguientes[x];
        }
    }
    if(nodo->definicion != 0){
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    auto nodo = _raiz;
    for(auto x: clave){
        if(nodo->siguientes[x] != nullptr){
            nodo = nodo->siguientes[x];
        }
    }
    return nodo->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    eraseRecursivo(_raiz, clave, 0);
    _size--;
}

template<typename T>
void string_map<T>::eraseRecursivo(Nodo* nodo, const string& clave, int nivel) {
    if(nodo != nullptr){
        if (nivel == clave.size()) {
            if (nodo->definicion != 0) {
                nodo->definicion = 0;
                nodo = nullptr;
                delete nodo;
                return;
            }
        }
        if(nivel < clave.size()){
            eraseRecursivo(nodo->siguientes[clave[nivel]], clave, nivel + 1);
            if (vacio(nodo)) {
                delete nodo;
            }
        }
    }
}

template <typename T>
int string_map<T>::size() const{
    return _size;
}

template <typename T>
bool string_map<T>::empty() const{
    return vacio(_raiz);
}

template<typename T>
bool string_map<T>::vacio(Nodo *nodo) const {
    if(nodo != nullptr) {
        int i;
        for (i = 0; i < cantidadDeCaracteres && nodo->siguientes[i] == nullptr; i++) {
        }
        return i == cantidadDeCaracteres;
    }
}