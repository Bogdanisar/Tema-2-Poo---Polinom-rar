#pragma once
#include "SimpleNode.h"
#include <iostream>

namespace PoliList {

	template<typename T>
	class DoubleNode : public SimpleNode<T> {
	public:
		SimpleNode<T>* prv;

	public:
		DoubleNode(T _info = T());
		DoubleNode(const DoubleNode&);

		virtual DoubleNode& operator= (const SimpleNode<T>& other);

		template<typename U>
		friend std::istream& operator>> (std::istream&, DoubleNode<U>&);

		template<typename U>
		friend std::ostream& operator<< (std::ostream&, DoubleNode<U>&);

		virtual ~DoubleNode();
	};

#include "DoubleNode.cpp"
}