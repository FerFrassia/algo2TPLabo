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
	void nuevoCorredor(const T& c);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T& c, const T& a);
	
	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T& c);
	/*
	 * El corredor pasa al que está adelante 
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor 
	 */
	void sobrepasar(const T& c);
	
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
	int damePosicion(const T& c) const;	

	/*
	 * Devuelve el corredor de la posición. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int i) const;	




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
	bool operator==(const CorrePocoyo<T>& otro) const;	
	
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
CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& otro) {
	length = 0;
	primero = NULL;
	ultimo = NULL;
	filmado = NULL;
	if(!otro.esVacia()) {
		length++;
		ultimo = new Nodo();
		ultimo -> dato = new T(*(otro.ultimo -> dato));
		ultimo -> ant = NULL;
		ultimo -> sig = NULL;
		if (otro.filmado == otro.ultimo) {filmado = ultimo;}

		Nodo* anterior = ultimo;
		Nodo* corredor = otro.ultimo -> sig;
		while(corredor != NULL) {
			Nodo* n = new Nodo();
			n -> dato = new T(*(corredor -> dato));
			n -> ant = anterior;
			n -> sig = NULL;
			anterior -> sig = n;

			if(otro.filmado == corredor) {filmado = n;}
			anterior = n;
			corredor = corredor -> sig;
			length++;
		}
		primero = otro.primero;
	}
}

template<class T>
CorrePocoyo<T>::~CorrePocoyo() {
	if(!esVacia()) {
		Nodo* corredor = ultimo;
		Nodo* sigCorredor = NULL;
		while (corredor != NULL) {
			sigCorredor = corredor -> sig;
			seCansa(*(corredor -> dato));
			corredor = sigCorredor;
		}
	}
}

template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T& c) {
	Nodo* n = new Nodo();
	n -> dato = new T(c);
	//referencio n
	n -> ant = NULL;
	// si existe ultimo, lo referencio
	if (ultimo != NULL) {
		n -> sig = ultimo;
		ultimo -> ant = n;
		ultimo = n;
	}
	else {
		//como no hay ultimo, tampoco hay primero ni filmado
		n -> sig = NULL;
		primero = n;
		filmado = n;
		ultimo = n;
	}	
	length++;	
}

template<class T>
void CorrePocoyo<T>::nuevoCorredor(const T& c, const T& a) {
	assert(length > 0);
	Nodo* n = new Nodo();
	n -> dato = new T(c);
	//busco al corredor a
	Nodo* corredor = ultimo;
	Nodo* sigCorredor = NULL;
	//cuando encuentro a a, agrego a c adelante
	while(corredor != NULL) {
		if(*(corredor -> dato) == a) {
			if(corredor == primero) {
				//referencio a corredor
				corredor -> sig = n;
				//referencio a n 
				n -> sig = NULL;
				n -> ant = corredor;
				primero = n;
			}
			else {
				sigCorredor = corredor -> sig;
				//referencio a sigCorredor
				sigCorredor -> ant = n;
				//referencio a corredor
				corredor -> sig = n;
				//referencio a n 
				n -> sig = sigCorredor;
				n -> ant = corredor;
			}
		}
		sigCorredor = corredor -> sig;
		corredor = sigCorredor;
	}
	length++;
}

template<class T>
void CorrePocoyo<T>::seCansa(const T& c) {
	if(length == 1 || primero == ultimo)	{
		delete ultimo -> dato;
		delete ultimo;
		length = 0;
		primero = NULL;
		ultimo = NULL;
		filmado = NULL;
		return;
	}
	else	{
		Nodo* corredor = ultimo;
		Nodo* sigCorredor = NULL;
		//busco al corredor
		while(*(corredor -> dato) != c) {
			sigCorredor = corredor -> sig;
			corredor = sigCorredor;
		}
		//si es el ultimo y es el filmado
		if (corredor -> ant == NULL && corredor == filmado) {
			(corredor -> sig) -> ant = NULL; 
			ultimo = corredor -> sig;
			filmado = filmado -> sig;
		//si es el ultimo y no es el filmado
		}
		else if (corredor -> ant == NULL && corredor != filmado) {
			(corredor -> sig) -> ant = NULL; 
			ultimo = corredor -> sig;
		}
		//si es el primero y es el filmado
		else if (corredor -> sig == NULL && corredor == filmado) {
			(corredor -> ant) -> sig = NULL;
			primero = corredor -> ant;
			filmado = filmado -> ant;
		}
		//si es el primero y no es el filmado
		else if (corredor -> sig == NULL && corredor != filmado) {
			(corredor -> ant) -> sig = NULL;
			primero = corredor -> ant;
		}
		//si esta en el medio y es el filmado
		else if (corredor == filmado) {
			(corredor -> ant) -> sig = corredor -> sig;
			(corredor -> sig) -> ant = corredor -> ant;
			filmado = filmado -> ant;
		}
		//si esta en el medio y no es el filmado
		else {
			(corredor -> ant) -> sig = corredor -> sig;
			(corredor -> sig) -> ant = corredor -> ant;
		}
		delete corredor -> dato;
		delete corredor;
		length--;
		return;
	}
}

template<class T>
void CorrePocoyo<T>::sobrepasar(const T& c) {
	//busco al coredor
	Nodo* corredor = ultimo;
	Nodo* sigCorredor = NULL;
	Nodo* antCorredor = NULL;
	Nodo* sigsigCorredor = NULL;

	while(*(corredor -> dato) != c) {
		sigCorredor = corredor -> sig;
		corredor = sigCorredor;
	}
	antCorredor = corredor -> ant;
	sigCorredor = corredor -> sig;
	//si es el ultimo y es el segundo
	if (corredor == ultimo && sigCorredor == primero) {
		ultimo = antCorredor;	
		primero = corredor;
		sigCorredor -> ant = antCorredor;
		sigCorredor -> sig = corredor;
		corredor -> ant = sigCorredor;
		corredor -> sig = NULL;	
	}
	//si es el ultimo y no es el segundo
	else if (corredor == ultimo && sigCorredor != primero)  {
		ultimo = sigCorredor;
		sigsigCorredor = sigCorredor -> sig;
		sigCorredor -> ant = antCorredor;
		sigCorredor -> sig = corredor;
		sigsigCorredor -> ant = corredor;
		corredor -> ant = sigCorredor;
		corredor -> sig = sigsigCorredor;
	}
	//si no es el ultimo y es el segundo
	else if (corredor != ultimo && sigCorredor == primero) {
		primero = corredor;
		antCorredor -> sig = sigCorredor;
		sigCorredor -> ant = antCorredor;
		sigCorredor -> sig = corredor;
		corredor -> ant = sigCorredor;
		corredor -> sig = NULL;
	}
	//si no es el ultimo y no es el segundo
	else if (corredor != ultimo && sigCorredor != primero){
		sigsigCorredor = sigCorredor -> sig;
		antCorredor -> sig = sigCorredor;
		sigCorredor -> ant = antCorredor;
		sigCorredor -> sig = corredor;
		sigsigCorredor -> ant = corredor;
		corredor -> ant = sigCorredor;
		corredor -> sig = sigsigCorredor;
	}
}

template<class T>
const T& CorrePocoyo<T>::corredorFilmado() const {
		return *(filmado -> dato);
}

template<class T>
void CorrePocoyo<T>::filmarProxPerdedor() {
		filmado = filmado -> ant;
}

template<class T>
void CorrePocoyo<T>::filmarProxExitoso() {
		filmado = filmado -> sig;
}

template<class T>
const T& CorrePocoyo<T>::damePrimero() const {
		return *(primero -> dato);
}

template<class T>
int CorrePocoyo<T>::damePosicion(const T& c) const {
	int j = 1;
	Nodo* corredor = primero;
	while (*(corredor -> dato) != c) {
		corredor = corredor -> ant;
		j++;
	}
	return j;
}

template<class T>
const T& CorrePocoyo<T>::dameCorredorEnPos(int i) const {
	int j = 1;
	Nodo* corredor = primero;
	while(j != i) {
		corredor = corredor -> ant;
		j++;
	}
	return *(corredor -> dato);
}

template<class T>
bool CorrePocoyo<T>::esVacia() const {
	return length == 0;

}

template<class T>
int CorrePocoyo<T>::tamanio() const {
	return length;

}

template<class T>
bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>& otro) const {
	if(esVacia() && otro.esVacia()) { return true; }
	else if (esVacia() || otro.esVacia()) {return false;}
	else {
		//chequeo largo, primero y ultimo
		if (length != otro.length || *(primero -> dato) != *(otro.primero -> dato) || *(ultimo -> dato) != *(otro.ultimo -> dato)) {
			return false;
		}
		//chequeo filmado
		if ((filmado != NULL && otro.filmado != NULL && *(filmado -> dato) != *(otro.filmado -> dato)) || (filmado != NULL && otro.filmado == NULL) || (filmado == NULL && otro.filmado != NULL)) {
			return false;
		}
		// chequeo todos los corredores
		Nodo* corredor = primero;
		Nodo* oCorredor = otro.primero;
		while(corredor != NULL) {
			if (*(corredor -> dato) != *(oCorredor -> dato)) {
				return false;
			}
			corredor = corredor -> ant;
			oCorredor = oCorredor -> ant;
		}
		return true;
	}
}

template<class T>
ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& os) const {
	os << "[";
		if(!esVacia()) {
			Nodo* corredor = primero;
			while(corredor != NULL)	{
				//el corredor es filmado y no es ultimo
				//if(*(corredor -> dato) == *(filmado -> dato) && *(corredor -> dato) != *(ultimo -> dato)) {
				//	os << "FILMADO(" << *(corredor -> dato) << "), ";
				//}
				//el corredor es filmado y es ultimo
				//else if(*(corredor -> dato) == *(filmado -> dato) && *(corredor -> dato) == *(ultimo -> dato)) {
				//	os << "FILMADO(" << *(corredor -> dato);
				//}
				//el corredor no es filmado y es ultimo
				if (*(corredor -> dato) == *(ultimo -> dato)) {
					os << *(corredor -> dato);
				}
				//el corredor no es filmado y no es ultimo
				else {
					os << *(corredor -> dato) << ", ";
				}
				corredor = corredor -> ant;
			}
		}
	os << "]";
	return os;
}













#endif //CORREPOCOYO_H_
