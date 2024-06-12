#ifndef __ADDER__H_
#define __ADDER__H_

template<int T>
class Adder : public sc_module {
public:
	sc_in<bool> nrst;
	sc_in<bool> clk;
	sc_in<sc_int<T>> a;
	sc_in<sc_int<T>> b;
	sc_out<sc_int<T + 1>> c;
	sc_out<sc_int<T>> c_overflow;

	// isn't it necessary? 

	Adder(sc_module_name name) : sc_module(name) {
		SC_THREAD(main);
		sensitive << clk.pos();
	}

	void main();
};

#endif