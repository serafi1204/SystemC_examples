#include <systemc.h>
#include <string>
#include "adder.h"
using namespace std;
using namespace sc_core;

template<int T>
void Adder<T>::main() {
	while (1) {
		c = sc_int<T>(a) + sc_int<T>(b);
		c_overflow = sc_int<T>(a) + sc_int<T>(b);
		wait();
	}
}