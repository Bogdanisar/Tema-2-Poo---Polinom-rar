#pragma once

#include "dList.h"
#include "Monom.h"
#include <iostream>

namespace PoliList {
	
	template<typename T>
	class Polinom: public dList<T> {
	public:
		class iterator;

	private:
		void add(const iterator&, const Monom<T>&);
		void clean();

	public:
		Polinom();
		Polinom(const Monom<T>&);
		Polinom(const Polinom&);

		virtual Polinom& operator=(const dList<T>&);
		virtual Polinom& operator=(const Polinom<T>&);
		virtual void push_front(const T&);
		virtual void push_back(const T&);
		virtual void add(const dList<T>::iterator&, const T&);
		T valueOf(const T&) const;
		int grad() const;

		Polinom operator+(const Polinom&);
		Polinom operator-(const Polinom&);
		Polinom operator*(const Polinom&);
		Polinom operator/(const Polinom&);
		Polinom operator%(const Polinom&);

		Monom<T>& operator[] (int);
		virtual bool operator<(const dList<T>&) const;

		template<typename U>
		friend std::istream& operator>>(std::istream&, Polinom<U>&);
		template<typename U>
		friend std::ostream& operator<<(std::ostream&, const Polinom<U>&);

		iterator begin() const {
			iterator it = iterator(dList<T>::sentinel, dList<T>::sentinel);
			++it;
			return it;
		}
		iterator end() const {
			return iterator(dList<T>::sentinel, dList<T>::sentinel);
		}

		virtual ~Polinom();
	};

#include "Polinom.cpp"
}