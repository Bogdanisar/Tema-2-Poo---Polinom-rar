#pragma once

template<typename T>
class Polinom<T>::iterator {
	DoubleNode<T>* ptr;
	DoubleNode<T>* sent;

	friend Polinom<T>;
private:
	iterator(DoubleNode<T>* _ptr, DoubleNode<T>* _sent) : ptr(_ptr), sent(_sent) {}
public:

	iterator & operator=(const iterator& other) {
		if (this == &other) {
			return *this;
		}

		ptr = other.ptr;
		sent = other.sent;
	}

	virtual const iterator& operator++ () {
		ptr = (DoubleNode<T>*)ptr->nxt;
		return *this;
	}

	virtual iterator operator++ (int) {
		iterator ret(*this);
		this->operator++();
		return ret;
	}

	virtual const iterator& operator-- () {
		ptr = (DoubleNode<T>*)ptr->prv;
		return *this;
	}

	virtual iterator operator-- (int) {
		iterator ret(*this);
		this->operator--();
		return ret;
	}

	bool operator== (const iterator& other) const {
		return ptr == other.ptr && sent == other.sent;
	}

	bool operator!= (const iterator& other) const {
		return !((*this) == other);
	}

	//*
	Monom<T>& operator* () const {
		if ((DoubleNode<T>*)ptr == sent) {
			throw std::domain_error("Can't dereference end()!: 55 Polinom.cpp");
		}

		//cout << (((Monom<T>*)ptr)->grad) << "  ";

		return (Monom<T>&)(*ptr);
	}
	//*/

	Monom<T>* operator->() const {
		if ((DoubleNode<T>*)ptr == sent) {
			throw std::domain_error("Can't dereference end()!: 66 Polinom.cpp");
		}
		return (Monom<T>*)ptr;
	}

	operator dList<T>::iterator() const {
		return dList<T>::iterator(ptr, sent);
	}
};

template<typename T>
Polinom<T>::Polinom() : dList<T>() {
}

template<typename T>
Polinom<T>::Polinom(const Monom<T>& mon) : dList<T>() {
	add(end(), mon);
	//cout << mon << "\n\n\n";
}

template<typename T>
Polinom<T>::Polinom(const Polinom<T>& pol) : dList<T>() {

	for (iterator it = pol.begin(); it != pol.end(); ++it) {
		add(end(), *it);
	}
}

template<typename T>
Polinom<T>& Polinom<T>::operator=(const dList<T>& other) {
	if (this == &other) {
		return *this;
	}

	this->clear();

	bool fail = false;
	try {
		dynamic_cast<const Polinom<T>&>(other);
	}
	catch (...) {
		fail = true;
	}

	if (!fail) {
		for (iterator it = ((const Polinom<T>&)other).begin(); it != ((const Polinom<T>&)other).end(); ++it) {
			add(end(), *it);
		}
	}
	else {
		int num = 0;
		for (dList<T>::iterator it = other.begin(); it != other.end(); ++it, ++num) {
			Monom<T> m(*it, num);
			add(end(), m);
		}
	}
}

template<typename T>
Polinom<T>& Polinom<T>::operator=(const Polinom<T>& other) {
	if (this == &other) {
		return *this;
	}

	this->clear();

	for (iterator it = ((const Polinom<T>&)other).begin(); it != ((const Polinom<T>&)other).end(); ++it) {
		add(end(), *it);
	}
}

template<typename T>
void Polinom<T>::push_front(const T& elem) {
	if (this->size() == 0) {
		add(begin(), Monom<T>(elem, 0));
		return;
	}

	begin()->coef += elem;
	//(*begin()).coef += elem;
}

template<typename T>
void Polinom<T>::push_back(const T& elem) {
	if (this->size() == 0) {
		add(end(), Monom<T>(elem, 0));
		return;
	}

	iterator aux = end();
	--aux;
	int grad = aux->grad + 1;
	add(end(), Monom<T>(elem, grad));
}

template<typename T>
void Polinom<T>::add(const dList<T>::iterator& it, const T& elem) {
	if (it.ptr == dList<T>::sentinel) {
		throw domain_error("Can't add coefficient to end()!");
	}
	*it += elem;
}

template<typename T>
void Polinom<T>::add(const Polinom<T>::iterator& it, const Monom<T>& mon) {
	if (it.sent != dList<T>::sentinel) {
		throw std::invalid_argument("Erase: Iterator is from a different object!");
	}

	DoubleNode<T>* ptr = (DoubleNode<T>*)(new Monom<T>(mon));
	//cout << *(Monom<T>*)ptr << "      ";
	dList<T>::add(it, ptr);
}

template<typename T>
T Polinom<T>::valueOf(const T& arg) const {
	T ret = T();

	for (auto it = begin(); it != end(); ++it) {

		int grad = it->grad;
		if (grad == 0) {
			ret = ret + it->coef;
			continue;
		}

		T val = arg;
		for (int i = 1; i < grad; ++i) {
			val *= arg;
		}

		//cout << grad << ' ' << val << ' ' << arg << '\n';

		ret = ret + it->coef * val;
	}

	return ret;
}

template<typename T>
void Polinom<T>::clean() {
	for (auto it = begin(); it != end();) {
		auto nxt = it;
		++nxt;

		if (it->coef == T()) {
			dList<T>::erase(it);
		}

		it = nxt;
	}
}

template<typename T>
int Polinom<T>::grad() const {
	if (this->size() == 0) {
		return -1;
	}

	return (--end())->grad;
}


template<typename T>
Polinom<T> Polinom<T>::operator+(const Polinom<T>& other) {
	Polinom<T> ret;

	Polinom<T>::iterator it1 = this->begin(), it2 = other.begin();

	while (it1 != this->end() && it2 != other.end()) {
		if (it1->grad < it2->grad) {
			ret.add(ret.end(), *it1);
			++it1;
		}
		else if (it2->grad < it1->grad) {
			ret.add(ret.end(), *it2);
			++it2;
		}
		else {
			Monom<T> m(it1->coef + it2->coef, it1->grad);
			ret.add(ret.end(), m);
			++it1;
			++it2;
		}
	}

	while (it1 != this->end()) {
		ret.add(ret.end(), *it1);
		++it1;
	}

	while (it2 != other.end()) {
		//cout << *it2 << "\n\n";
		ret.add(ret.end(), *it2);
		++it2;
	}

	ret.clean();
	return ret;
}

template<typename T>
Polinom<T> Polinom<T>::operator-(const Polinom<T>& other) {
	Polinom<T> ret;

	Polinom<T>::iterator it1 = this->begin(), it2 = other.begin();

	while (it1 != this->end() && it2 != other.end()) {
		if (it1->grad < it2->grad) {
			ret.add(ret.end(), *it1);
			++it1;
		}
		else if (it2->grad < it1->grad) {
			Monom<T> m(-(it2->coef), it2->grad);
			ret.add(ret.end(), m);
			++it2;
		}
		else {
			Monom<T> m(it1->coef - it2->coef, it1->grad);
			ret.add(ret.end(), m);
			++it1;
			++it2;
		}
	}

	while (it1 != this->end()) {
		ret.add(ret.end(), *it1);
		++it1;
	}

	while (it2 != other.end()) {
		Monom<T> m(-(it2->coef), it2->grad);
		ret.add(ret.end(), m);
		++it2;
	}

	ret.clean();
	return ret;
}

template<typename T>
Polinom<T> Polinom<T>::operator*(const Polinom<T>& other) {
	Polinom<T> ret;

	for (auto it1 = this->begin(); it1 != this->end(); ++it1) {
		for (auto it2 = other.begin(); it2 != other.end(); ++it2) {
			Monom<T> m(it1->coef * it2->coef, it1->grad + it2->grad);
			//cout << m << '\n';
			ret = ret + Polinom(m);
			//cout << ret << "    " << Polinom(m) << '\n';
		}
	}

	ret.clean();
	return ret;
}

template<typename T>
Polinom<T> Polinom<T>::operator/(const Polinom<T>& divisor) {
	if (divisor.grad() == -1) {
		throw std::invalid_argument("Can't divide by 0 polynomial!");
	}

	Polinom<T> rem = (*this), quotient;
	while (rem.grad() >= divisor.grad()) {
		Monom<T> finRem = *(--rem.end()), finDiv = *(--divisor.end());
		//cout << finRem.coef << ' ' << finRem.grad << ' ' << finDiv.coef << ' ' << finDiv.grad << "\n";
		Monom<T> q(finRem.coef / finDiv.coef, finRem.grad - finDiv.grad);
		quotient = quotient + Polinom(q);

		rem = rem - Polinom(q) * divisor;

		if (finRem.grad == rem.grad()) {
			rem.erase(--rem.end());
		}

		if (0) {
			cout << rem << '\n';
			cout << quotient << '\n';
			cout << divisor << '\n';
			cout << "\n";
		}
	}

	quotient.clean();
	return quotient;
}

template<typename T>
Polinom<T> Polinom<T>::operator%(const Polinom<T>& divisor) {
	if (divisor.grad() == -1) {
		throw std::invalid_argument("Can't divide by 0 polynomial!");
	}

	Polinom<T> rem = (*this), quotient;
	while (rem.grad() >= divisor.grad()) {
		Monom<T> finRem = *(--rem.end()), finDiv = *(--divisor.end());
		//cout << finRem.coef << ' ' << finRem.grad << ' ' << finDiv.coef << ' ' << finDiv.grad << "\n";
		Monom<T> q(finRem.coef / finDiv.coef, finRem.grad - finDiv.grad);
		quotient = quotient + Polinom(q);

		rem = rem - Polinom(q) * divisor;

		if (finRem.grad == rem.grad()) {
			rem.erase(--rem.end());
		}

		if (0) {
			cout << rem << '\n';
			cout << quotient << '\n';
			cout << divisor << '\n';
			cout << "\n";
		}
	}

	rem.clean();
	return rem;
}

template<typename T>
Monom<T>& Polinom<T>::operator[] (int idx) {
	if (idx >= this->size() || idx < 0) {
		throw std::invalid_argument("Index isn't correct!");
	}

	auto it = this->begin();
	for (int curr = 0; curr < idx; ++it, ++curr) ;
	return *it;
}

template<typename T>
bool Polinom<T>::operator<(const dList<T>& other) const {
	bool fail = false;
	try {
		dynamic_cast<const Polinom<T>&>(other);
	}
	catch (...) {
		fail = true;
	}

	if (!fail) {
		auto it1 = this->begin(), it2 = ((const Polinom<T>&)other).begin();
		for (; it1 != this->end() && it2 != ((const Polinom<T>&)other).end(); ++it1, ++it2) {
			if (*it1 < *it2) {
				return true;
			}

			if (*it2 < *it1) {
				return false;
			}
		}

		if (it1 == this->end() && it2 != ((const Polinom<T>&)other).end()) {
			return true;
		}

		return false;
	}
	
	auto it1 = this->dList<T>::begin(), it2 = other.begin();
	for (; it1 != this->dList<T>::end() && it2 != other.end(); ++it1, ++it2) {
		if (*it1 < *it2) {
			return true;
		}

		if (*it2 < *it1) {
			return false;
		}
	}

	if (it1 == dList<T>::end() && it2 != other.end()) {
		return true;
	}

	return false;
}

/*
template<typename T>
bool Polinom<T>::operator==(const Polinom<T>& other) const {
	return !((*this) < other || other < (*this));
}

template<typename T>
bool Polinom<T>::operator!=(const Polinom<T>& other) const {
	return !((*this) == other);
}
//*/

template<typename T>
Polinom<T>::~Polinom() {}

template<typename T>
std::istream& operator>>(std::istream& in, Polinom<T>& p) {
	p.clear();

	int N;
	in >> N;
	for (int i = 0;i < N;++i) {
		Monom<T> m;
		in >> m;
		p.add(p.end(), m);
	}

	if (p.size() < 2) {
		return in;
	}

	for (typename Polinom<T>::iterator it = ++p.begin(); it != p.end(); ++it) {
		auto aux = it;
		--aux;
		if (aux->grad >= it->grad) {
			throw std::invalid_argument("Polinomul trebuie sa aiba gradele in ordine crescatoare!");
		}
	}

	p.clean();
	return in;
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Polinom<U>& p) {
	if (p.size() == 0) {
		out << 0;
		return out;
	}

	typename Polinom<U>::iterator it = p.begin();
	out << *it;

	for (++it; it != p.end(); ++it) {
		out << " + " << *it;
	}

	return out;
}