#pragma once
#include "DoubleNode.h"
#include <iostream>
#include <stdexcept>

namespace PoliList {
	const int debugMonom = 0;

	template<typename T>
	class Monom : protected DoubleNode<T> {
	public:
		T& coef = SimpleNode<T>::info;
		const int grad;		

	public:
		explicit Monom(T _coef = T(), int _grad = 0);
		Monom(const Monom&);

		Monom& operator= (const Monom& other);
		bool operator<(const Monom&);

		template<typename U>
		friend std::istream& operator>> (std::istream&, Monom<U>&);

		template<typename U>
		friend std::ostream& operator<< (std::ostream&, const Monom<U>&);

		~Monom();
	};

#include "Monom.cpp"
}