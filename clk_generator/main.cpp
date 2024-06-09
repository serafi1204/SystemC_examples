#include <systemc.h>
#include <string>
using namespace std;

/** NOTE
* CLK_PERIOD(ns)
* CLK_DUTY_CYCLE(%): 0~1
* CLK_TIME_UNIT(ns): initial pause time
* 
* referance LNK : https://www.learnsystemc.com/basic/clock
*/
#define CLK_PERIOD 1
#define CLK_TIME_UNIT 0.5
#define	CLK_DUTY_CYCLE 10
#define VSD_NAME "top"

void openGTKwave() {
	string run_commend;

	run_commend = "gtkwave ";
	run_commend += VSD_NAME;
	run_commend += ".vcd";

	system(run_commend.c_str());
}

int sc_main(int argc, char* argv[]) {
	sc_clock clk("clk", CLK_PERIOD, CLK_DUTY_CYCLE, CLK_TIME_UNIT, 0);
	sc_trace_file* fp;

	fp = sc_create_vcd_trace_file(VSD_NAME);
	fp->set_time_unit(100, SC_PS);
	sc_trace(fp, clk, "CLK");

	sc_start(1000, SC_NS);
	sc_close_vcd_trace_file(fp);
	
	openGTKwave();
	return 0;
}
