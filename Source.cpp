#include "SimpleNode.h"
#include "DoubleNode.h"
#include "Monom.h"
#include "dList.h"
#include "Polinom.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#if 1
#define pv(x) cout<<#x<<" = "<<(x)<<"; ";cout.flush()
#define pn cout<<endl
#else
#define pv(x)
#define pn
#endif

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;
#define pb push_back
#define mp make_pair
const int NMax = 3e6 + 5;
const ll inf_ll = 1e18 + 5;
const int inf_int = 1e9 + 5;
const int mod = 100003;
using zint = int;

using namespace PoliList;

int main() {
	ifstream in("date.in");
	ofstream out("date.out");

	try {
		//*
		dList<int> lst(1, 1);
		lst = dList<int>(2, 3);

		in >> lst;
		for (dList<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
			cout << *it << ' ';
		}
		cout << '\n';

		lst.pop_front();
		lst.pop_back();

		lst.push_front(1);
		lst.add(++lst.begin(), 2);

		lst.push_back(10);
		lst.erase(--lst.end());

		out << lst;
		out << '\n';
		//*/

		//*
		Polinom<double> a, b;
		in >> a >> b;
		pv(a); pn;
		pv(b); pn;
		pv((a*b)[0]); pn;
		out << a + b << '\n' << a - b << '\n';
		out << a * b << '\n';
		out << a / b << '\n';
		out << a % b << "\n\n";
		out << a[2] << '\n';
		out << b.valueOf(1.1) << '\n';
		//*/

		Polinom<int> p1(Monom<int>(2, 2));
		Polinom<int> p2(Monom<int>(1, 3));

		pv((p1 < p2)); pn;
	}
	catch (const exception& e) {
		pv(e.what());
	}

	return 0;
}

