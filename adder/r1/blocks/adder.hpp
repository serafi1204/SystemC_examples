#ifndef __ADDER__H_
#define __ADDER__H_

#include <systemc.h>
#include <string>

using namespace std;
using namespace sc_core;

template<int T>
class Adder : public sc_module {
public:
	sc_in<bool> nrst;
	sc_in<bool> clk;
	sc_in<sc_int<T>> in0;
	sc_in<sc_int<T>> in1;
	sc_out<sc_int<T>> out;

	Adder(sc_module_name name) : sc_module(name) {
		SC_THREAD(main);
		sensitive << clk.pos() << nrst;
	}

private:
	sc_int<T+1> res;


	void main();
};

template<int T>
void Adder<T>::main() {
	while (1) {
		if (nrst.read() == 0) wait();

		res = in0.read() + in1.read();
		out = res.range(T, 1);

		wait();
	}
}

#endif