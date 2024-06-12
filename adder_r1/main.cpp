/** NOTE
* CLK_PERIOD(ns)
* CLK_DUTY_CYCLE(%): 0~1
* CLK_TIME_UNIT(ns): initial pause time
* 
* referance LNK : https://www.learnsystemc.com/basic/clock
*/
#include <systemc.h>
#include <string>
#include "blocks/adder.h"
using namespace std;
using namespace sc_core;

#define CLK_PERIOD 1
#define CLK_TIME_UNIT 2
#define	CLK_DUTY_CYCLE 0.5
#define VSD_NAME "top"

// clk
sc_clock clk("clk", CLK_PERIOD, CLK_DUTY_CYCLE, CLK_TIME_UNIT, 0);

// signals
sc_signal<sc_int<8>> a, b, c_overflow;
sc_signal<sc_int<9>> c;
sc_signal<bool> nrst;

void testbench() {
	nrst = 1;
	a = 0;
	b = 0;

	sc_start(1, SC_NS);
	nrst = 0;

	sc_start(1, SC_NS);
	a = 0b01111111;

	sc_start(1, SC_NS);
	b = 1;

	sc_start(80, SC_NS);
}

void openGTKwave() {
	string run_commend;

	run_commend = "gtkwave ";
	run_commend += VSD_NAME;
	run_commend += ".vcd";

	system(run_commend.c_str());
}

int sc_main(int argc, char* argv[]) {
	// Wave
	sc_trace_file* fp;
	fp = sc_create_vcd_trace_file(VSD_NAME);
	fp->set_time_unit(10, SC_PS);

	// Blocks
	Adder<8> adder("adder");
	adder.clk(clk); // wiring
	adder.nrst(nrst);
	adder.a(a);
	adder.b(b);
	adder.c(c);
	adder.c_overflow(c_overflow);

	// trace
	sc_trace(fp, clk, "CLK");
	sc_trace(fp, a, "ADDER_A");
	sc_trace(fp, b, "ADDER_B");
	sc_trace(fp, c, "ADDER_C");
	sc_trace(fp, c, "ADDER_C_overflow");
	sc_trace(fp, nrst, "NRST");

	// start simulation
	testbench();

	// set wave
	sc_close_vcd_trace_file(fp);
	openGTKwave();

	return 0;
}