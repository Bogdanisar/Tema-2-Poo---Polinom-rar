#pragma once
#include "DoubleNode.h"
#include <stdexcept>

namespace PoliList {
	template<typename T> class dList;

	template<typename T> class Polinom;


	template<typename T>
	class dList {
	public:
		class iterator;

	private:
		unsigned sz;
		void initialize();

	protected:
		DoubleNode<T> *sentinel;
		void add(const iterator&, DoubleNode<T>*);

	public:
		dList();
		dList(unsigned, const T&);
		dList(const dList&);

		virtual dList& operator=(const dList&);

		virtual void push_front(const T&);
		virtual void push_back(const T&);
		void pop_front();
		void pop_back();
		virtual void add(const iterator&, const T&);
		void erase(const iterator&);
		unsigned size() const;
		void clear();
		iterator begin() const;
		iterator end() const;

		bool operator==(const dList&) const;
		bool operator!=(const dList&) const;
		virtual bool operator<(const dList&) const;

		template<typename U>
		friend std::istream& operator>> (std::istream&, dList<U>&);

		template<typename U>
		friend std::ostream& operator<< (std::ostream&, const dList<U>&);

		virtual ~dList();
	};

	#include "dList.cpp"
}