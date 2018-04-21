#pragma once

template<typename T>
DoubleNode<T>::DoubleNode(T _info): 
	SimpleNode<T>(_info), prv(nullptr) {}

template<typename T>
DoubleNode<T>::DoubleNode(const DoubleNode<T>& other): 
	SimpleNode<T>(other), prv(other.prv) {}

template<typename T>
DoubleNode<T>& DoubleNode<T>::operator= (const SimpleNode<T>& other) {
	if (this == &other) {
		return *this;
	}

	SimpleNode<T>::operator=(other);

	bool fail = false;
	try {
		dynamic_cast<const DoubleNode<T>&>(other);
	}
	catch (exception e) {
		fail = true;
	}
	if (fail) {
		prv = nullptr;
	}
	else {
		prv = ((DoubleNode<T>&)other).prv;
	}

	return *this;
}

template<typename T>
std::istream& operator>> (std::istream& in, DoubleNode<T>& node) {
	in >> (SimpleNode<T>&)node;
	return in;
}

//*
template<typename T>
std::ostream& operator<< (std::ostream& out, DoubleNode<T>& node) {
	out << (SimpleNode<T>&)node;
	//out << "heh\n";
	return out;
}
//*/

template<typename T>
DoubleNode<T>::~DoubleNode() {

}