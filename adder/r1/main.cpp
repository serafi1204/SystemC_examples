/** NOTE
* CLK_PERIOD(ns)
* CLK_DUTY_CYCLE(%): 0~1
* CLK_TIME_UNIT(ns): initial pause time
* 
* referance LNK : https://www.learnsystemc.com/basic/clock
*/
#include <systemc.h>
#include <string>
#include "blocks.h"
using namespace std;
using namespace sc_core;

#define CLK_PERIOD 1
#define CLK_TIME_UNIT 2
#define	CLK_DUTY_CYCLE 0.5
#define VSD_NAME "top"

// clk
sc_clock clk("clk", CLK_PERIOD, CLK_DUTY_CYCLE, CLK_TIME_UNIT, 0);

// signals
sc_signal<sc_int<8>> in0, in1, out;
sc_signal<bool> nrst;

// TestBench
void testbench() {
	nrst = 0;
	in0 = 0;
	in1 = 0;

	sc_start(1, SC_NS);
	in0 = 0b01111111;

	sc_start(1, SC_NS);
	nrst = 1;


	sc_start(1, SC_NS);
	in1 = 1;

	sc_start(80, SC_NS);
}

void openGTKwave() {
	// Make commend
	string run_commend;

	run_commend = "gtkwave ";
	run_commend += VSD_NAME;
	run_commend += ".vcd";

	// Run GTKwave
	system(run_commend.c_str());
}

int sc_main(int argc, char* argv[]) {
	// Set wave file
	sc_trace_file* fp;
	fp = sc_create_vcd_trace_file(VSD_NAME);
	fp->set_time_unit(10, SC_PS);

	// Blocks
	Adder<8> adder("adder");
	adder.clk(clk); // wiring
	adder.nrst(nrst);
	adder.in0(in0);
	adder.in1(in1);
	adder.out(out);

	// Tracing
	sc_trace(fp, clk, "CLK");
	sc_trace(fp, in0, "ADDER_IN0");
	sc_trace(fp, in1, "ADDER_IN1");
	sc_trace(fp, out, "ADDER_OUT");
	sc_trace(fp, nrst, "NRST");

	// Testbench
	testbench();

	// Save & Open wave
	sc_close_vcd_trace_file(fp);
	openGTKwave();

	return 0;
}