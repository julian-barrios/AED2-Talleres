#include <iostream>
#include "list"
using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(uint mes, uint dia);
    uint mes();
    uint dia();
    void incrementar_dia();
    bool operator==(Fecha o);
    bool operator<(Fecha f);

  private:
    uint mes_;
    uint dia_;
};

Fecha::Fecha(uint mes, uint dia): mes_(mes), dia_(dia) {}

uint Fecha::mes() {
    return mes_;
}

uint Fecha::dia() {
    return dia_;
}

// Ejercicio 8

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

bool Fecha::operator==(Fecha o) {
    bool igual_dia (this -> mes_ == o.mes());
    bool igual_mes (this -> dia_ == o.dia());
    return (igual_mes and igual_dia);
}

bool Fecha::operator<(Fecha f) {
    if(mes_ == f.mes()){
        return dia_ < f.dia();
    } else {
        return mes_ < f.mes();
    }
}

// Ejercicio 11, 12

void Fecha::incrementar_dia() {
    if((mes_ == 2 && dia_== 28) || (mes_ % 2 == 1 && dia_ == 31) || (mes_ % 2 == 0 && dia_ == 30)){
        dia_= 1;
        mes_ = mes_ + 1;
    } else {
        dia_= dia_ + 1;
    }
}

//Ejercicio 11
// Clase Horario

class Horario {
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator==(Horario o);
    bool operator<(Horario h);

private:
    uint hora_;
    uint min_;
};

Horario::Horario(uint hora, uint min): hora_(hora), min_(min) {}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}
ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator==(Horario o) {
    bool igual_hora (this -> hora_ == o.hora());
    bool igual_min (this -> min_ == o.min());
    return (igual_hora and igual_min);
}

// Ejercicio 12

bool Horario::operator<(Horario o) {
    if(hora_ == o.hora()){
        return min_ < o.min();
    } else {
        return hora_ < o.hora();
    }
}

// Ejercicio 13

// Clase Recordatorio

class Recordatorio{
public:
    Recordatorio(Fecha f, Horario h, string mensaje);
        Fecha f();
        Horario h();
        string mensaje();
    bool operator<(Recordatorio r);

private:
    Fecha f_;
    Horario h_;
    string mensaje_;
};

Recordatorio::Recordatorio(Fecha f, Horario h, string mensaje): f_(f), h_(h), mensaje_(mensaje) {}

string Recordatorio::mensaje(){
    return mensaje_;
}

Fecha Recordatorio::f() {
    return f_;
}

Horario Recordatorio::h() {
    return h_;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.mensaje() << " @ " << r.f() << " " << r.h();
    return os;
}
bool Recordatorio::operator<(Recordatorio r) {
    if(f_ == r.f()){
        return h_ < r.h();
    } else {
        return f_ < r.f();
    }
}

// Ejercicio 14

// Clase Agenda

class Agenda{
public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();

private:
    Fecha hoy_;
    list<Recordatorio> recordatorios_de_hoy_;
};

Agenda::Agenda(Fecha fecha_inicial): hoy_(fecha_inicial), recordatorios_de_hoy_() {}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    recordatorios_de_hoy_.push_front(rec);
}

void Agenda::incrementar_dia() {
    hoy_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> recs;
    for(Recordatorio r: recordatorios_de_hoy_){
        recs.push_front(r);
    }
    recs.sort();
    return recs;
}

Fecha Agenda::hoy(){
    return hoy_;
}

ostream& operator<<(ostream &os,  Agenda a){
    if(a.hoy().dia() != a.recordatorios_de_hoy().front().f().dia()){
        os << a.hoy() << endl;
        os << "=====" << endl;
    } else {
        os << a.hoy() << endl;
        os << "=====" << endl;
        for(Recordatorio r: a.recordatorios_de_hoy()){
            os << r << endl;
        }
        a.incrementar_dia();
    }
    return os;
}









