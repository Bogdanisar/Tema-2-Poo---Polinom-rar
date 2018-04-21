

template<typename T>
class dList<T>::iterator {
	DoubleNode<T>* ptr;
	DoubleNode<T>* sent;

	friend dList<T>;
	friend Polinom<T>;

private:
	iterator(DoubleNode<T>* _ptr, DoubleNode<T>* _sent) : ptr(_ptr), sent(_sent) {}

public:

	iterator& operator=(const iterator& other) {
		if (this == &other) {
			return *this;
		}

		ptr = other.ptr;
		sent = other.sent;
	}

	virtual const iterator& operator++ () {
		/*
		if (ptr == sent) {
			throw exception("Can't move past end()!");
		}
		//*/
		ptr = (DoubleNode<T>*)ptr->nxt;
		return *this;
	}

	virtual iterator operator++ (int) {
		iterator ret(*this);
		this->operator++();
		return ret;
	}
	
	virtual const iterator& operator-- () {
		/*
		if (ptr->prv == sent) {
			throw exception("Can't move past begin()!");
		}
		//*/
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

	T& operator* () const {
		if (ptr == sent) {
			throw std::domain_error("Can't dereference end()!");
		}
		return ptr->info;
	}
};

template<typename T>
void dList<T>::initialize() {
	sz = 0;
	sentinel = new DoubleNode<T>();
	sentinel->nxt = sentinel;
	sentinel->prv = sentinel;
};

template<typename T>
dList<T>::dList() {
	initialize();
}

template<typename T>
dList<T>::dList(const dList<T>& other) {
	initialize();

	for (iterator it = other.begin(); it != other.end(); ++it) {
		push_back(*it);
	}
}

template<typename T>
dList<T>::dList(unsigned sz, const T& element) {
	initialize();

	for (unsigned i = 0; i < sz; ++i) {
		push_back(element);
	}
}

template<typename T>
dList<T>& dList<T>::operator= (const dList<T>& other) {
	if (this == &other) {
		return *this;
	}

	/*
	this->~dList();
	initialize();
	//*/
	clear();

	for (iterator it = other.begin(); it != other.end(); ++it) {
		push_back(*it);
	}

	return *this;
}

template<typename T>
void dList<T>::push_front(const T& element) {
	add(begin(), element);
}

template<typename T>
void dList<T>::push_back(const T& element) {
	add({ sentinel, sentinel}, element);
}

template<typename T>
void dList<T>::add(const iterator& it, DoubleNode<T>* node) {
	if (it.sent != sentinel) {
		throw std::invalid_argument("Erase: Iterator is from a different object!");
	}
	++sz;
	DoubleNode<T>* aux = node;
	aux->nxt = it.ptr;
	aux->prv = it.ptr->prv;
	it.ptr->prv->nxt = aux;
	it.ptr->prv = aux;
}

template<typename T>
void dList<T>::pop_front() {
	if (sz == 0) {
		throw std::length_error("List is empty! Can't pop!");
	}

	erase(begin());
}

template<typename T>
void dList<T>::pop_back() {
	if (sz == 0) {
		throw std::length_error("List is empty! Can't pop!");
	}

	iterator it = end();
	--it;
	erase(it);
}

template<typename T>
unsigned dList<T>::size() const {
	return sz;
}

template<typename T>
typename dList<T>::iterator dList<T>::begin() const {
	iterator it(sentinel, sentinel);
	++it;
	return it;
}

template<typename T>
typename dList<T>::iterator dList<T>::end() const {
	return iterator(sentinel, sentinel);
}

template<typename T>
void dList<T>::add(const iterator& it, const T& elem) {
	if (it.sent != sentinel) {
		throw std::invalid_argument("Erase: Iterator is from a different object!");
	}
	++sz;
	DoubleNode<T>* aux = new DoubleNode<T>(elem);
	aux->nxt = it.ptr;
	aux->prv = it.ptr->prv;
	it.ptr->prv->nxt = aux;
	it.ptr->prv = aux;
}

template<typename T>
void dList<T>::erase(const iterator& it) {
	if (it.sent != sentinel) {
		throw std::invalid_argument("Erase: Iterator is from a different object!");
	}
	if (it == end()) {
		throw std::exception("Can't delete end()!");
	}
	--sz;

	DoubleNode<T>* aux = it.ptr;
	it.ptr->prv->nxt = it.ptr->nxt;
	((DoubleNode<T>*)it.ptr->nxt)->prv = (DoubleNode<T>*)(it.ptr->prv);
	delete aux;
}

template<typename T>
void dList<T>::clear() {
	while (sz) {
		pop_back();
	}
}

template<typename T>
dList<T>::~dList() {
	clear();
	delete sentinel;
}

template<typename T>
bool dList<T>::operator==(const dList& other) const {
	return !((*this) < other || other < (*this));
}

template<typename T>
bool dList<T>::operator!=(const dList& other) const {
	return !((*this) == other);
}

template<typename T>
bool dList<T>::operator<(const dList& other) const {
	iterator it1 = begin(), it2 = other.begin();
	for (; it1 != end() && it2 != other.end() && *it1 == *it2; ++it1, ++it2) {}
	if (it1 == end() && it2 == other.end()) {
		return false;
	}
	if (it1 == end() || *it1 < *it2) {
		return true;
	}
	return false;
}


template<typename T>
std::istream& operator>> (std::istream& in, dList<T>& list) {
	list.clear();

	int N;
	in >> N;
	for (int i = 0; i < N; ++i) {
		T elem;
		in >> elem;
		list.push_back(elem);
	}

	return in;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const dList<T>& list) {
	for (typename dList<T>::iterator it = list.begin(); it != list.end(); ++it) {
		out << *it << ' ';
	}

	return out;
}