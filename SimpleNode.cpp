#pragma once

template<typename T>
SimpleNode<T>::SimpleNode(T _info) :
	info(_info), nxt(nullptr) {
}

template<typename T>
SimpleNode<T>::SimpleNode(const SimpleNode& other) :
	info(other.info), nxt(other.nxt) {}

template<typename T>
SimpleNode<T>& SimpleNode<T>::operator= (const SimpleNode& other) {
	if (this == &other) {
		return *this;
	}

	info = other.info;
	nxt = other.nxt;
	return *this;
}


template<typename T>
std::istream& operator>> (std::istream& in, SimpleNode<T>& node) {
	in >> node.info;
	return in;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, SimpleNode<T>& node) {
	out << node.info;
	return out;
}

template<typename T>
SimpleNode<T>::~SimpleNode() {}
