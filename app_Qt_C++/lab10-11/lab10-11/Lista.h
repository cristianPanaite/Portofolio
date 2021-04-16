#pragma once

#pragma once
#include <string>
#include <vector>
using namespace std;

template <typename T>
struct Nod {
	T val;
	Nod* urm;
	Nod(T v) :val{ v }, urm{ nullptr } {};
	Nod(T v, Nod* urm) :val{ v }, urm{ urm } {};
};

template <typename T>
class MyListaIterator;

template <typename T>
class MyLista {

	Nod<T>* cap;

	void elibereazaNoduri();

	Nod<T>* copieaza(Nod<T>* current);

public:
	MyLista() :cap{ nullptr } {};

	MyLista(const MyLista& ot);

	void operator=(const MyLista& ot);


	~MyLista();

	size_t size() const;


	void addInceput(T v);

	void push_back(T v);

	void erase(int poz);


	T& first() const;


	MyListaIterator<T> begin() const;

	MyListaIterator<T> end() const;


	T& operator[](size_t poz);

	const vector<T> get_all();


};

template <typename T>
MyLista<T>::MyLista(const MyLista& ot) {
	cap = copieaza(ot.cap);
}

template <typename T>
void MyLista<T>::operator=(const MyLista& ot) {
	elibereazaNoduri();
	cap = copieaza(ot.cap);
}

template <typename T>
MyLista<T>::~MyLista() {
	elibereazaNoduri();
}

template <typename T>
Nod<T>* MyLista<T>::copieaza(Nod<T>* current) {
	if (current == nullptr) {
		return nullptr;
	}
	auto n = new Nod<T>{ current->val };
	n->urm = copieaza(current->urm);
	return n;
}

template <typename T>
void MyLista<T>::addInceput(T v) {
	Nod<T>* n = new Nod<T>{ v,cap };
	cap = n;
}


template <typename T>
void MyLista<T>::push_back(T v) {
	auto nCurent = cap;
	while (nCurent != nullptr && nCurent->urm != nullptr) {
		nCurent = nCurent->urm;
	}

	if (nCurent == nullptr) {
		cap = new Nod<T>{ v,nullptr };
	}
	else {
		nCurent->urm = new Nod<T>{ v,nullptr };
	}
}

template<typename T>
inline void MyLista<T>::erase(int poz)
{
	if (this->size() == 1) {
		delete cap;
		return;
	}
	if (poz == 0) {
		Nod <T>* old = cap;
		cap = cap->urm;
		delete old;
		return;
	}
	auto nCurent = cap;
	auto nNext = cap->urm;
	int lg = 0;
	while (lg < poz - 1) {
		lg++;
		nCurent = nCurent->urm;
		nNext = nNext->urm;
	}
	nCurent->urm = nNext->urm;
	delete nNext;
}

template <typename T>
size_t MyLista<T>::size() const {
	auto nCurent = cap;
	int lg = 0;
	while (nCurent != nullptr) {
		lg++;
		nCurent = nCurent->urm;
	}
	return lg;
}

template <typename T>
T& MyLista<T>::operator[](size_t poz) {
	auto nCurent = cap;
	size_t lg = 0;
	while (lg < poz) {
		lg++;
		nCurent = nCurent->urm;
	}
	return nCurent->val;
}

template<typename T>
inline const vector<T> MyLista<T>::get_all()
{
	vector<T> v;
	auto nCurtent = cap;
	while (nCurtent != nullptr) {
		v.push_back(nCurtent->val);
		nCurtent = nCurtent->urm;
	}
	return v;
}

template <typename T>
T& MyLista<T>::first() const {
	return cap->val;
}
template <typename T>
void MyLista<T>::elibereazaNoduri() {
	auto nCurent = cap;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	cap = nullptr;
}

template<typename T>
class MyListaIterator {
	Nod<T>* current;
public:
	MyListaIterator(Nod<T>* c) :current{ c } {
	}

	bool operator!=(const MyListaIterator& ot);

	void operator++();

	T& operator*();
};


template <typename T>
MyListaIterator<T> MyLista<T>::begin() const {
	return MyListaIterator<T>{ cap };
}


template <typename T>
MyListaIterator<T> MyLista<T>::end() const {
	return MyListaIterator<T>{ nullptr };
}


template <typename T>
bool MyListaIterator<T>::operator!=(const MyListaIterator& ot) {
	return current != ot.current;
}


template <typename T>
void MyListaIterator<T>::operator++() {
	current = current->urm;
}

template <typename T>
T& MyListaIterator<T>::operator*() {
	return current->val;
}