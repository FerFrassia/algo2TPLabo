#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	/*
	 * Crea una nueva carrera
	 */	
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CorrePocoyo(const CorrePocoyo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final 
	 */
	void nuevoCorredor(const T&);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T&, const T&);
	
	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);
	/*
	 * El corredor pasa al que está adelante 
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor 
	 */
	void sobrepasar(const T&);
	
	/*
	 * Devuelve el corredor que está siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;
	
    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de atás 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();
	    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de adelante 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	const T& damePrimero() const;	

	/*
	 * Devuelve la posición del elemento pasado por parámetro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	int damePosicion(const T& ) const;	

	/*
	 * Devuelve el corredor de la posición. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;	




	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		const T* dato;
		Nodo* sig;
		Nodo* ant;
	};

	int length;
	Nodo* primero;
	Nodo* ultimo;
	Nodo* filmado;

};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.

template <class T>
CorrePocoyo<T>::CorrePocoyo() {
	length = 0;
	primero = NULL;
	ultimo = NULL;
	filmado = NULL;
}

template<class T>
CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>&) {

}

template<class T>
CorrePocoyo<T>::~CorrePocoyo() {

}

template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T&) {
	Nodo* = new Nodo();
	


}

template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T&, const T&) {

}

template<class T>
void CorrePocoyo<T>::seCansa(const T&) {

}

template<class T>
void CorrePocoyo<T>::sobrepasar(const T&) {

}

template<class T>
const T& CorrePocoyo<T>::corredorFilmado() const {

}

template<class T>
void CorrePocoyo<T>::filmarProxPerdedor() {

}

template<class T>
void CorrePocoyo<T>::filmarProxExitoso() {

}

template<class T>
const T& CorrePocoyo<T>::damePrimero() const {

}

template<class T>
int CorrePocoyo<T>::damePosicion(const T&) const {

}

template<class T>
const T& CorrePocoyo<T>::dameCorredorEnPos(int) const {

}

template<class T>
bool CorrePocoyo<T>::esVacia() const {

}

template<class T>
int CorrePocoyo<T>::tamanio() const {

}

template<class T>
bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>&) const {

}

template<class T>
ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream&) const {

}













#endif //CORREPOCOYO_H_
