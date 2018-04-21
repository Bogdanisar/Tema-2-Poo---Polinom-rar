#pragma once

template<typename T>
Monom<T>::Monom(T _coef, int _grad) :
	DoubleNode<T>(_coef), grad(_grad) {
	if (_grad < 0) {
		throw std::invalid_argument("Degree can't be negative!");
	}

	if (debugMonom) cout << "Constructor Monom\n";
}

template<typename T>
Monom<T>::Monom(const Monom<T>& other):
	DoubleNode<T>(other), grad(other.grad) {

	if (debugMonom) cout << "Copiere Monom\n";
}

//*
template<typename T>
Monom<T>& Monom<T>::operator= (const Monom<T>& other) {
	if (debugMonom) cout << "Atribuire Monom\n";
	if (this == &other) {
		return *this;
	}

	DoubleNode<T>::operator=(other);
	(int&)grad = other.grad;

	return *this;
}
//*/

template<typename T>
bool Monom<T>::operator<(const Monom& other) {
	if (grad == other.grad) {
		return coef < other.coef;
	}
	return grad < other.grad;
}

template<typename T>
std::istream& operator>> (std::istream& in, Monom<T>& m) {
	in >> m.coef >> (int&)m.grad;

	if (debugMonom) cout << "Citire Monom\n";

	return in;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const Monom<T>& m) {
	out << m.coef << "*X^" << m.grad;

	if (debugMonom) cout << "Scriere Monom\n";

	return out;
}

template<typename T>
Monom<T>::~Monom() {

	if (debugMonom) cout << "Destructor Monom\n";
}