#pragma once

#include <iostream>

namespace PoliList {
	template<typename T>
	class SimpleNode {
	public:
		T info;
		SimpleNode* nxt;

	public:

		SimpleNode(T _info = T());
		SimpleNode(const SimpleNode&);
		virtual SimpleNode& operator= (const SimpleNode& other);

		//*
		template<typename U>
		friend std::istream& operator>> (std::istream&, SimpleNode<U>&);

		template<typename U>
		friend std::ostream& operator<< (std::ostream&, SimpleNode<U>&);
		//*/

		virtual ~SimpleNode();
	};

#include "SimpleNode.cpp"
}